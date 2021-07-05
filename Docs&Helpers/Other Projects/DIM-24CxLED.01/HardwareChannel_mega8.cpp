 #include "HardwareChannel_mega8.h"

  void HardwareChannel_mega8::Setup(const uint8_t outpins[])
  {
      for(int channel = 0;channel<NO_OF_CHANNELS;channel++)
      {
        if(outpins[channel] < 100)
        {
          digitalWrite(outpins[channel], LOW);
          pinMode(outpins[channel], OUTPUT);
        }
      }
    #ifdef __AVR_ATmega2560__  

    // Setup PWM Timer 1
    TCCR1A =
      (1 << WGM11);     // Fast PWM mode
    TCCR1B =
      (1 << WGM12) | (1 << WGM13) |   // Fast PWM mode  
      (1 << CS10);    // No clock prescaling (fastest possible freq).
      
    ICR1 = 0x7fff;      //  15-bit PWM => 488Hz
      
    // Off
    OCR1A = 0;
    OCR1B = 0;
    OCR1C = 0;

    // Setup PWM Timer 3
    TCCR3A =
      (1 << WGM31);     // Fast PWM mode
    TCCR3B =
      (1 << WGM32) | (1 << WGM33) |   // Fast PWM mode  
      (1 << CS30);    // No clock prescaling (fastest possible freq).
      
    ICR3 = 0x7fff;      //  15-bit PWM => 488Hz
      
    // Off
    OCR3A = 0;
    OCR3B = 0;
    OCR3C = 0;

    // Setup PWM Timer 4
    TCCR4A =
      (1 << WGM41);     // Fast PWM mode
    TCCR4B =
      (1 << WGM42) | (1 << WGM43) |   // Fast PWM mode  
      (1 << CS40);    // No clock prescaling (fastest possible freq).
      
    ICR4 = 0x7fff;      //  15-bit PWM => 488Hz
      
    // Off
    OCR4A = 0;
    OCR4B = 0;
    OCR4C = 0;


    // Setup PWM Timer 5
    TCCR5A =
      (1 << WGM51);     // Fast PWM mode
    TCCR5B =
      (1 << WGM52) | (1 << WGM53) |   // Fast PWM mode  
      (1 << CS50);    // No clock prescaling (fastest possible freq).
      
    ICR5 = 0x7fff;      //  15-bit PWM => 488Hz
      
    // Off
    OCR5A = 0;
    OCR5B = 0;
    OCR5C = 0;

    #endif
  }

  HardwareChannel_mega8::HardwareChannel_mega8(uint8_t pin, uint8_t channel, const uint16_t pwmtable[])
  {
    m_pin = pin;
    m_channel = channel;
    m_pwmtable = pwmtable;
  }
 
 void HardwareChannel_mega8::SetValue(uint8_t value, bool force)
  {
    #ifdef APPDEBUG
    Debug.println(F("HardwareChannel %d Set Value 0x%02X"),m_channel, value);
    #endif
    if(value == m_currentValue)
    { //nothing to do
      ;
    }
    else if(m_currentValue == 0)
    { // currently switched off
      if(value == 255)
      { //switch on
        digitalWrite(m_pin, HIGH);
      }
      else
      { //dimm
        set_pwm(m_pwmtable[value]);
        en_pwm(true);
      }
    }
    else if(m_currentValue == 255)
    { // currently switched on
      if(value == 0)
      { //switch off
        digitalWrite(m_pin, LOW);
      }
      else
      { //dimm
        set_pwm(m_pwmtable[value]);
        en_pwm(true); 
      }
    }
    else // m_currentValue >0 && m_currentValue<255
    {  // currently dimmed 
      if(value == 0)
      { //switch off
        digitalWrite(m_pin, LOW);
        en_pwm(false);
      }
      else if(value == 255)
      { //switch on
        digitalWrite(m_pin, HIGH);

        en_pwm(false);
      }
      else
      {
        set_pwm(m_pwmtable[value]);
      }
    }
    m_currentValue = value;
  }

  bool HardwareChannel_mega8::WorkerRequested()
  {
    return false;
  }

  void HardwareChannel_mega8::ExecuteWorker(){}

  void HardwareChannel_mega8::Shutdown()
  {
    #if (DBGLVL & DBG_HWCHANNEL) != 0
    Debug.println(F("HardwareChannel_mega8::Shutdown"));
    #endif

    digitalWrite(m_pin, LOW);
    en_pwm(false);
    m_shutdown = true;
  }
  
  void HardwareChannel_mega8::set_pwm(uint16_t value)
  {
    if(!m_shutdown)
    {
      switch(m_channel)
      {
        #ifdef __AVR_ATmega2560__
        case 0:
          OCR_A = value;
          break;
        case 1:
          OCR_B = value;
          break;
        case 2:
          OCR_C = value;
          break;
        case 3:
          OCR_D = value;
          break;
        case 4:
          OCR_E = value;
          break;
        case 5:
          OCR_F = value;
          break;
        case 6:
          OCR_G = value;
          break;
        case 7:
          OCR_H = value;
          break;
        case 8:
          OCR_I = value;
          break;
        case 9:
          OCR_J = value;
          break;
        case 10:
          OCR_K = value;
          break;
        case 11:
          OCR_L = value;
          break;
        #endif
      }
    }
  }
  
  void HardwareChannel_mega8::en_pwm(bool value)
  {
    if(!m_shutdown)
    {
      switch(m_channel)
      {
        #ifdef __AVR_ATmega2560__
        case 0:
          if(value)
            TCCR_A |= (1 << COM_A);
          else
            TCCR_A &= ~(1 << COM_A);
          break;
        case 1:
          if(value)
            TCCR_B |= (1 << COM_B);
          else
            TCCR_B &= ~(1 << COM_B);
          break;
        case 2:
          if(value)
            TCCR_C |= (1 << COM_C);
          else
            TCCR_C &= ~(1 << COM_C);
          break;
        case 3:
          if(value)
            TCCR_D |= (1 << COM_D);
          else
            TCCR_D &= ~(1 << COM_D);
          break;
        case 4:
          if(value)
            TCCR_E |= (1 << COM_E);
          else
            TCCR_E &= ~(1 << COM_E);
          break;
        case 5:
          if(value)
            TCCR_F |= (1 << COM_F);
          else
            TCCR_F &= ~(1 << COM_F);
          break;
        case 6:
          if(value)
            TCCR_G |= (1 << COM_G);
          else
            TCCR_G &= ~(1 << COM_G);
          break;
        case 7:
          if(value)
            TCCR_H |= (1 << COM_H);
          else
            TCCR_H &= ~(1 << COM_H);
          break;
        case 8:
          if(value)
            TCCR_I |= (1 << COM_I);
          else
            TCCR_I &= ~(1 << COM_I);
          break;
        case 9:
          if(value)
            TCCR_J |= (1 << COM_J);
          else
            TCCR_J = ~(1 << COM_J);
          break;
        case 10:
          if(value)
            TCCR_K |= (1 << COM_K);
          else
            TCCR_K &= ~(1 << COM_K);
          break;
        case 11:
          if(value)
            TCCR_L |= (1 << COM_L);
          else
            TCCR_L &= ~(1 << COM_L);
          break;
        #endif
      }
    }
  }