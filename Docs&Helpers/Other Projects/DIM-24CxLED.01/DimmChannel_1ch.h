#pragma once

#include <KonnektingDevice.h>
#include "HardwareChannel.h"
#include "HardwareChannel_mega8.h"
#include "HardwareChannel_pca9685.h"
#include "config.h"
#include "DimmChannel.h"

class DimmChannel_1ch : public DimmChannel
{
  private: HardwareChannel* m_hardwareChannel;

  //params
  private: uint8_t m_fading_time;
  private: bool m_sw_on_dim;
  private: bool m_sw_off_dim;
  private: uint8_t m_switchonvalue_day = 0;
  private: uint8_t m_switchonvalue_night = 0;
  private: uint16_t m_lock_time = 0;   // fallback time after lock [min]
  private: uint8_t m_lock_mode = 0;   // lock m_lock_mode
  private: uint16_t m_autooff_time = 0;   // automatic off switch time [min]

  //comobj index
  private: byte m_comobj_sw;
  private: byte m_comobj_sw_stat;
  private: byte m_comobj_dim;
  private: byte m_comobj_dim_stat;
  private: byte m_comobj_dimrel;
  private: byte m_comobj_lock;
  private: byte m_comobj_scene;

  private: uint8_t m_currentSwValue = 0;
  private: uint8_t m_currentDimValue = 255;

  private: uint8_t m_fade_base = 0;
  private: uint8_t m_fade_goal = 0;
  private: uint8_t m_fade_steps = 0;
  private: uint8_t m_fade_step = 0;
  private: uint8_t m_fade_dir = 0;

  private: bool m_daynight = false;    // 0 = Day, 1 = Night
  private: uint32_t m_autooff_counter = 0;
  private: uint32_t m_lock_counter = 0;
  private: uint8_t m_lock_state = 0;    // 0 = no lock, != 0 lock
  private: uint8_t m_lock_value = 0;     // current dimm value due to lock

  //constructors
  public: DimmChannel_1ch(HardwareChannel* hardwareChannel, uint8_t fading_time, uint8_t sw_on_dim, uint16_t switchonvalue, uint8_t lock_mode, uint16_t lock_time, uint16_t autooff_time, byte first_comobj);
	
	public: void KnxEvent(byte index);
	
	public: void Cyclic();

  public: void Shutdown();
 
	private: void Switch(bool value);

  private: void Switch(bool value, bool ignore_sw_on_values);
	
	private: void Dimm(byte value);
	
	private: void DimmRel(byte value);
	
	private: void Fade(uint8_t value);

  private: void Lock(uint8_t value);

  private: void Scene(uint8_t value);
	
	private: void ExecFadeStep();

  public: void Refresh();

  private: void RefreshAutoOffTimer();

  private: void EvaluateAutoOffTimer();

  private: void SetLockTimer();

  private: void EvaluateLockTimer();

  private: void Unlock();

  private: void Lock_ON();

  private: void Lock_OFF();

  private: void Lock_FREEZE();

  private: void Lock_DIMM(uint8_t value);
};
