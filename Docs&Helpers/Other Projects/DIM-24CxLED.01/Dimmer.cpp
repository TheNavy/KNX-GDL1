#include "Dimmer.h"


Dimmer::Dimmer(const uint8_t outpins[])
{
  
}

void Dimmer::Setup(const uint8_t outpins[])
{
  for(int i = 0;i<NO_OF_CHANNELS;i++)
  {
    if(outpins[i] <100)
    {
      m_HardwareChannels[i] = new HardwareChannel_mega8(outpins[i], i, m_pwmtable_15);
    }
    else if(outpins[i] >=100)
    {
      int j = outpins[i]-100;
      int pca_num = j/16;
      j %= 16;

      m_HardwareChannels[i] = new HardwareChannel_pca9685(outpins[i]-100-pca_num*16, m_pwmtable_12, pca_num);
      #if (DBGLVL & DBG_DIMMER) != 0
      Debug.println(F("Dimmer::Setup new HardwareChannel_pca9685 %d %d"), outpins[i]-100-pca_num*16, pca_num);
      #endif
    }
    
    int channelgroup = i / 4;
    int channelingroup = i % 4;
    if(Konnekting.getUINT8Param(channelgroup) == 0 || channelingroup == 3)
    {
      m_DimmChannels[m_NoOfDimmChannels] = new DimmChannel_1ch(
          m_HardwareChannels[i],
          Konnekting.getUINT8Param(PARAM_ch_A_fade_time + i * PARAMS_PER_CHANNEL),
          Konnekting.getUINT8Param(PARAM_ch_A_sw_on_dim + i * PARAMS_PER_CHANNEL),
          Konnekting.getUINT16Param(PARAM_ch_A_switchvalues + i * PARAMS_PER_CHANNEL),
          Konnekting.getUINT8Param(PARAM_ch_A_lock_mode + i * PARAMS_PER_CHANNEL),
          Konnekting.getUINT16Param(PARAM_ch_A_lock_time + i * PARAMS_PER_CHANNEL),
          Konnekting.getUINT16Param(PARAM_ch_A_autooff_time + i * PARAMS_PER_CHANNEL),
          COMOBJ_ch_A_sw + i * KO_PER_CHANNEL);
          
          m_NoOfDimmChannels++;
      #if (DBGLVL & DBG_DIMMER) != 0
      Debug.println(F("Dimmer::Setup new DimmChannel_1ch"));
      #endif
    }
    else if(Konnekting.getUINT8Param(channelgroup) == 1 && channelingroup == 2)
    {
      uint8_t switchonvalues[6];
      Konnekting.getParamValue(PARAM_ch_ABC_switchvalues + channelgroup * PARAMS_PER_RGB_CHANNEL, switchonvalues);

      m_DimmChannels[m_NoOfDimmChannels] = new DimmChannel_RGB(
          m_HardwareChannels[i-2],
          m_HardwareChannels[i-1],
          m_HardwareChannels[i],
          //Konnekting.getUINT8Param(PARAM_ch_A_fade_time + (channelgroup + NO_OF_CHANNELS) * PARAMS_PER_CHANNEL), //9  //27 29 31
          Konnekting.getUINT8Param(PARAM_ch_ABC_fade_time + channelgroup * PARAMS_PER_RGB_CHANNEL), //9  //27 29 31
          //Konnekting.getUINT8Param(PARAM_ch_A_sw_on_dim + (channelgroup + NO_OF_CHANNELS) * PARAMS_PER_CHANNEL), //10 //28 30 32
          Konnekting.getUINT8Param(PARAM_ch_ABC_sw_on_dim + channelgroup * PARAMS_PER_RGB_CHANNEL), //10 //28 30 32
          switchonvalues,
          Konnekting.getUINT8Param(PARAM_ch_ABC_lock_mode + channelgroup * PARAMS_PER_RGB_CHANNEL),
          Konnekting.getUINT16Param(PARAM_ch_ABC_lock_time + channelgroup * PARAMS_PER_RGB_CHANNEL),
          Konnekting.getUINT16Param(PARAM_ch_ABC_autooff_time + channelgroup * PARAMS_PER_RGB_CHANNEL),
          COMOBJ_ch_ABC_sw + channelgroup * KO_PER_RGB_CHANNEL); //16  //48 52 56
          
          m_NoOfDimmChannels++;
      #if (DBGLVL & DBG_DIMMER) != 0
      Debug.println(F("Dimmer::Setup new DimmChannel_RGB"));
      #endif
    }
  }

  Knx.update(COMOBJ_gen_daynight);
}

void Dimmer::Cyclic()
{
  for(int i = 0;i<m_NoOfDimmChannels;i++)
  {
    m_DimmChannels[i]->Cyclic();
  }
}

void Dimmer::CyclicMax()
{
  //this method should be called with max. frequency and should block the smallest possible amount of time (max 400µs)
  uint8_t i = 0;
  while(!m_HardwareChannels[m_currentDimmChannel]->WorkerRequested() && i < NO_OF_CHANNELS)
  {
    m_currentDimmChannel++;
    m_currentDimmChannel %= NO_OF_CHANNELS;
    i++;
  }
  if(m_HardwareChannels[m_currentDimmChannel]->WorkerRequested())
    m_HardwareChannels[m_currentDimmChannel]->ExecuteWorker();
}

void Dimmer::KnxEvent(byte index)
{
  #if (DBGLVL & DBG_DIMMER) != 0
  DEBUGSERIAL.println("Dimmer::KnxEvent");
  #endif
  //Call KnxEvent on all Channels
	for(int i = 0;i<m_NoOfDimmChannels;i++)
	{
		m_DimmChannels[i]->KnxEvent(index);
	}
}

void Dimmer::Refresh()
{
  #if (DBGLVL & DBG_DIMMER) != 0
  DEBUGSERIAL.println("Dimmer::Refresh");
  #endif
  //Call Refresh on all Channels
	for(int i = 0;i<m_NoOfDimmChannels;i++)
	{
		m_DimmChannels[i]->Refresh();
	}
}

void Dimmer::Shutdown()
{
  #if (DBGLVL & DBG_DIMMER) != 0
  DEBUGSERIAL.println("Dimmer::Shutdown");
  #endif

  //Shutdown all HWChannels
	for(int i = 0;i<NO_OF_CHANNELS;i++)
	{
		m_HardwareChannels[i]->Shutdown();
	}
}