#include "KNXClock.h"



KNXCLock::KNXCLock(byte DPT19_ComObj)
{
  m_DPT19_ComObj = DPT19_ComObj;
}

void KNXCLock::Setup()
{
  #if (DBGLVL & DBG_KNXCLOCK) != 0
    Debug.println(F("KNXCLock::Setup"));
  #endif
  Knx.update(m_DPT19_ComObj);
}

uint32_t KNXCLock::Time()
{
  if(m_clock != 0)
  {
    uint32_t curr_micros = micros();
    uint32_t diff_micros = calculateElapsedMillis(m_clock_micros, curr_micros);
    diff_micros *= m_clock_correction;

    m_clock = m_clock + (diff_micros+500000)  / 1000000;
    m_clock_micros = curr_micros;
    return m_clock;
  }
  return 0;
}


void KNXCLock::KnxEvent(byte index)
{
  if(index == m_DPT19_ComObj)
  {
    #if (DBGLVL & DBG_KNXCLOCK) != 0
    Debug.println(F("KNXCLock::KnxEvent"));
    #endif
    uint32_t curr_micros = micros();
    byte returnedValue[8];
    Knx.read(m_DPT19_ComObj, returnedValue);
    #if (DBGLVL & DBG_KNXCLOCK) != 0
    Debug.println(F("KNXCLock::KnxEvent data: %X %X %X %X %X %X %X %X"), returnedValue[0], returnedValue[1], returnedValue[2], returnedValue[3], returnedValue[4], returnedValue[5], returnedValue[6], returnedValue[7]);
    #endif

    uint32_t knxtime = DPT19_2_POSIX(returnedValue);
    SetClock(knxtime, curr_micros);
  }
}

uint32_t KNXCLock::DPT19_2_POSIX(byte DPT19bytes[])
{
  //uint16_t year, month, day, day_of_week, hour, minutes, seconds = 0;
  bool flag_F, flag_WD, flag_NWD, flag_NY, flag_ND, flag_NDoW, flag_NT, flag_SUTI, flag_CLQ = false;

  struct tm my_time = { /*.tm_year=0, .tm_mon=0, .tm_mday=0, .tm_hour=0, .tm_min=0, .tm_sec=0*/ };

  my_time.tm_year = 1900 + DPT19bytes[0];
  my_time.tm_mon = DPT19bytes[1];
  my_time.tm_mday = DPT19bytes[2];
  my_time.tm_hour = (DPT19bytes[3]) & 0x1F;
  my_time.tm_min = DPT19bytes[4];
  my_time.tm_sec = DPT19bytes[5];

  #if (DBGLVL & DBG_KNXCLOCK) != 0
  Debug.println(F("KNXCLock::DPT19_2_POSIX %u %u %u %u %u %u"), my_time.tm_year, my_time.tm_mon, my_time.tm_mday, my_time.tm_hour, my_time.tm_min, my_time.tm_sec);
  #endif

  /*
  year = 1900 + DPT19bytes[1];
  month = DPT19bytes[2];
  day = DPT19bytes[3];
  day_of_week = (DPT19bytes[4] >> 5) & 0x07;
  hour = (DPT19bytes[4]) & 0x1F;
  minutes = DPT19bytes[5];
  seconds = DPT19bytes[6];
  */
  
  flag_F    = (DPT19bytes[6] >> 7 ) & 0x01;
  flag_WD	  = (DPT19bytes[6] >> 6 ) & 0x01;
  flag_NWD	= (DPT19bytes[6] >> 5 ) & 0x01;
  flag_NY	  = (DPT19bytes[6] >> 4 ) & 0x01;
  flag_ND	  = (DPT19bytes[6] >> 3 ) & 0x01;
  flag_NDoW	= (DPT19bytes[6] >> 2 ) & 0x01;
  flag_NT	  = (DPT19bytes[6] >> 1 ) & 0x01;
  flag_SUTI	= (DPT19bytes[6]      ) & 0x01;
  flag_CLQ	= (DPT19bytes[7] >> 7 ) & 0x01;
  
  if(!(flag_F || flag_NY || flag_ND || flag_NT))
  {
    #if (DBGLVL & DBG_KNXCLOCK) != 0
    Debug.println(F("KNXCLock::DPT19_2_POSIX %u"), mktime(&my_time));
    #endif
    return mktime(&my_time);
  }
  else
  {
    return 0;
  }
}

double KNXCLock::SetClock(uint32_t posix, uint32_t a_micros)
{
  #if (DBGLVL & DBG_KNXCLOCK) != 0
  Debug.println(F("KNXCLock::SetClock to %u"), posix);
  #endif
  uint32_t curr_micros = a_micros;

  // if the clock has not been received any sync before, a new correction factor cannot be calculated, so stay with inital value
  if(m_clock_sync != 0)
  {
    uint32_t diff_micros = calculateElapsedMillis(m_clock_sync_micros, curr_micros);
    uint32_t diff_posix = posix - m_clock_sync;
    m_clock_correction = (diff_posix * 1000000.0) / diff_micros;

    #if (DBGLVL & DBG_KNXCLOCK) != 0
    Debug.println(F("KNXCLock::SetClock new correction %.10f"), m_clock_correction);
    Debug.println(F("KNXCLock::SetClock diff_posix %u"), diff_posix);
    Debug.println(F("KNXCLock::SetClock diff_micros %u"), diff_micros);
    #endif
  }
  
  m_clock_sync = posix;
  m_clock = posix;
  m_clock_sync_micros = curr_micros;
  m_clock_micros = curr_micros;

  return m_clock_correction;
}