/*
DIM-24CxLED.01 24channel PWM LED Dimmer
V0.0.3
*/

/*
Changelog:
  V0.0.3
    - added Knx.Write at dimmchannel_1ch when fading
    - added Knx.Write at dimmchannel_rgb when fading and setting value


/*
Sprint 2
- neue Parameter und KOs unterstützen 
  - daynight knx.update -- DONE

  - treppenlicht zeit (bei jeder "Aktion" wird der "last_action" Wert gesetzt, im Cyclic wird geprüft ob abgelaufen und ggf. ausgeschaltet )
      1ch DONE
      RGB DONE

  - Switch on und off at dimm neuer param
      => 1ch/RGB Konstruktor angepasst, neue member angelegt, funktion fehlt noch
      => 1ch DONE (Dimm umgesetzt, DimmRel geht über Dimm)
      => RGB DONE

  - einschaltwert (letzter, fest tag/nacht
      => 1ch DONE
      => RGB DONE

  - Sperrobjekt / Rückfallzeit Sperrobjekt
    => 1ch DONE
    => RGB DONE

  - Szenen
    stub im knxevent

  - 8-Bit Animationen (1-3 einfache Beispielanimationen)
    => struktur vorhanden, 3 Beispielanimationen vorhanden: DONE
    

Sprint 3
- user interface (buttons und tft)


Backlog
- 32bit anminationen (color, speed)

- busspannungsausfall detektieren und werte wegspeichern / wiederherstellen

- make eeprom function cpu specific

- korrekter DPT 18.001 statt 17.001 für szenen

- RGB fading alle kanäle gleich lang

- zentralobjekte (ggf. mehrere "sets", zuordnung zu den selben über bitmasken)

- FadeTime unterschiedlich für Switch, Dimm und DimmRel mit raw-Parameter

- irgendwas mit der Uhrzeit anfangen (update datetime in knxclock)

- min-max wert dimm als Parameter

- Netzteil(e) abschalten zuordnung der kanäle zu einem Netzteil 1..n über bitmasken
  KOs zum schalten der Netzteile an einem Aktor
  Paramter für Abschaltzeit etc...

- Load Balancing / Phase shifting in einer Netzteilgruppe
  Last pro Kanal als Parameter ggf als sammelparameter



*/



// Developed/Tested with
//
// Library Versions:
//
// KONNEKTING_Device_Library: 1.0.0-BETA4b_mod
// Adafriut_Dotstar: 1.1.2
// Adafriut_SPIFlash: 1.0.8 / 1.1.0
//
// Other Versions:
// Arduino IDE: 1.8.8
// Boardmanager Arduino SAMD Boards: 1.8.3
// Boardmanager Adafruit SAMD Boards: 1.5.3

/* DotStar RBG LED Color definitions

red:    Waiting for establishing Debug Connection USB-Serial
blue:   FactoryMode - Programm with Konnekting Suite
green:  Normal Mode
cyan:   Normal Mode with Serial Debug
*/



// external libs
#include <KonnektingDevice.h>
#include <Adafruit_DotStar.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Wire.h>
#include "PCA9685.h"

// own classes
#include "FileAsEEPROM.h"
#include "timeslice.h"
#include "DimmChannel.h"
#include "Dimmer.h"
#include "KRSXL_common.h"
#include "KNXClock.h"


// include device related configuration code, created by "KONNEKTING CodeGenerator"
#include "kdevice_dim24.h"

//configuration
#include "config.h"




// ################################################
// ### Global variables, sketch related
// ################################################

// this array defines which PWM channel is used for the KNX-channels (A..X)
// a number < 100 will be matched to the corresponding arduino-pinMode
// a number > 100 will be matched to a PCA9685 channel e.g. 100 is channel 0 on PCA9685 controller 0. 123 is channel 7 in controller 1.
const uint8_t outpins[NO_OF_CHANNELS] = {OUTPIN_A, OUTPIN_B, OUTPIN_C, OUTPIN_D, OUTPIN_E, OUTPIN_F, OUTPIN_G, OUTPIN_H, OUTPIN_I, OUTPIN_J, OUTPIN_K, OUTPIN_L, OUTPIN_M, OUTPIN_N, OUTPIN_O, OUTPIN_P, OUTPIN_Q, OUTPIN_R, OUTPIN_S, OUTPIN_T, OUTPIN_U, OUTPIN_V, OUTPIN_W, OUTPIN_X};


Dimmer dimmer(outpins);
KRSXL_common common;
KNXCLock knxclock(COMOBJ_gen_datetime);

//Dotstar LED
Adafruit_DotStar px(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

//ErrorCode
uint32_t g_ErrorCode = 0;


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



// ################################################
// ### KNX EVENT CALLBACK
// ################################################
void knxEvents(byte index)
{
  dimmer.KnxEvent(index);
  knxclock.KnxEvent(index);
}




// ################################################
// ### SETUP
// ################################################

void setup()
{  
  px.begin(); // Initialize pins for output
  px.show();  // Turn all LEDs off ASAP
  px.setPixelColor(0, 50, 0, 0); // red
  px.show();

  // debug related stuff
#ifdef KDEBUG

    // Start debug serial
    DEBUGSERIAL.begin(115200);

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

  Konnekting.setMemoryReadFunc(&readMemory);
  Konnekting.setMemoryWriteFunc(&writeMemory);
  Konnekting.setMemoryUpdateFunc(&updateMemory);
  Konnekting.setMemoryCommitFunc(&commitMemory);

  HardwareChannel_mega8::Setup(outpins);
  HardwareChannel_pca9685::Setup(outpins);

  common.Setup();
  
  // Initialize KNX enabled Arduino Board
  Konnekting.init(KNX_SERIAL,
                    &progLed,
                    MANUFACTURER_ID,
                    DEVICE_ID,
                    REVISION);

  /*
  pinMode(PROG_BUTTON_PIN, INPUT_PULLUP);
  if(!digitalRead(PROG_BUTTON_PIN))
  {
    Debug.println(F("Jumper set to ProgMode. Starting programming mode..."));
    Konnekting.setProgState(true);
  }
  */


  if (!Konnekting.isFactorySetting())
  {
    dimmer.Setup(outpins);
    knxclock.Setup();

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
  timeslice_setup();

  #if (DBGLVL & DBG_MAIN) != 0
  Debug.println(F("Setup is ready. go to loop..."));
  #endif
}








// ################################################
// ### LOOP
// ################################################
void loop()
{
    Knx.task();
    // only do application stuff if not in programming mode
    if (Konnekting.isReadyForApplication())
    {
      timeslice_scheduler();
      dimmer.CyclicMax();
    }
}

void T1() // 1ms
{
}

void T2() // 5ms
{
}

void T3() // 25ms
{
  dimmer.Cyclic();
}

void T4() // 500ms
{
  int check = HardwareChannel_pca9685::CheckConnection(outpins);
  // 0 = all good
  // 1 = PCA9685 gone away
  // 2 = PCA9685 i2cerror after Re-Setup
  // 3 = Re-Setup successfull, do refresh
  if(check)
  {
    uint32_t old_error = g_ErrorCode;
    if(check == 3)
    { 
      dimmer.Refresh();
      SetErrorCode(ERRORCODE_PCASTATUS_GOOD, ERRORCODE_PCASTATUS_MASK);
    }
    else
    {
      SetErrorCode(ERRORCODE_PCASTATUS_ERR, ERRORCODE_PCASTATUS_MASK);
    }

    if(old_error != g_ErrorCode)
      Knx.write(COMOBJ_error_code, g_ErrorCode);
  }

  int common_cyclic500_returnvalue = common.Cyclic_500();
  if(common_cyclic500_returnvalue & 0x01)
  {
    dimmer.Shutdown();
  }
}

void T5() // 10000ms
{
  #if (DBGLVL & DBG_MAIN) != 0
  Debug.println(F("T5"));
  #endif

  if(g_ErrorCode || BETA) // send only when != 0 OR when BETA
  {
    Knx.write(COMOBJ_error_code, g_ErrorCode);
  }
}



// ################################################
// ### HELPER FUNCTIONS
// ################################################


void SetErrorCode(uint32_t ErrorBits, uint32_t Mask)
{
  g_ErrorCode &= ~Mask; // Bits löschen
  g_ErrorCode |= ErrorBits;
}