#pragma once

#include <KonnektingDevice.h>
#include <Wire.h>
#include "PCA9685.h"
#include "config.h"
#include "HardwareChannel.h"


class HardwareChannel_mega8 : public HardwareChannel
{
  //members
  private: uint8_t m_currentValue = 0;
  private: uint8_t m_pin = 0;
  private: uint8_t m_channel = 0;
  private: const uint16_t *m_pwmtable;
  private: bool m_shutdown = 0;

  //constructors
  public: HardwareChannel_mega8(uint8_t pin, uint8_t channel, const uint16_t pwmtable[]);

  //functions
  public: void SetValue(uint8_t value)
  {
    return SetValue(value, false);
  }

  public: void SetValue(uint8_t value, bool force);

  public: uint8_t GetCurrentValue()
  {
    return m_currentValue;
  }

  public: bool WorkerRequested();

  public: void ExecuteWorker();

  public: void Shutdown();
  
  private: void set_pwm(uint16_t value);
  
  private: void en_pwm(bool value);

  //statics

  public: static void Setup(const uint8_t outpins[]);
};
