// ################################################
// ### DEBUG CONFIGURATION
// ################################################
#define KDEBUG // comment this line to disable DEBUG mode
#ifdef KDEBUG
#include "src/KonnektingDeviceLibrary/DebugUtil.h"
#endif

// ################################################
// ### KONNEKTING Configuration
// ################################################

// SAMD21 / ItsyBitsy M0
#define SerialKNX Serial1
#define DEBUGSERIAL Serial //(USB)

// ################################################
// ### IO Configuration
// ################################################

// SAMD21
#define PROG_LED_PIN 13
#define PROG_BUTTON_PIN 7
#define LED_STRIP_PIN 5
#define POWER_SUPPLY_PIN 4 //active low
#define SENS_UP_PIN 9
#define SENS_DOWN_PIN 10

//pin definitions for the ItsyBitsy M0 Dotstar LED
#define DATAPIN    41
#define CLOCKPIN   40
#define NUMPIXELS   1
