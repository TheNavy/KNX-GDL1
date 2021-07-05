#pragma once

#include <KonnektingDevice.h>
#include <time.h>
#include "timeslice.h"

#include "config.h"

class KNXCLock
{
  //current offset when calculating new time
  private: double m_clock_correction = 1;

  //time at last request as POSIX
  private: uint32_t m_clock = 0;

  //value of micros() at last request
  private: uint32_t m_clock_micros = 0;

  //time at last SYNC
  private: uint32_t m_clock_sync = 0;

  //value of micros() at last SYNC
  private: uint32_t m_clock_sync_micros = 0;

  private: byte m_DPT19_ComObj = 0;

  //constructors
  public: KNXCLock(byte DPT19_ComObj);

  //gets current time as POSIX timestamp (seconds since EPOCH (1970-01-01 00:00:00))
  //call at least every 24h to prevent double overflow of micros()
  public: uint32_t Time();

  // call this as soon knx is initialized
  public: void Setup();

  //handles a time update by DPT 19.001
  public: void KnxEvent(byte index);

  public: uint32_t DPT19_2_POSIX(byte DPT19bytes[]);

  public: double SetClock(uint32_t posix, uint32_t a_micros);
};