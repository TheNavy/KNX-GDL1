#include "DimmChannel_1ch.h"


DimmChannel_1ch::DimmChannel_1ch(HardwareChannel* hardwareChannel, uint8_t fading_time, uint8_t sw_on_dim, uint16_t switchonvalue, uint8_t lock_mode, uint16_t lock_time, uint16_t autooff_time, byte first_comobj)
{
  m_hardwareChannel = hardwareChannel;

  //save params
  m_fading_time = fading_time;
  m_sw_on_dim = sw_on_dim % 2;
  m_sw_off_dim = (sw_on_dim % 4) / 2;
  m_switchonvalue_day = switchonvalue / 0x100;
  m_switchonvalue_night = switchonvalue % 0x100;
  m_lock_mode = lock_mode;
  m_lock_time = lock_time;
  m_autooff_time = autooff_time;


  m_comobj_sw = first_comobj + COMOBJ_CH_X_SW;
  m_comobj_sw_stat = first_comobj + COMOBJ_CH_X_STAT_SW;
  m_comobj_dim = first_comobj + COMOBJ_CH_X_DIM;
  m_comobj_dim_stat = first_comobj + COMOBJ_CH_X_STAT_DIM;
  m_comobj_dimrel = first_comobj + COMOBJ_CH_X_DIMREL;
  m_comobj_lock = first_comobj + COMOBJ_CH_X_LOCK;
  m_comobj_scene = first_comobj + COMOBJ_CH_X_SCENE;
}

void DimmChannel_1ch::KnxEvent(byte index)
{
  if(index == m_comobj_sw)
  {
    if(!m_lock_state)
    {
      Switch(Knx.read(index));
      RefreshAutoOffTimer();
    }
  }
  else if(index == m_comobj_dim)
  {
    if(!m_lock_state)
    {
      Dimm(Knx.read(index));
      RefreshAutoOffTimer();
    }
  }
	else if(index == m_comobj_dimrel)
  {
    if(!m_lock_state)
    {
      DimmRel(Knx.read(index));
      RefreshAutoOffTimer();
    }
  }
  else if(index == m_comobj_lock)
  {
    Lock(Knx.read(index));
  }
  else if(index == m_comobj_scene)
  {
    uint8_t sceneval = Knx.read(index);

    if(sceneval >= 128) // msb HIGH = "save" scene
    {
      Scene(sceneval);
    }
    else  // msb LOW = "call" scene
    {
      if(!m_lock_state)
      {
        Scene(sceneval);
        RefreshAutoOffTimer();
      }
    }
  }
  else if (index == COMOBJ_gen_daynight)
  {
    m_daynight = Knx.read(index);
  }
}
  
void DimmChannel_1ch::Cyclic()
{
  ExecFadeStep();
  EvaluateAutoOffTimer();
  EvaluateLockTimer();
}

void DimmChannel_1ch::Shutdown()
{
  m_hardwareChannel->SetValue(0);
}

void DimmChannel_1ch::Switch(bool value)
{
  return Switch(value, false);
}

void DimmChannel_1ch::Switch(bool value, bool ignore_sw_on_values)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Switch"));
  #endif

  if(m_currentSwValue != value)             // do nothing, when value is not changed
  {
    Knx.write(m_comobj_sw_stat, value);
    if(value)                               // switch on
    {
      #if (DBGLVL & DBG_DIMMCHANNEL) != 0
      Debug.println(F("DimmChannel_1ch::Switch Switch1"));
      #endif
      if(m_daynight)
      {
        //night
        if(m_switchonvalue_night && !ignore_sw_on_values)
          m_currentDimValue = m_switchonvalue_night;
      }
      else
      {
        //day
        if(m_switchonvalue_day && !ignore_sw_on_values)
          m_currentDimValue = m_switchonvalue_day;
      }

      if(m_currentDimValue != m_hardwareChannel->GetCurrentValue())       // send dim status if the values differ.
        Knx.write(m_comobj_dim_stat, (unsigned short)m_currentDimValue);
      if(m_fading_time == 0)
      {
        m_hardwareChannel->SetValue(m_currentDimValue);
      }
      else
      {
        Fade(m_currentDimValue);
      }
    }
    else                                    //switch off
    {
      #if (DBGLVL & DBG_DIMMCHANNEL) != 0
      Debug.println(F("DimmChannel_1ch::Switch Switch2"));
      #endif
      if(m_fading_time == 0)
        m_hardwareChannel->SetValue(0);
      else
        Fade(0);
    }
    m_currentSwValue = value;
  }
}
  
void DimmChannel_1ch::DimmRel(byte value)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::DimmRel"));
  #endif

	unsigned short steps = value % 8;
	bool dir = value & 8;
	
	if(steps) // dimm
	{
		int newvalue;
		int stepsize = 256 / pow(2, steps-1);
		if(!dir)
			stepsize *= -1;
		newvalue = m_hardwareChannel->GetCurrentValue() + stepsize;
		if(newvalue < 0)
			newvalue = 0;
		if(newvalue > 255)
			newvalue = 255;

		Dimm(newvalue);
	}
	else // stop
	{
		if(m_fade_steps)
		{
			m_fade_steps = 0; // stop fading process
			m_currentDimValue = m_hardwareChannel->GetCurrentValue();
			Knx.write(m_comobj_dim_stat, (unsigned short)m_currentDimValue);
		}
	}
}
  
void DimmChannel_1ch::Dimm(byte value)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Dimm"));
  #endif

  if(m_currentDimValue != value)             // do nothing, when value is not changed
  {
    if(m_currentSwValue)                       //channel is on
    {
      if(value == 0 && m_sw_off_dim)
      {
        Knx.write(m_comobj_dim_stat, (unsigned short)m_currentDimValue);
        Switch(LOW);
      }
      else if(m_fading_time == 0)
      {
        Knx.write(m_comobj_dim_stat, (unsigned short)value);
        m_hardwareChannel->SetValue(value);
        m_currentDimValue = value;
      }
      else
      {
        Knx.write(m_comobj_dim_stat, (unsigned short)value);
        Fade(value);
        m_currentDimValue = value;
      }
    }
    else                                    //channel is off => Switch-On
    {
      m_currentDimValue = value;
      if(m_sw_on_dim)                       //channel is off and switch-on-on-dim is activated
      {
        if(m_fading_time == 0)
          Knx.write(m_comobj_dim_stat, (unsigned short)value);
          Switch(HIGH, true);                     // switch on
          //ToDo: don't overwrite Dimmvalue with switch-on-values
      }
    }
  }
  else if(m_sw_on_dim && m_currentSwValue == 0)       //value equal and channel off and switch-on-on-dim is activated
  {
    Knx.write(m_comobj_dim_stat, (unsigned short)m_currentDimValue);
    Switch(HIGH, true);                      // switch on
  }
  else if(m_sw_off_dim && m_currentSwValue == 1)       //value equal and channel on and switch-off-on-dim is activated
  {
    Knx.write(m_comobj_dim_stat, (unsigned short)m_currentDimValue);
    Switch(LOW);                      // switch off
  }
}

void DimmChannel_1ch::Lock(byte value)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Lock %u"), value);
  #endif

  if(m_lock_mode == 0x00)
  {
    // 1Bit, 0 = unlock, 1 = OFF
    value &= 0x01;
    if(value)
    {
      Lock_OFF();
    }
    else
    {
      Unlock();
    }
  }
  else if(m_lock_mode == 0x01)
  {
    // 1Bit, 0 = unlock, 1 = ON
    value &= 0x01;
    if(value)
    {
      Lock_ON();
    }
    else
    {
      Unlock();
    }
  }
  else if(m_lock_mode == 0x02)
  {
    // 1Bit, 0 = unlock, 1 = FREEZE
    value &= 0x01;
    if(value)
    {
      Lock_FREEZE();
    }
    else
    {
      Unlock();
    }
  }
  else if(m_lock_mode == 0x03)
  {
    // 1Bit, 0 = OFF, 1 = ON
    value &= 0x01;
    if(value)
    {
      Lock_ON();
    }
    else
    {
      Lock_OFF();
    }
  }
  else if(m_lock_mode == 0x10)
  {
    // 2Bit, 0x = unlock, 10 = OFF, 11 = ON
    value &= 0x03;
    if(value <= 1)
    {
      //0x = unlock
      Unlock();
    }
    else if(value <= 2)
    {
      //10 = OFF
      Lock_OFF();
    }
    else
    {
      //11 = ON
      Lock_ON();
    }
  }
  else if(m_lock_mode == 0x11)
  {
    // 2Bit, 0x = unlock, 10 = OFF, 11 = FREEZE
    value &= 0x03;
    if(value <= 1)
    {
      //0x = unlock
      Unlock();
    }
    else if(value <= 2)
    {
      //10 = OFF
      Lock_OFF();
    }
    else
    {
      //11 = FREEZE
      Lock_FREEZE();
    }
  }
  else if(m_lock_mode == 0x12)
  {
    // 2Bit, 0x = unlock, 10 = FREEZE, 11 = ON
    value &= 0x03;
    if(value <= 1)
    {
      //0x = unlock
      Unlock();
    }
    else if(value <= 2)
    {
      //10 = OFF
      Lock_FREEZE();
    }
    else
    {
      //11 = ON
      Lock_ON();
    }
  }
  else if(m_lock_mode == 0x20)
  {
    // 8Bit, 0 = unlock, 01-FF = Dimmvalue
    if(value)
    {
      Lock_DIMM(value);
    }
    else
    {
      Unlock();
    }
  }
}

void DimmChannel_1ch::Lock_ON()
{
  //Wird bei aktiver Animation (AN) eine Sperre AN gesetzt, so bleibt die Animation erhalten (egal, ob ein Einschaltwert definiert ist)
  //Wird bei aktiver Animation (AUS) eine Sperre AN gesetzt, so bleibt die Animation erhalten wenn kein Einschaltwert definiert ist. Andernfalls wird die Animation beendet und der Einschaltwert gesetzt.
  //Bei AN über Sperrobjekt wird der aktuell passende Einschaltwert Tag bzw. Nacht gesetzt
  //Ist der Kanal AN und wird über Lock ein AN angefordert, so wird der aktuelle Wert beibehalten, auch wenn ein spez. Einschaltwert definiert ist.

  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Lock_ON"));
  #endif

  m_lock_state = true;
  m_lock_value = m_currentDimValue;
  SetLockTimer();

  if(!m_currentSwValue)   // channel off
  {
    if(m_daynight)
    {
      //night
      if(m_switchonvalue_night)
        m_lock_value = m_switchonvalue_night;
    }
    else
    {
      //day
      if(m_switchonvalue_day)
        m_lock_value = m_switchonvalue_day;
    }

    if(m_fading_time == 0)
    {
      m_hardwareChannel->SetValue(m_lock_value);
    }
    else
      Fade(m_lock_value);
  }

  m_autooff_counter = 0;
}

void DimmChannel_1ch::Lock_OFF()
{
  //Wird bei aktiver Animation (AN) eine Sperre AUS gesetzt, so bleibt die Animation erhalten und der Kanal wird ausgeschaltet.
  //Wird bei aktiver Animation (AUS) eine Sperre AUS gesetzt, so bleibt die Animation erhalten und der Kanal bleibt ausgeschaltet.
  //Bei AUS über Sperrobjekt wird der Kanal ausgeschaltet.

  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Lock_OFF"));
  #endif

  m_lock_state = true;
  m_lock_value = 0;
  SetLockTimer();

  if(m_fading_time == 0)
    m_hardwareChannel->SetValue(m_lock_value);
  else
    Fade(m_lock_value);

  m_autooff_counter = 0;
}

void DimmChannel_1ch::Lock_FREEZE()
{
  //Wird bei aktiver Animation (AN oder AUS) eine Sperre FREEZE gesetzt, so bleibt die Animation erhalten.

  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Lock_FREEZE"));
  #endif

  m_lock_state = true;
  SetLockTimer();

  if(m_currentSwValue)
    m_lock_value = m_currentDimValue;
  else
    m_lock_value = 0;
  
  m_autooff_counter = 0;
}

void DimmChannel_1ch::Lock_DIMM(uint8_t value)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Lock_DIMM %d"),value );
  #endif

  m_lock_state = true;
  m_lock_value = value;
  SetLockTimer();


  if(m_fading_time == 0)
  {
    m_hardwareChannel->SetValue(m_lock_value);
  }
  else
    Fade(m_lock_value);

  m_autooff_counter = 0;
}

void DimmChannel_1ch::Unlock()
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Unlock"));
  #endif

  // set lock flag to unlocked
  m_lock_state = false;
  m_lock_counter = 0;

  // restore old values
  Refresh();

  // set unlock counter
  RefreshAutoOffTimer();
}

void DimmChannel_1ch::Scene(byte value)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Scene %u"), value);
  #endif

  //ToDo
  //
}
  
void DimmChannel_1ch::Fade(uint8_t value)
{
  m_fade_base = m_hardwareChannel->GetCurrentValue();   //cant use m_currentDimValue here, because a fade could be ongoing
  m_fade_goal = value;

  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Fade Fade1 %d %d %d %d %d"),m_fade_base, m_fade_goal, m_fade_steps, m_fade_step, m_fade_dir );
  #endif

  if(m_fade_base != m_fade_goal)
  {
    m_fade_steps = abs((m_fade_goal - m_fade_base)) / (m_fading_time);
    if(abs((m_fade_goal - m_fade_base)) % (m_fading_time))
      m_fade_steps++;
    m_fade_step = 1;
    m_fade_dir = m_fade_goal > m_fade_base;

    #if (DBGLVL & DBG_DIMMCHANNEL) != 0
    Debug.println(F("DimmChannel_1ch::Fade Fade2 %d %d %d %d %d"),m_fade_base, m_fade_goal, m_fade_steps, m_fade_step, m_fade_dir );
    #endif

    ExecFadeStep();
  }
}
  
void DimmChannel_1ch::ExecFadeStep()
{
	if(m_fade_step < m_fade_steps)
  {
    #if (DBGLVL & DBG_DIMMCHANNEL) != 0
    Debug.println(F("DimmChannel_1ch::ExecFadeStep: %d %d %d"), m_fade_step, m_fade_steps, m_fade_goal);
    #endif
    if(m_fade_dir)
      m_hardwareChannel->SetValue(m_fade_base + (m_fade_step++*m_fading_time));
    else
      m_hardwareChannel->SetValue(m_fade_base - (m_fade_step++*m_fading_time));
  }
  else if (m_fade_steps && m_fade_step == m_fade_steps)
  {
    m_hardwareChannel->SetValue(m_fade_goal);
    m_fade_steps = 0;
  }
}

void DimmChannel_1ch::Refresh()
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Refresh"));
  #endif

  if(m_lock_state)
  {
    m_hardwareChannel->SetValue(m_lock_value, true);
  }
  else
  {
    if(m_currentSwValue)
      m_hardwareChannel->SetValue(m_currentDimValue, true);
    else
      m_hardwareChannel->SetValue(0, true);
  }
}

void DimmChannel_1ch::RefreshAutoOffTimer()
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::RefreshAutoOffTimer"));
  #endif
  if(m_autooff_time && m_currentSwValue)
  {
    m_autooff_counter = m_autooff_time * 60 * 40; // 60s * (1000ms / 25ms) (25ms cycletime)
  }
}

void DimmChannel_1ch::EvaluateAutoOffTimer()
{
  if(m_autooff_counter > 0)
  {
    m_autooff_counter--;
    if(m_autooff_counter == 0)
    {       
      Switch(LOW);
    }
  }
}

void DimmChannel_1ch::SetLockTimer()
{
  if(m_lock_time)
  {
    m_lock_counter = m_lock_time * 60 * 40; // 60s * (1000ms / 25ms) (25ms cycletime)
    #if (DBGLVL & DBG_DIMMCHANNEL) != 0
    Debug.println(F("DimmChannel_1ch::SetLockTimer %d"), m_lock_counter);
    #endif
  }
}

void DimmChannel_1ch::EvaluateLockTimer()
{
  if(m_lock_counter > 0)
  {
    #if (DBGLVL & DBG_DIMMCHANNEL) != 0
    //Debug.println(F("DimmChannel_1ch::EvaluateLockTimer: %d"), m_lock_counter);
    #endif
    m_lock_counter--;
    if(m_lock_counter == 0)
    {
      #if (DBGLVL & DBG_DIMMCHANNEL) != 0
      Debug.println(F("DimmChannel_1ch::EvaluateLockTimer: reached 0"));
      #endif
      Unlock();
    }
  }
}
