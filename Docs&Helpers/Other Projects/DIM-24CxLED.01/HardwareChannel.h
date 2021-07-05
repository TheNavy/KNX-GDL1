#pragma once
#include <KonnektingDevice.h>
#include "config.h"


class HardwareChannel
{
  //functions
  public: virtual void SetValue(uint8_t value) = 0;

  public: virtual void SetValue(uint8_t value, bool force) = 0;
  
  public: virtual uint8_t GetCurrentValue() = 0;

  public: virtual bool WorkerRequested() = 0;

  public: virtual void ExecuteWorker() = 0;

  public: virtual void Shutdown() = 0;
};