
// Developed/Tested with
//
// Library Versions:
//
// KONNEKTING_Device_Library
// Adafruit Dotstar
// Adafruit SPIFlash
// Adafruit Zero DMA
// Adafruit DMA neopixel
// Adafruit NeoPixel
// Boardmanager Arduino SAMD Boards
// Boardmanager Adafruit SAMD Boards

/* DotStar RBG LED Color definitions

red:    Waiting for establishing Debug Connection USB-Serial
blue:   FactoryMode - Programm with Konnekting Suite
green:  Normal Mode
cyan:   Normal Mode with Serial Debug
*/

// Include used Librarys
#include <KonnektingDevice.h>
#include <Adafruit_DotStar.h>
#include <Adafruit_NeoPixel_ZeroDMA.h>

// own classes
#include "FileAsEEPROM.h"

//configuration
#include "config.h"

// include device related configuration code, created by "KONNEKTING CodeGenerator"
//#include "kdevice_DemoSketch.h"

// ################################################
// ### Global variables, sketch related
// ################################################

//Dotstar LED
Adafruit_DotStar px(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

// ################################################
// ### KONNEKTING Configuration
// ################################################

//FlashStorage
byte readMemory(int index)
{
  #if (DBGLVL & DBG_FLASHSTORAGE) != 0
  Debug.println(F("FLASH read on index %d"),index);
  #endif

  return FileEEPROM.read(index);
}
void writeMemory(int index, byte val)
{
  #if (DBGLVL & DBG_FLASHSTORAGE) != 0
  Debug.println(F("FLASH write value %d on index %d"),val, index);
  #endif

  FileEEPROM.write(index, val);
}
void updateMemory(int index, byte val)
{
  #if (DBGLVL & DBG_FLASHSTORAGE) != 0
  Debug.println(F("FLASH update"));
  #endif

  if (FileEEPROM.read(index) != val)
  {
    FileEEPROM.write(index, val);
  }
}
void commitMemory()
{
  #if (DBGLVL & DBG_FLASHSTORAGE) != 0
  Debug.println(F("FLASH commit"));
  #endif

  FileEEPROM.commit();
}

// ################################################
// ### set ProgLED status
// ################################################
//this function is used to indicate programming mode.
//you can use LED, LCD display or what ever you want...
void progLed(bool state)
{
    digitalWrite(PROG_LED_PIN, state);
}

void setup() {
  // DotStar LED Initialize
  px.begin(); // Initialize pins for output
  px.show();  // Turn all LEDs off ASAP
  px.setPixelColor(0, 50, 0, 0); // red
  px.show();

  // debug related stuff
#ifdef KDEBUG

    // Start debug serial
    DEBUGSERIAL.begin(9600);

#ifdef __AVR_ATmega32U4__
    // wait for serial port to connect. Needed for Leonardo/Micro/ProMicro only
    while (!DEBUGSERIAL)
#endif

#ifdef __SAMD21G18A__
    // wait for serial port to connect. Needed for SAMD21G18A
    while (!DEBUGSERIAL)
#endif

    // make debug serial port known to debug class
    // Means: KONNEKTING will sue the same serial port for console debugging
    Debug.setPrintStream(&DEBUGSERIAL);
#endif

  if (!Konnekting.isFactorySetting())
  {

    #ifdef KDEBUG
    px.setPixelColor(0, 63, 136, 143); // cyan
    #else
    px.setPixelColor(0, 0, 50, 0); // green
    #endif
    px.show();

  }
  else
  {
    #if (DBGLVL & DBG_MAIN) != 0
    Debug.println(F("Device is in factory mode. Starting programming mode..."));
    #endif
    px.setPixelColor(0, 0, 0, 50); // blue
    px.show();
    Konnekting.setProgState(true);
  }

  #if (DBGLVL & DBG_MAIN) != 0
  Debug.println(F("Setup is ready. go to loop..."));
  #endif

}

void loop() {
  // put your main code here, to run repeatedly:

}
