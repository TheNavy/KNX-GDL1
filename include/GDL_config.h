// ################################################
// ### IO Configuration
// ################################################

#define SENS_UP_PIN 6
#define SENS_DOWN_PIN 7

//pin definitions for the ItsyBitsy M0 Dotstar LED
#define DATAPIN    41
#define CLOCKPIN   40
#define NUMPIXELS   1

// ################################################
// ### Door Configuration
// ################################################

#define doorMoveTime  15000 //Maximum Time the Door needs
#define doorDeadTime  2000 //Time between Motor starts & Sensor recognised
#define doorMotorDeadTime  60000 //Dead time after one move
#define doorOpenLight 300000 //Open Light how long

// ################################################
// ### KONNEKTING Configuration
// ################################################

#define SerialUSB Serial //USB