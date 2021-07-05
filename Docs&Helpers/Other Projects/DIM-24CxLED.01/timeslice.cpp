#include "timeslice.h"

unsigned long T1_last_run = 0;
unsigned long T2_last_run = 0;
unsigned long T3_last_run = 0;
unsigned long T4_last_run = 0;
unsigned long T5_last_run = 0;

unsigned int T1_duration = 0;
unsigned int T2_duration = 0;
unsigned int T3_duration = 0;
unsigned int T4_duration = 0;
unsigned int T5_duration = 0;

unsigned int T1_overtime = 0;
unsigned int T2_overtime = 0;
unsigned int T3_overtime = 0;
unsigned int T4_overtime = 0;
unsigned int T5_overtime = 0;

void timeslice_setup()
{
  T1_last_run = T2_last_run = T3_last_run = T4_last_run = T5_last_run = millis();  // start well-defined into the time slices.. (init can take long)
}

void timeslice_scheduler()
{
  unsigned long currentMillis = millis();
  
  if(calculateElapsedMillis(T1_last_run, currentMillis) >= T1_CYCLETIME)
  {
    T1_overtime = calculateElapsedMillis(T1_last_run, currentMillis) - T1_CYCLETIME;
    T1_last_run = currentMillis;
    T1();
    T1_duration = calculateElapsedMillis(currentMillis, millis());
  }
  else if(calculateElapsedMillis(T2_last_run, currentMillis) >= T2_CYCLETIME)
  {
    T2_overtime = calculateElapsedMillis(T2_last_run, currentMillis) - T2_CYCLETIME;
    T2_last_run = currentMillis;
    T2();
    T2_duration = calculateElapsedMillis(currentMillis, millis());
  }
  else if(calculateElapsedMillis(T3_last_run, currentMillis) >= T3_CYCLETIME)
  {
    T3_overtime = calculateElapsedMillis(T3_last_run, currentMillis) - T3_CYCLETIME;
    T3_last_run = currentMillis;
    T3();
    T3_duration = calculateElapsedMillis(currentMillis, millis());
  }
  else if(calculateElapsedMillis(T4_last_run, currentMillis) >= T4_CYCLETIME)
  {
    T4_overtime = calculateElapsedMillis(T4_last_run, currentMillis) - T4_CYCLETIME;
    T4_last_run = currentMillis;
    T4();
    T4_duration = calculateElapsedMillis(currentMillis, millis());
  }
  else if(calculateElapsedMillis(T5_last_run, currentMillis) >= T5_CYCLETIME)
  {
    T5_overtime = calculateElapsedMillis(T5_last_run, currentMillis) - T5_CYCLETIME;
    T5_last_run = currentMillis;
    T5();
    T5_duration = calculateElapsedMillis(currentMillis, millis());
  }
}


unsigned long calculateElapsedMillis(unsigned long lastrunMillis, unsigned long currentMillis)
{
  if(currentMillis >= lastrunMillis)
    return currentMillis-lastrunMillis;
  else // this means, there was an overflow
    return (0xFFFFFFFF-lastrunMillis)+currentMillis;
}
