//DPT3.007 stuff
#define DPT3_007_MASK_DIRECTION B1000
#define DPT3_007_INCREASE       B1000
#define DPT3_007_DECREASE       B0000
#define DPT3_007_MASK_STEP      B0111
#define DPT3_007_STOP           B0000



//Scene 1 .. 9
#define ALL_OFF 0x00  //1
#define WHITE 0x01    //2
#define RED 0x02      //3
#define YELLOW 0x03   //4
#define GREEN 0x04    //5
#define CYAN 0x05     //6
#define BLUE 0x06     //7
#define PURPLE 0x07   //8
#define ORANGE 0x08   //9

//Scenes 21 .. 25
#define USER_COLOR_1 0x14 //21
#define USER_COLOR_2 0x15 //22
#define USER_COLOR_3 0x16 //23
#define USER_COLOR_4 0x17 //24
#define USER_COLOR_5 0x18 //25

//Scenes 41 .. 52
#define RAINBOW 0x28              //41
#define SINGLERGB 0x29            //42
#define SPARKLER 0x2A             //43
#define TWINKYSTARS 0x2B          //44
#define CHASER 0x2C               //45
#define HUEFADER 0x2D             //46
#define SPEEDTRAILS 0x2E          //47
#define BOUNCYBALLS 0x2F          //48
#define TWOBRUSHCOLORMIXING 0x30  //49

#define WHIREMIDDLEON 0x32        //51
#define WHIREMIDDLEOFF 0x33       //52

//Scene 61 .. 64
#define TASK_RGB 0x3C
#define TASK_RGBW 0x3D
#define TASK_HSV 0x3E
#define TASK_DIMMER 0x3F

#define TASK_IDLE 0xFE

#define USERCOLORS 5
#define R 0
#define G 1
#define B 2
#define W 3

#define DEBOUNCE 80 //ms

#define M_OFF       0
#define M_OFF_WAIT  2
#define M_ON        1
#define M_ON_WAIT   3
