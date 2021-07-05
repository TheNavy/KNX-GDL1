#pragma once

#include <KonnektingDevice.h>
#include <Wire.h>
#include "PCA9685.h"
#include "config.h"
#include "HardwareChannel.h"


class HardwareChannel_pca9685 : public HardwareChannel
{
  //members
  private: uint8_t m_currentValue = 0;
  private: uint8_t m_currentValueHW = 0;
  private: bool m_forceSetValue = 0;
  private: uint8_t m_channel = 0;
  private: uint8_t m_controller = 0;
  private: const uint16_t *m_pwmtable;
  private: bool m_shutdown = 0;

  //constructors
  public: HardwareChannel_pca9685(uint8_t channel, const uint16_t pwmtable[], uint8_t controller);

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
  public: static PCA9685 pwmControllers[NO_OF_PCA9685];
  public: static int Setup(const uint8_t outpins[]);
  public: static int CheckConnection(const uint8_t outpins[]);
};
