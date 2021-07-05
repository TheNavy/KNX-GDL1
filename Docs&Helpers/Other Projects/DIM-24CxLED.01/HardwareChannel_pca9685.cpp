#include "HardwareChannel_pca9685.h"

  PCA9685 HardwareChannel_pca9685::pwmControllers[NO_OF_PCA9685] = {PCA9685(), PCA9685()};

  int HardwareChannel_pca9685::Setup(const uint8_t outpins[])
  {
    #if (DBGLVL & DBG_HWCHANNEL) != 0
      Debug.println(F("HardwareChannel_pca9685::Setup"));
    #endif

    int retval = 0;

    
    Wire.begin();                       // Wire must be started first
    Wire.setClock(1000000);              // Supported baud rates are 100kHz, 400kHz, and 1000kHz

    for(int i = 0;i< NO_OF_PCA9685;i++)
    {
      pwmControllers[i] = PCA9685(Wire, PCA9685_PhaseBalancer_None);
      if(i == 0)
        pwmControllers[0].resetDevices();
      pwmControllers[i].init(i);
      pwmControllers[i].setPWMFrequency(500);
      pwmControllers[i].setAllChannelsPWM(0);
      uint8_t i2cerror = pwmControllers[i].getLastI2CError();
      if (i2cerror)
      {
        #if (DBGLVL & DBG_HWCHANNEL) != 0
          Debug.println(F("HardwareChannel PCA %d Setup i2c error %d"),i, i2cerror);
        #endif
        retval = i2cerror;
      }
        
    }

    #if (DBGLVL & DBG_HWCHANNEL) != 0
    Debug.println("HardwareChannel_pca9685::Setup printModuleInfo");
      #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
      pwmControllers[0].printModuleInfo();
      pwmControllers[1].printModuleInfo();
      #endif
    #endif

    return retval;
  }

  HardwareChannel_pca9685::HardwareChannel_pca9685(uint8_t channel, const uint16_t pwmtable[], uint8_t controller)
  {
    m_channel = channel;
    m_pwmtable = pwmtable;
    m_controller = controller;
  }
 
 void HardwareChannel_pca9685::SetValue(uint8_t value, bool force)
{
  #if (DBGLVL & DBG_HWCHANNEL) != 0
  Debug.println(F("HardwareChannel_pca9685::SetValue PCA %d Set Value 0x%02X (%d)"),m_channel, m_pwmtable[value], force);
  #endif
  m_currentValue = value;
  if(force)
  {
    m_forceSetValue = true;
  }
}

bool HardwareChannel_pca9685::WorkerRequested()
{
  if(m_forceSetValue)
  {
    #if (DBGLVL & DBG_HWCHANNEL) != 0
    Debug.println(F("HardwareChannel_pca9685::WorkerRequested forced"));
    #endif
    return true;
  }
  else
  {
    return (m_currentValue != m_currentValueHW);
  }
}


void HardwareChannel_pca9685::ExecuteWorker()
{
  #if (DBGLVL & DBG_HWCHANNEL) != 0
  Debug.println(F("HardwareChannel_pca9685::ExecuteWorker PCA %d ExecuteWorker %d %d %d %d %d"),m_channel,  m_currentValueHW, m_currentValue, pwmControllers[m_controller].getLastI2CError(), pwmControllers[m_controller].getI2CAddress(),  m_pwmtable[m_currentValue]);
  #endif

  if(!m_shutdown)
    pwmControllers[m_controller].setChannelPWM(m_channel, m_pwmtable[m_currentValue]);

  m_forceSetValue = false;
  m_currentValueHW = m_currentValue;
}

void HardwareChannel_pca9685::Shutdown()
{
  #if (DBGLVL & DBG_HWCHANNEL) != 0
  Debug.println(F("HardwareChannel_pca9685::Shutdown"));
  #endif

  m_shutdown = true;
  pwmControllers[m_controller].setChannelPWM(m_channel, 0);
}


int HardwareChannel_pca9685::CheckConnection(const uint8_t outpins[])
{
  // return values
  // 0 = all good
  // 1 = PCA9685 gone away
  // 2 = PCA9685 i2cerror after Re-Setup
  // 3 = Re-Setup successfull, do refresh
  #if (DBGLVL & DBG_HWCHANNEL) != 0
    Debug.println(F("HardwareChannel_pca9685::CheckConnection"));
  #endif

  int retval = 0;
  
  for(int i = 0;i< NO_OF_PCA9685;i++)
  {
    bool do_reset = false;
    byte val = pwmControllers[i].readRegister(0x01); //PCA9685_MODE2_REG
    #if (DBGLVL & DBG_HWCHANNEL) != 0
      Debug.println(F("HardwareChannel_pca9685::CheckConnection PCA %d MODE2 REG %d"),i , val);
    #endif
    if(val != 0x0C)
    {
      #if (DBGLVL & DBG_HWCHANNEL) != 0
      Debug.println(F("HardwareChannel_pca9685::CheckConnection PCA %dn error detected"), i, val);
      #endif
      
      if(val == 0x00)
      {
        retval = 1;
      }
      else if (val == 0x04)
      {
        do_reset = true;
      }
    }

    if(do_reset)
    {
      #if (DBGLVL & DBG_HWCHANNEL) != 0
      Debug.println(F("HardwareChannel_pca9685::CheckConnection do reset"));
      #endif

      if(HardwareChannel_pca9685::Setup(outpins) == 0)
        return 3;
      else
        return 2;
    }
  }

  return retval;
}

  
