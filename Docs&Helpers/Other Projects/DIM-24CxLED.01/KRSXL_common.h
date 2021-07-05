#pragma once


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include <OneWire.h> 
#include <DallasTemperature.h>

#include "config.h"
#include <KonnektingDevice.h>


/*
// functions
- read case temp and send it, also alarm and shutdown
- errorcode handling
- display
- buttons
- time
- busspannungsausfall

*/


class KRSXL_common
{
  
	private: Adafruit_ILI9341 *m_tft;
  
  private: DallasTemperature m_ds18b20;
  private: DeviceAddress m_ds18b20_adr;
  private: uint16_t m_ds18b20_delay;
  private: uint32_t m_ds18b20_lastrequest;
  private: uint8_t m_tft_brightness = 80;
  private: uint8_t m_max_casetemp = 60;
  private: uint8_t m_tempwarn_cnt = 0;
  private: uint8_t m_tempwarn_cnt_threshold = 3;

  private: bool m_toggle_error_led = false;

  //constructors
  public: KRSXL_common();

	public: int Cyclic_500();

  public: void Setup();

  public: void KnxEvent(byte index);

  public: void displayOff();

  public: void displayOn();
  
};