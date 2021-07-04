// ################################################
// ### DEBUG CONFIGURATION
// ################################################
#define KDEBUG // comment this line to disable DEBUG mode
#ifdef KDEBUG
#include <DebugUtil.h>
#endif

// ################################################
// ### KONNEKTING Configuration
// ################################################

// SAMD21 / ItsyBitsy M0
#define KNX_SERIAL Serial1
#define DEBUGSERIAL Serial //(USB)

//pin definitions for the ItsyBitsy M0 Dotstar LED
#define DATAPIN    41
#define CLOCKPIN   40
#define NUMPIXELS   1


// ################################################
// ### IO Configuration
// ################################################

// SAMD21
#define PROG_LED_PIN A4
#define ERROR_LED_PIN 10

// Konnekting XML

#define MANUFACTURER_ID 7337
#define DEVICE_ID 100
#define REVISION 0
