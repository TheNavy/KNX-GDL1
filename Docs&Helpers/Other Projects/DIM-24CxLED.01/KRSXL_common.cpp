#include "KRSXL_common.h"


KRSXL_common::KRSXL_common()
{
  // Tempsens
  OneWire *oneWire = new OneWire(TEMPSENS);
  m_ds18b20 = DallasTemperature((oneWire));
}

void KRSXL_common::Setup()
{
  #if (DBGLVL & DBG_KRSXL_COMMON) != 0
  Debug.println("KRSXL_common::Setup");
  #endif

  // LEDs
  pinMode(ERROR_LED_PIN, OUTPUT);
  
  // Display
  m_tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
  m_tft->begin();
  m_tft->fillScreen(ILI9341_BLACK);
  m_tft->setRotation(3);
  m_tft->setCursor(10, 10);
  m_tft->setTextColor(ILI9341_RED);
  m_tft->setTextSize(5);
  m_tft->println("KRS-XL");  

  pinMode(TFT_LED, OUTPUT);
  analogWrite(TFT_LED, m_tft_brightness);

  displayOff(); // ToDo

  // Tempsens
  m_ds18b20.begin();
  m_ds18b20.getAddress(m_ds18b20_adr, 0);
  m_ds18b20.setResolution(m_ds18b20_adr, DS18B20_RESOLUTION);
  m_ds18b20.setWaitForConversion(false);
  m_ds18b20.requestTemperatures();
  m_ds18b20_delay = 750 / (1 << (12 - DS18B20_RESOLUTION)); 
  m_ds18b20_lastrequest = millis();
  
}

void KRSXL_common::KnxEvent(byte index)
{
  
}

int KRSXL_common::Cyclic_500()
{
  #if (DBGLVL & DBG_KRSXL_COMMON) != 0
  //Debug.println(F("KRSXL_common::Cyclic_500"));
  #endif

  int returnval = 0;

  // LEDs
  if(BETA)
  {
    m_toggle_error_led = !m_toggle_error_led;
    digitalWrite(ERROR_LED_PIN, m_toggle_error_led);
  }

  // Tempsens
  if (millis() - m_ds18b20_lastrequest >= m_ds18b20_delay) // waited long enough??
  {

    float temperature = m_ds18b20.getTempCByIndex(0);
    m_ds18b20.requestTemperatures();
    
    m_ds18b20_delay = 750 / (1 << (12 - DS18B20_RESOLUTION)); 
    m_ds18b20_lastrequest = millis(); 

    Knx.write(COMOBJ_gen_casetemp, temperature);

    #if (DBGLVL & DBG_KRSXL_COMMON) != 0
    //Debug.println(F("Temp %f"),temperature);
    #endif

    if(temperature >= m_max_casetemp)
    {
      m_tempwarn_cnt++;
      if(m_tempwarn_cnt >= m_tempwarn_cnt_threshold)
      {
        Knx.write(COMOBJ_gen_temp_alarm, 1);

        returnval |= 0x01;
      }
    }
    else
    {
      m_tempwarn_cnt = 0;
    }
  }

  return returnval;
}

void KRSXL_common::displayOff()
{
  #if (DBGLVL & DBG_KRSXL_COMMON) != 0
  Debug.println("KRSXL_common::displayOff");
  #endif

  analogWrite(TFT_LED, 0);
  m_tft->startWrite();
  m_tft->writeCommand(ILI9341_SLPIN);
  delay(120);
  m_tft->writeCommand(ILI9341_DISPOFF);
  delay(120);
  m_tft->endWrite();
  
}

void KRSXL_common::displayOn()
{
  #if (DBGLVL & DBG_KRSXL_COMMON) != 0
  Debug.println("KRSXL_common::displayOn");
  #endif

  m_tft->startWrite();
  m_tft->writeCommand(ILI9341_SLPOUT);
  delay(120);
  m_tft->writeCommand(ILI9341_DISPON);
  delay(120);
  m_tft->endWrite();
  analogWrite(TFT_LED, m_tft_brightness);
}