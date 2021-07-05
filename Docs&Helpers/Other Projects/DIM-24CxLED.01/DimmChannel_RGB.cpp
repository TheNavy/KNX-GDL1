#include "DimmChannel_RGB.h"

 
DimmChannel_RGB::DimmChannel_RGB(HardwareChannel* hardwareChannel_R, HardwareChannel* hardwareChannel_G, HardwareChannel* hardwareChannel_B, uint8_t fading_time, uint8_t sw_on_dim, uint8_t switchonvalue[], uint8_t lock_mode, uint16_t lock_time, uint16_t autooff_time, byte first_comobj)
{
  m_hardwareChannel_R = hardwareChannel_R;
  m_hardwareChannel_G = hardwareChannel_G;
  m_hardwareChannel_B = hardwareChannel_B;
  m_hardwareChannels[0] = m_hardwareChannel_R;
  m_hardwareChannels[1] = m_hardwareChannel_G;
  m_hardwareChannels[2] = m_hardwareChannel_B;

  //save params
  m_fading_time = fading_time;
  m_sw_on_dim = sw_on_dim % 2;
  m_sw_off_dim = (sw_on_dim % 4) / 2;
  for(int i = 0;i<3;i++)
  {
    m_switchonvalue_day[i] = switchonvalue[i];
    m_switchonvalue_night[i] = switchonvalue[i+3];
  }
  m_lock_mode = lock_mode;
  m_lock_time = lock_time;
  m_autooff_time = autooff_time;

  m_comobj_sw = first_comobj + COMOBJ_CH_X_SW;
  m_comobj_sw_stat = first_comobj + COMOBJ_CH_X_STAT_SW;
  m_comobj_dim = first_comobj + COMOBJ_CH_X_DIM;
  m_comobj_dim_stat = first_comobj + COMOBJ_CH_X_STAT_DIM;
  m_comobj_lock = first_comobj + COMOBJ_CH_X_LOCK;
  m_comobj_scene = first_comobj + COMOBJ_CH_X_SCENE;
  m_comobj_animation = first_comobj + COMOBJ_CH_X_ANIMATION;
}

void DimmChannel_RGB::KnxEvent(byte index)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  DEBUGSERIAL.println("DimmChannel_RGB::KnxEvent");
  #endif
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
      byte rgb[3];
      Knx.read(index, rgb);
      Dimm(rgb);
      RefreshAutoOffTimer();
    }
  }
  else if(index == m_comobj_animation)
  {
    if(!m_lock_state)
    {
      Animation(Knx.read(index));
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
	
void DimmChannel_RGB::Cyclic()
{
  ExecFadeStep();
  ExecAnimation();
  EvaluateAutoOffTimer();
}

void DimmChannel_RGB::Shutdown()
{
  m_hardwareChannel_R->SetValue(0);
  m_hardwareChannel_G->SetValue(0);
  m_hardwareChannel_B->SetValue(0);
}

void DimmChannel_RGB::Switch(bool value)
{
  return Switch(value, false);
}

void DimmChannel_RGB::Switch(bool value, bool ignore_sw_on_values)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_RGB::Switch: %d"), value);
  #endif

  if(m_currentSwValue != value)             // do nothing, when value is not changed
  {
    Knx.write(m_comobj_sw_stat, value);
    if(value)                               // switch on
    {
      if(m_daynight)
      {
        //night
        if((!(m_switchonvalue_night[0] == 0 || m_switchonvalue_night[1] == 0 || m_switchonvalue_night[2] == 0)) && !ignore_sw_on_values)
        {
          m_currentDimValue[0] = m_switchonvalue_night[0];
          m_currentDimValue[1] = m_switchonvalue_night[1];
          m_currentDimValue[2] = m_switchonvalue_night[2];
        }
      }
      else
      {
        //day
        if((!(m_switchonvalue_day[0] == 0 || m_switchonvalue_day[1] == 0 || m_switchonvalue_day[2] == 0)) && !ignore_sw_on_values)
        {
          m_currentDimValue[0] = m_switchonvalue_day[0];
          m_currentDimValue[1] = m_switchonvalue_day[1];
          m_currentDimValue[2] = m_switchonvalue_day[2];
        }
      }

      if(m_current_animation)   // only when no animation, else don't dimm let ExecAnimation do the job
      {
        if( m_currentDimValue[0] != m_hardwareChannel_R->GetCurrentValue() ||
            m_currentDimValue[1] != m_hardwareChannel_G->GetCurrentValue() ||
            m_currentDimValue[2] != m_hardwareChannel_B->GetCurrentValue())       // send dim status if the values differ. (for example when switch on values are defined)
        {
          Knx.write(m_comobj_dim_stat, m_currentDimValue);
        }

        if(m_fading_time == 0)
        {
          SetValues(m_currentDimValue);
        }
        else
        {
          Fade(m_currentDimValue);
        }
      }
    }
    else                              // switch off
    {
      if(m_fading_time == 0)
      {
        m_hardwareChannel_R->SetValue(0);
        m_hardwareChannel_G->SetValue(0);
        m_hardwareChannel_B->SetValue(0);
      }
      else
      {
        byte zero[]={0,0,0};
        Fade(zero);
      }
    }
    m_currentSwValue = value;
  }
}
	
void DimmChannel_RGB::Dimm(byte value[])
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_RGB::Dimm: 0x%02X%02X%02X"),value[0] ,value[1],value[2]);
  #endif
  
  if(m_current_animation)
  {
    m_current_animation = 0; // every dimm exits animation
    Knx.write(m_comobj_animation, m_current_animation);
  }

  if(memcmp(m_currentDimValue, value, 3) != 0)             // do nothing, when value is not changed
  {
    Knx.write(m_comobj_dim_stat, value);
    if(m_currentSwValue)                       //channel is on
    {
      if(value[0] == 0 && value[1] == 0 && value[2] == 0 && m_sw_off_dim)
      {
        Knx.write(m_comobj_dim_stat, m_currentDimValue);
        Switch(LOW);
      }
      else if(m_fading_time == 0)
      {
        Knx.write(m_comobj_dim_stat, value);
        SetValues(value);
      }
      else
      {
        Knx.write(m_comobj_dim_stat, value);
        Fade(value);
      }

      m_currentDimValue[0] = value[0];
      m_currentDimValue[1] = value[1];
      m_currentDimValue[2] = value[2];
    }
    else                                  	//channel is off
    {
      m_currentDimValue[0] = value[0];
      m_currentDimValue[1] = value[1];
      m_currentDimValue[2] = value[2];
      if(m_sw_on_dim)                   		//channel is off and switch-on-on-dim is activated
      {
        Switch(HIGH);                  		// switch on
      }
    }

  }
  else if(m_sw_on_dim && m_currentSwValue == LOW)       //value equal and channel off and switch-on-on-dim is activated
  {
    Knx.write(m_comobj_dim_stat, m_currentDimValue);
    Switch(HIGH);                      // switch on
  }
  else if(m_sw_off_dim && m_currentSwValue == HIGH)       //value equal and channel on and switch-off-on-dim is activated
  {
    Knx.write(m_comobj_dim_stat, m_currentDimValue);
    Switch(LOW);                      // switch off
  }
}

void DimmChannel_RGB::Lock(byte value)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_RGB::Lock %u"), value);
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
}

void DimmChannel_RGB::Lock_ON()
{
  //Wird bei aktiver Animation (AN) eine Sperre AN gesetzt, so bleibt die Animation erhalten (egal, ob ein Einschaltwert definiert ist)
  //Wird bei aktiver Animation (AUS) eine Sperre AN gesetzt, so bleibt die Animation erhalten wenn kein Einschaltwert definiert ist. Andernfalls wird die Animation beendet und der Einschaltwert gesetzt.
  //Bei AN über Sperrobjekt wird der aktuell passende Einschaltwert Tag bzw. Nacht gesetzt
  //Ist der Kanal AN und wird über Lock ein AN angefordert, so wird der aktuelle Wert beibehalten, auch wenn ein spez. Einschaltwert definiert ist.

  m_lock_state = true;
  memcpy(m_lock_values, m_currentDimValue, 3); //m_lock_value = m_currentDimValue;
  m_lock_animation = m_current_animation;
  SetLockTimer();

  if(!m_currentSwValue)   // channel off
  {
    if(m_daynight)
    {
      //night
      if(m_switchonvalue_night)
      {
        memcpy(m_lock_values, m_switchonvalue_night, 3); //m_lock_value = m_switchonvalue_night;
        m_lock_animation = 0;
      }
      // else keep animation
    }
    else
    {
      //day
      if(m_switchonvalue_day)
      {
        memcpy(m_lock_values, m_switchonvalue_day, 3); //m_lock_value = m_switchonvalue_day;
        m_lock_animation = 0;
      }
      // else keep animation
    }

    if(!m_lock_animation)
    {
      if(m_fading_time == 0)
      {
        SetValues(m_lock_values); //m_hardwareChannel->SetValue(m_lock_value);
      }
      else
        Fade(m_lock_values);
    }
  }  

  m_autooff_counter = 0;
}

void DimmChannel_RGB::Lock_OFF()
{
  //Wird bei aktiver Animation (AN) eine Sperre AUS gesetzt, so bleibt die Animation erhalten und der Kanal wird ausgeschaltet.
  //Wird bei aktiver Animation (AUS) eine Sperre AUS gesetzt, so bleibt die Animation erhalten und der Kanal bleibt ausgeschaltet.
  //Bei AUS über Sperrobjekt wird der Kanal ausgeschaltet.

  m_lock_state = true;
  m_lock_values[0] = m_lock_values[1] = m_lock_values[2] = 0;
  m_lock_animation = 0;
  SetLockTimer();

  if(m_fading_time == 0)
    SetValues(m_lock_values); //m_hardwareChannel->SetValue(m_lock_value);
  else
    Fade(m_lock_values);

  m_autooff_counter = 0;
}

void DimmChannel_RGB::Lock_FREEZE()
{
  //Wird bei aktiver Animation (AN oder AUS) eine Sperre FREEZE gesetzt, so bleibt die Animation erhalten.

  m_lock_state = true;
  m_lock_animation = m_current_animation;
  SetLockTimer();

  if(m_currentSwValue)
    memcpy(m_lock_values, m_currentDimValue, 3);
  else
    m_lock_values[0] = m_lock_values[1] = m_lock_values[2] = 0;
  
  m_autooff_counter = 0;
}

void DimmChannel_RGB::Unlock()
{
  // set lock flag to unlocked
  m_lock_state = false;
  m_lock_animation = 0;
  m_lock_counter = 0;

  // restore old values
  Refresh();

  // set unlock counter
  RefreshAutoOffTimer();
}

void DimmChannel_RGB::Scene(byte value)
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_1ch::Scene %u"), value);
  #endif

  bool savescene = (value >= 128);
  uint8_t scene = value & 0x7F;

  if(savescene) //"save" scene
  {
    // RGB
      // switch status (1bit)
      // dimm status (3 byte)
      // animation status (3 byte)
      // => 4 byte / 6 kanäle

      // DimmChannel_1ch
      // switch status (1bit)
      // dimm status (1 byte)
      // => 2 byte / 24 kanäle
  }
  else        // "call" scene
  {

  }
  
}



void DimmChannel_RGB::Fade(byte value[])
{
  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_RGB::Fade: 0x%02X%02X%02X"),value[0] ,value[1],value[2]);
  #endif
  for(int i=0;i<3;i++)
  {
    m_fade_base[i] = m_hardwareChannels[i]->GetCurrentValue();		//cant use m_currentDimValue here, because a fade could be ongoing
    m_fade_goal[i] = value[i];
  
    if(m_fade_base[i] != m_fade_goal[i])
    {
      m_fade_steps[i] = abs((m_fade_goal[i] - m_fade_base[i])) / (m_fading_time);
      if(abs((m_fade_goal[i] - m_fade_base[i])) % (m_fading_time))
        m_fade_steps[i]++;
      m_fade_step[i] = 1;
      m_fade_dir[i] = m_fade_goal[i] > m_fade_base[i];
      
      ExecFadeStep();
    }
  }
}

void DimmChannel_RGB::ExecFadeStep()
{
  for(int i=0;i<3;i++)
  {
    if(m_fade_step[i] < m_fade_steps[i])
    {
      #if (DBGLVL & DBG_DIMMCHANNEL) != 0
      Debug.println(F("DimmChannel_RGB::Cyclic: %d %d %d %d"), i,m_fade_step[i],m_fade_steps[i],m_fade_goal[i] );
      #endif
      if(m_fade_dir[i])
        m_hardwareChannels[i]->SetValue(m_fade_base[i] + (m_fade_step[i]++*m_fading_time));
      else
        m_hardwareChannels[i]->SetValue(m_fade_base[i] - (m_fade_step[i]++*m_fading_time));
    }
    else if (m_fade_steps[i] && m_fade_step[i] == m_fade_steps[i])
    {
      m_hardwareChannels[i]->SetValue(m_fade_goal[i]);
      m_fade_steps[i] = 0;
    }
  }
}

void DimmChannel_RGB::Animation(uint16_t value)
{
  //#if (DBGLVL & DBG_DIMMCHANNEL) != 0
  Debug.println(F("DimmChannel_RGB::Animation: 0x%04X"),value);
  //#endif

  if(!value)  // activate animation
  {
    // cancel fade
    m_fade_steps[0] = m_fade_steps[1] = m_fade_steps[2] = 0;

    if(m_sw_off_dim && m_currentSwValue) //sw-on-on-dimm active AND Animation to deactivate AND channel currently on
    {
      m_currentSwValue = LOW;
      Knx.write(m_comobj_sw_stat, m_currentSwValue);
    }
  }
  else  // deactivate animation
  {
    if(m_sw_on_dim && !m_currentSwValue)  //sw-on-on-dimm active AND Animation to activate AND channel currently off
    {
      m_currentSwValue = HIGH;
      Knx.write(m_comobj_sw_stat, m_currentSwValue);
    }

    if(m_currentSwValue)  //if channel is on, restore the dimmvalues
    {
      SetValues(m_currentDimValue);
    }
  }
  
  m_current_animation = value;      // set current animation for cyclic
  m_current_animationstep = 0;      // reset animationstep to begin at startpoint

}

void DimmChannel_RGB::ExecAnimation()
{
  if((m_current_animation && m_currentSwValue && !m_lock_state) || (m_lock_state && m_lock_animation))
  {
    #if (DBGLVL & DBG_DIMMCHANNEL) != 0
    Debug.println(F("DimmChannel_RGB::ExecAnimation"));
    #endif

    uint8_t animation_type = m_current_animation % 0x100;
    uint8_t animation_speed = 128;
    uint8_t animation_brightness = 255;


    if(animation_type == 0x01)  // rainbow
    {
      uint8_t rgbvals[] = {0,0,0};
      RainbowColorFromStep(m_current_animationstep++, rgbvals);
      SetValues(rgbvals);
      if(m_current_animationstep == 0x600)
      {
        m_current_animationstep = 0;
      }
    }
    else if(animation_type == 0x02)  // Jump 5
    {
      uint8_t rgbvals[] = {0,0,0};
      
      if(m_current_animationstep < 20)
      {
        //rot
        rgbvals[0] = 255;
      }
      else if(m_current_animationstep < 40)
      {
        //gelb
        rgbvals[0] = 255;
        rgbvals[1] = 255;
      }
      else if(m_current_animationstep < 60)
      {
        //grün
        rgbvals[1] = 255;
      }
      else if(m_current_animationstep < 80)
      {
        //türkis
        rgbvals[1] = 255;
        rgbvals[2] = 255;
      }
      else if(m_current_animationstep < 100)
      {
        //blau
        rgbvals[2] = 255;
      }
      SetValues(rgbvals);
      m_current_animationstep++;
      if(m_current_animationstep == 100)
      {
        m_current_animationstep = 0;
      }
    }
    else if(animation_type == 0x03)  // flash 3x,  pause
    {
      uint8_t rgbvals[] = {0,0,0};
      
      if(m_current_animationstep < 4)
      {
        //rot
        rgbvals[0] = 255;
      }
      else if(m_current_animationstep < 8)
      {
        //rot
        rgbvals[0] = 0;
      }
      else if(m_current_animationstep < 12)
      {
        //rot
        rgbvals[0] = 255;
      }
      else if(m_current_animationstep < 16)
      {
        //rot
        rgbvals[0] = 0;
      }
      else if(m_current_animationstep < 20)
      {
        //rot
        rgbvals[0] = 255;
      }
      else if(m_current_animationstep < 40)
      {
        //rot
        rgbvals[0] = 0;
      }

      SetValues(rgbvals);
      m_current_animationstep++;
      if(m_current_animationstep == 40)
      {
        m_current_animationstep = 0;
      }
    }
  }
}

void DimmChannel_RGB::Refresh()
{
  if(m_lock_state)
  {
    if(!m_lock_animation)
    {
      for(int i=0;i<3;i++)
      {
        m_hardwareChannels[i]->SetValue(m_lock_values[i], true);
      }
    }
  }
  else
  {
    if(!m_current_animation)
    {
      for(int i=0;i<3;i++)
      {
        if(m_currentSwValue)
          m_hardwareChannels[i]->SetValue(m_currentDimValue[i], true);
        else
          m_hardwareChannels[i]->SetValue(0, true);
      }
    }
  }
}

void DimmChannel_RGB::RefreshAutoOffTimer()
{
  if(m_autooff_time && m_currentSwValue)
  {
    m_autooff_counter = m_autooff_time * 60 * 40; // 60s * (1000ms / 25ms) (25ms cycletime)
  }
}

void DimmChannel_RGB::EvaluateAutoOffTimer()
{
  if(m_autooff_counter > 0)
  {
    m_autooff_counter--;
    if(m_autooff_counter == 0)
    {
      Switch(0);
    }
  }
}

void DimmChannel_RGB::SetValues(uint8_t values[])
{
  m_hardwareChannel_R->SetValue(values[0]);
  m_hardwareChannel_G->SetValue(values[1]);
  m_hardwareChannel_B->SetValue(values[2]);

  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  //Debug.println(F("DimmChannel_RGB::SetValues 0x %02X %02X %02X"), values[0], values[1], values[2]);
  #endif
}

void DimmChannel_RGB::RainbowColorFromStep(uint16_t step, uint8_t rgb[])
{
  uint8_t bstep = step / 0x100;

  uint8_t ascending = step % 0x100;
  uint8_t descending = 255 - ascending;

  #if (DBGLVL & DBG_DIMMCHANNEL) != 0
  //Debug.println(F("DimmChannel_RGB::RainbowColorFromStep 0x %d %d %d"), step, bstep, ascending);
  #endif

  switch (bstep)
  {
    case 0:
      rgb[0] = 255;
      rgb[1] = ascending;
      rgb[2] = 0;
      break;
    case 1:
      rgb[0] = descending;
      rgb[1] = 255;
      rgb[2] = 0;
      break;
    case 2:
      rgb[0] = 0;
      rgb[1] = 255;
      rgb[2] = ascending;
      break;
    case 3:
      rgb[0] = 0;
      rgb[1] = descending;
      rgb[2] = 255;
      break;
    case 4:
      rgb[0] = ascending;
      rgb[1] = 0;
      rgb[2] = 255;
      break;
    case 5:
      rgb[0] = 255;
      rgb[1] = 0;
      rgb[2] = descending;
      break;
  }
}

void DimmChannel_RGB::SetLockTimer()
{
  if(m_lock_time)
  {
    m_lock_counter = m_lock_time * 60 * 40; // 60s * (1000ms / 25ms) (25ms cycletime)
    #if (DBGLVL & DBG_DIMMCHANNEL) != 0
    Debug.println(F("DimmChannel_RGB::SetLockTimer %d"), m_lock_counter);
    #endif
  }
}

void DimmChannel_RGB::EvaluateLockTimer()
{
  if(m_lock_counter > 0)
  {
    m_lock_counter--;
    if(m_lock_counter == 0)
    {
      Unlock();
    }
  }
}
