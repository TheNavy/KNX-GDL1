// ################################################
// ### DEBUG CONFIGURATION
// ################################################
//#define KDEBUG // comment this line to disable DEBUG mode
#ifdef KDEBUG
#include <DebugUtil.h>
#endif

#define DBG_MAIN 1
#define DBG_TIMESLICE 2
#define DBG_KRSXL_COMMON 4
#define DBG_KNXCLOCK 8
#define DBG_DIMMER 16
#define DBG_DIMMCHANNEL 32
#define DBG_HWCHANNEL 64
#define DBG_FLASHSTORAGE 128

//#define DBGLVL  DBG_MAIN | DBG_DIMMCHANNEL | DBG_KNXCLOCK | DBG_KRSXL_COMMON
#define DBGLVL  (DBG_MAIN | DBG_DIMMCHANNEL)

//
#define BETA 1
//define BETA 0

#define ERRORCODE_PCASTATUS_MASK   0x00000003
#define ERRORCODE_PCASTATUS_GOOD    0x00000000
#define ERRORCODE_PCASTATUS_GONE    0x00000001
#define ERRORCODE_PCASTATUS_ERR     0x00000002


// ################################################
// ### KONNEKTING Configuration
// ################################################
/*
// Nano & Pro Mini
#include <SoftwareSerial.h>
SoftwareSerial softserial(6, 7); // RX, TX
#define DEBUGSERIAL softserial
#define KNX_SERIAL Serial
*/

/*
// Micro & Pro Micro
#define DEBUGSERIAL Serial
#define KNX_SERIAL Serial1 // Leonardo/Micro etc. use Serial1
*/

/*
// Mega2560
#define KNX_SERIAL Serial2
#define DEBUGSERIAL Serial //(USB)
*/

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
/*
// Micro
#define PROG_LED_PIN 13 //(32/PC7/D13)
#define PROG_BUTTON_PIN 2 //(19/PD1/D2)
#define OUTPIN_A 9 //(29/PB5/D9)
#define OUTPIN_B 10 //(30/PB6/D10)
#define OUTPIN_C 11 //(12/PB7/D11)
#define OUTPIN_D 5 //(31/PC6/D5)
*/

/*
// ProMicro
#define PROG_LED_PIN 3 //(/P/D3)
#define PROG_BUTTON_PIN 2 //(19/PD1/D2)
#define OUTPIN_A 9 //(29/PB5/D9)
#define OUTPIN_B 10 //(30/PB6/D10)
#define OUTPIN_C 11 //(12/PB7/D11)
#define OUTPIN_D 5 //(31/PC6/D5)
*/

/*
// Mega 2560
#define PROG_LED_PIN 4      //(1/PG5)
#define PROG_BUTTON_PIN 18  //(46/PD3)

#define OUTPIN_A 2
#define OUTPIN_B 46
#define OUTPIN_C 45
#define OUTPIN_D 44
#define OUTPIN_E 3
#define OUTPIN_F 13
#define OUTPIN_G 12
#define OUTPIN_H 11
#define OUTPIN_I 8
#define OUTPIN_J 7
#define OUTPIN_K 6
#define OUTPIN_L 5

#define OCR_A OCR3B
#define OCR_B OCR5A
#define OCR_C OCR5B
#define OCR_D OCR5C
#define OCR_E OCR3C
#define OCR_F OCR1C
#define OCR_G OCR1B
#define OCR_H OCR1A
#define OCR_I OCR4C
#define OCR_J OCR4B
#define OCR_K OCR4A
#define OCR_L OCR3A

#define TCCR_A TCCR3A
#define TCCR_B TCCR5A
#define TCCR_C TCCR5A
#define TCCR_D TCCR5A
#define TCCR_E TCCR3A
#define TCCR_F TCCR1A
#define TCCR_G TCCR1A
#define TCCR_H TCCR1A
#define TCCR_I TCCR4A
#define TCCR_J TCCR4A
#define TCCR_K TCCR4A
#define TCCR_L TCCR3A

#define COM_A COM3B1
#define COM_B COM5A1
#define COM_C COM5B1
#define COM_D COM5C1
#define COM_E COM3C1
#define COM_F COM1C1
#define COM_G COM1B1
#define COM_H COM1A1
#define COM_I COM4C1
#define COM_J COM4B1
#define COM_K COM4A1
#define COM_L COM3A1
*/

// SAMD21
#define PROG_LED_PIN A4
#define ERROR_LED_PIN 10


#define TFT_DC 2
#define TFT_CS 4
#define TFT_RST A5
#define TFT_LED 3

#define BUTTON_SW1 12
#define BUTTON_SW2 9
#define BUTTON_SW3 7
#define BUTTON_SW4 5

#define TEMPSENS A3
#define DS18B20_RESOLUTION 9

#define OUTPIN_A 115
#define OUTPIN_B 114
#define OUTPIN_C 113
#define OUTPIN_D 112
#define OUTPIN_E 111
#define OUTPIN_F 110
#define OUTPIN_G 109
#define OUTPIN_H 108
#define OUTPIN_I 100
#define OUTPIN_J 101
#define OUTPIN_K 102
#define OUTPIN_L 103
#define OUTPIN_M 107
#define OUTPIN_N 106
#define OUTPIN_O 105
#define OUTPIN_P 104
#define OUTPIN_Q 116
#define OUTPIN_R 117
#define OUTPIN_S 118
#define OUTPIN_T 119
#define OUTPIN_U 123
#define OUTPIN_V 122
#define OUTPIN_W 121
#define OUTPIN_X 120





// dont change here, this will result in broken code
#define KO_PER_CHANNEL 7
#define KO_PER_RGB_CHANNEL 7
#define PARAMS_PER_CHANNEL 6
#define PARAMS_PER_RGB_CHANNEL 6

#define COMOBJ_CH_X_SW 0
#define COMOBJ_CH_X_DIM 1
#define COMOBJ_CH_X_DIMREL 2
#define COMOBJ_CH_X_ANIMATION 2
#define COMOBJ_CH_X_LOCK 3
#define COMOBJ_CH_X_SCENE 4
#define COMOBJ_CH_X_STAT_SW 5
#define COMOBJ_CH_X_STAT_DIM 6


// ToDo More Channels
// Change here if you change the number of the channels
#define NO_OF_CHANNELS 24
#define NO_OF_RGB_CHANNELS (NO_OF_CHANNELS/4)
#define NO_OF_ALL_CHANNELS (NO_OF_CHANNELS+NO_OF_RGB_CHANNELS)

#define NO_OF_PCA9685 2


// Konnekting XML

#define MANUFACTURER_ID 7337
#define DEVICE_ID 100
#define REVISION 0

#define COMOBJ_ch_A_sw 0
#define COMOBJ_ch_A_dim 1
#define COMOBJ_ch_A_dimrel 2
#define COMOBJ_ch_A_lock 3
#define COMOBJ_ch_A_scene 4
#define COMOBJ_ch_A_stat_sw 5
#define COMOBJ_ch_A_stat_dim 6
#define COMOBJ_ch_B_sw 7
#define COMOBJ_ch_B_dim 8
#define COMOBJ_ch_B_dimrel 9
#define COMOBJ_ch_B_lock 10
#define COMOBJ_ch_B_scene 11
#define COMOBJ_ch_B_stat_sw 12
#define COMOBJ_ch_B_stat_dim 13
#define COMOBJ_ch_C_sw 14
#define COMOBJ_ch_C_dim 15
#define COMOBJ_ch_C_dimrel 16
#define COMOBJ_ch_C_lock 17
#define COMOBJ_ch_C_scene 18
#define COMOBJ_ch_C_stat_sw 19
#define COMOBJ_ch_C_stat_dim 20
#define COMOBJ_ch_D_sw 21
#define COMOBJ_ch_D_dim 22
#define COMOBJ_ch_D_dimrel 23
#define COMOBJ_ch_D_lock 24
#define COMOBJ_ch_D_scene 25
#define COMOBJ_ch_D_stat_sw 26
#define COMOBJ_ch_D_stat_dim 27
#define COMOBJ_ch_E_sw 28
#define COMOBJ_ch_E_dim 29
#define COMOBJ_ch_E_dimrel 30
#define COMOBJ_ch_E_lock 31
#define COMOBJ_ch_E_scene 32
#define COMOBJ_ch_E_stat_sw 33
#define COMOBJ_ch_E_stat_dim 34
#define COMOBJ_ch_F_sw 35
#define COMOBJ_ch_F_dim 36
#define COMOBJ_ch_F_dimrel 37
#define COMOBJ_ch_F_lock 38
#define COMOBJ_ch_F_scene 39
#define COMOBJ_ch_F_stat_sw 40
#define COMOBJ_ch_F_stat_dim 41
#define COMOBJ_ch_G_sw 42
#define COMOBJ_ch_G_dim 43
#define COMOBJ_ch_G_dimrel 44
#define COMOBJ_ch_G_lock 45
#define COMOBJ_ch_G_scene 46
#define COMOBJ_ch_G_stat_sw 47
#define COMOBJ_ch_G_stat_dim 48
#define COMOBJ_ch_H_sw 49
#define COMOBJ_ch_H_dim 50
#define COMOBJ_ch_H_dimrel 51
#define COMOBJ_ch_H_lock 52
#define COMOBJ_ch_H_scene 53
#define COMOBJ_ch_H_stat_sw 54
#define COMOBJ_ch_H_stat_dim 55
#define COMOBJ_ch_I_sw 56
#define COMOBJ_ch_I_dim 57
#define COMOBJ_ch_I_dimrel 58
#define COMOBJ_ch_I_lock 59
#define COMOBJ_ch_I_scene 60
#define COMOBJ_ch_I_stat_sw 61
#define COMOBJ_ch_I_stat_dim 62
#define COMOBJ_ch_J_sw 63
#define COMOBJ_ch_J_dim 64
#define COMOBJ_ch_J_dimrel 65
#define COMOBJ_ch_J_lock 66
#define COMOBJ_ch_J_scene 67
#define COMOBJ_ch_J_stat_sw 68
#define COMOBJ_ch_J_stat_dim 69
#define COMOBJ_ch_K_sw 70
#define COMOBJ_ch_K_dim 71
#define COMOBJ_ch_K_dimrel 72
#define COMOBJ_ch_K_lock 73
#define COMOBJ_ch_K_scene 74
#define COMOBJ_ch_K_stat_sw 75
#define COMOBJ_ch_K_stat_dim 76
#define COMOBJ_ch_L_sw 77
#define COMOBJ_ch_L_dim 78
#define COMOBJ_ch_L_dimrel 79
#define COMOBJ_ch_L_lock 80
#define COMOBJ_ch_L_scene 81
#define COMOBJ_ch_L_stat_sw 82
#define COMOBJ_ch_L_stat_dim 83
#define COMOBJ_ch_M_sw 84
#define COMOBJ_ch_M_dim 85
#define COMOBJ_ch_M_dimrel 86
#define COMOBJ_ch_M_lock 87
#define COMOBJ_ch_M_scene 88
#define COMOBJ_ch_M_stat_sw 89
#define COMOBJ_ch_M_stat_dim 90
#define COMOBJ_ch_N_sw 91
#define COMOBJ_ch_N_dim 92
#define COMOBJ_ch_N_dimrel 93
#define COMOBJ_ch_N_lock 94
#define COMOBJ_ch_N_scene 95
#define COMOBJ_ch_N_stat_sw 96
#define COMOBJ_ch_N_stat_dim 97
#define COMOBJ_ch_O_sw 98
#define COMOBJ_ch_O_dim 99
#define COMOBJ_ch_O_dimrel 100
#define COMOBJ_ch_O_lock 101
#define COMOBJ_ch_O_scene 102
#define COMOBJ_ch_O_stat_sw 103
#define COMOBJ_ch_O_stat_dim 104
#define COMOBJ_ch_P_sw 105
#define COMOBJ_ch_P_dim 106
#define COMOBJ_ch_P_dimrel 107
#define COMOBJ_ch_P_lock 108
#define COMOBJ_ch_P_scene 109
#define COMOBJ_ch_P_stat_sw 110
#define COMOBJ_ch_P_stat_dim 111
#define COMOBJ_ch_Q_sw 112
#define COMOBJ_ch_Q_dim 113
#define COMOBJ_ch_Q_dimrel 114
#define COMOBJ_ch_Q_lock 115
#define COMOBJ_ch_Q_scene 116
#define COMOBJ_ch_Q_stat_sw 117
#define COMOBJ_ch_Q_stat_dim 118
#define COMOBJ_ch_R_sw 119
#define COMOBJ_ch_R_dim 120
#define COMOBJ_ch_R_dimrel 121
#define COMOBJ_ch_R_lock 122
#define COMOBJ_ch_R_scene 123
#define COMOBJ_ch_R_stat_sw 124
#define COMOBJ_ch_R_stat_dim 125
#define COMOBJ_ch_S_sw 126
#define COMOBJ_ch_S_dim 127
#define COMOBJ_ch_S_dimrel 128
#define COMOBJ_ch_S_lock 129
#define COMOBJ_ch_S_scene 130
#define COMOBJ_ch_S_stat_sw 131
#define COMOBJ_ch_S_stat_dim 132
#define COMOBJ_ch_T_sw 133
#define COMOBJ_ch_T_dim 134
#define COMOBJ_ch_T_dimrel 135
#define COMOBJ_ch_T_lock 136
#define COMOBJ_ch_T_scene 137
#define COMOBJ_ch_T_stat_sw 138
#define COMOBJ_ch_T_stat_dim 139
#define COMOBJ_ch_U_sw 140
#define COMOBJ_ch_U_dim 141
#define COMOBJ_ch_U_dimrel 142
#define COMOBJ_ch_U_lock 143
#define COMOBJ_ch_U_scene 144
#define COMOBJ_ch_U_stat_sw 145
#define COMOBJ_ch_U_stat_dim 146
#define COMOBJ_ch_V_sw 147
#define COMOBJ_ch_V_dim 148
#define COMOBJ_ch_V_dimrel 149
#define COMOBJ_ch_V_lock 150
#define COMOBJ_ch_V_scene 151
#define COMOBJ_ch_V_stat_sw 152
#define COMOBJ_ch_V_stat_dim 153
#define COMOBJ_ch_W_sw 154
#define COMOBJ_ch_W_dim 155
#define COMOBJ_ch_W_dimrel 156
#define COMOBJ_ch_W_lock 157
#define COMOBJ_ch_W_scene 158
#define COMOBJ_ch_W_stat_sw 159
#define COMOBJ_ch_W_stat_dim 160
#define COMOBJ_ch_X_sw 161
#define COMOBJ_ch_X_dim 162
#define COMOBJ_ch_X_dimrel 163
#define COMOBJ_ch_X_lock 164
#define COMOBJ_ch_X_scene 165
#define COMOBJ_ch_X_stat_sw 166
#define COMOBJ_ch_X_stat_dim 167
#define COMOBJ_ch_ABC_sw 168
#define COMOBJ_ch_ABC_dim 169
#define COMOBJ_ch_ABC_animation 170
#define COMOBJ_ch_ABC_lock 171
#define COMOBJ_ch_ABC_scene 172
#define COMOBJ_ch_ABC_stat_sw 173
#define COMOBJ_ch_ABC_stat_dim 174
#define COMOBJ_ch_EFG_sw 175
#define COMOBJ_ch_EFG_dim 176
#define COMOBJ_ch_EFG_animation 177
#define COMOBJ_ch_EFG_lock 178
#define COMOBJ_ch_EFG_scene 179
#define COMOBJ_ch_EFG_stat_sw 180
#define COMOBJ_ch_EFG_stat_dim 181
#define COMOBJ_ch_IJK_sw 182
#define COMOBJ_ch_IJK_dim 183
#define COMOBJ_ch_IJK_animation 184
#define COMOBJ_ch_IJK_lock 185
#define COMOBJ_ch_IJK_scene 186
#define COMOBJ_ch_IJK_stat_sw 187
#define COMOBJ_ch_IJK_stat_dim 188
#define COMOBJ_ch_MNO_sw 189
#define COMOBJ_ch_MNO_dim 190
#define COMOBJ_ch_MNO_animation 191
#define COMOBJ_ch_MNO_lock 192
#define COMOBJ_ch_MNO_scene 193
#define COMOBJ_ch_MNO_stat_sw 194
#define COMOBJ_ch_MNO_stat_dim 195
#define COMOBJ_ch_QRS_sw 196
#define COMOBJ_ch_QRS_dim 197
#define COMOBJ_ch_QRS_animation 198
#define COMOBJ_ch_QRS_lock 199
#define COMOBJ_ch_QRS_scene 200
#define COMOBJ_ch_QRS_stat_sw 201
#define COMOBJ_ch_QRS_stat_dim 202
#define COMOBJ_ch_UVW_sw 203
#define COMOBJ_ch_UVW_dim 204
#define COMOBJ_ch_UVW_animation 205
#define COMOBJ_ch_UVW_lock 206
#define COMOBJ_ch_UVW_scene 207
#define COMOBJ_ch_UVW_stat_sw 208
#define COMOBJ_ch_UVW_stat_dim 209
#define COMOBJ_gen_casetemp 210
#define COMOBJ_gen_temp_alarm 211
#define COMOBJ_gen_daynight 212
#define COMOBJ_gen_datetime 213
#define COMOBJ_error_code 214
#define PARAM_ch_ABC_mode 0
#define PARAM_ch_EFG_mode 1
#define PARAM_ch_IJK_mode 2
#define PARAM_ch_MNO_mode 3
#define PARAM_ch_QRS_mode 4
#define PARAM_ch_UVW_mode 5
#define PARAM_ch_A_sw_on_dim 6
#define PARAM_ch_A_fade_time 7
#define PARAM_ch_A_lock_mode 8
#define PARAM_ch_A_lock_time 9
#define PARAM_ch_A_autooff_time 10
#define PARAM_ch_A_switchvalues 11
#define PARAM_ch_B_sw_on_dim 12
#define PARAM_ch_B_fade_time 13
#define PARAM_ch_B_lock_mode 14
#define PARAM_ch_B_lock_time 15
#define PARAM_ch_B_autooff_time 16
#define PARAM_ch_B_switchvalues 17
#define PARAM_ch_C_sw_on_dim 18
#define PARAM_ch_C_fade_time 19
#define PARAM_ch_C_lock_mode 20
#define PARAM_ch_C_lock_time 21
#define PARAM_ch_C_autooff_time 22
#define PARAM_ch_C_switchvalues 23
#define PARAM_ch_D_sw_on_dim 24
#define PARAM_ch_D_fade_time 25
#define PARAM_ch_D_lock_mode 26
#define PARAM_ch_D_lock_time 27
#define PARAM_ch_D_autooff_time 28
#define PARAM_ch_D_switchvalues 29
#define PARAM_ch_E_sw_on_dim 30
#define PARAM_ch_E_fade_time 31
#define PARAM_ch_E_lock_mode 32
#define PARAM_ch_E_lock_time 33
#define PARAM_ch_E_autooff_time 34
#define PARAM_ch_E_switchvalues 35
#define PARAM_ch_F_sw_on_dim 36
#define PARAM_ch_F_fade_time 37
#define PARAM_ch_F_lock_mode 38
#define PARAM_ch_F_lock_time 39
#define PARAM_ch_F_autooff_time 40
#define PARAM_ch_F_switchvalues 41
#define PARAM_ch_G_sw_on_dim 42
#define PARAM_ch_G_fade_time 43
#define PARAM_ch_G_lock_mode 44
#define PARAM_ch_G_lock_time 45
#define PARAM_ch_G_autooff_time 46
#define PARAM_ch_G_switchvalues 47
#define PARAM_ch_H_sw_on_dim 48
#define PARAM_ch_H_fade_time 49
#define PARAM_ch_H_lock_mode 50
#define PARAM_ch_H_lock_time 51
#define PARAM_ch_H_autooff_time 52
#define PARAM_ch_H_switchvalues 53
#define PARAM_ch_I_sw_on_dim 54
#define PARAM_ch_I_fade_time 55
#define PARAM_ch_I_lock_mode 56
#define PARAM_ch_I_lock_time 57
#define PARAM_ch_I_autooff_time 58
#define PARAM_ch_I_switchvalues 59
#define PARAM_ch_J_sw_on_dim 60
#define PARAM_ch_J_fade_time 61
#define PARAM_ch_J_lock_mode 62
#define PARAM_ch_J_lock_time 63
#define PARAM_ch_J_autooff_time 64
#define PARAM_ch_J_switchvalues 65
#define PARAM_ch_K_sw_on_dim 66
#define PARAM_ch_K_fade_time 67
#define PARAM_ch_K_lock_mode 68
#define PARAM_ch_K_lock_time 69
#define PARAM_ch_K_autooff_time 70
#define PARAM_ch_K_switchvalues 71
#define PARAM_ch_L_sw_on_dim 72
#define PARAM_ch_L_fade_time 73
#define PARAM_ch_L_lock_mode 74
#define PARAM_ch_L_lock_time 75
#define PARAM_ch_L_autooff_time 76
#define PARAM_ch_L_switchvalues 77
#define PARAM_ch_M_sw_on_dim 78
#define PARAM_ch_M_fade_time 79
#define PARAM_ch_M_lock_mode 80
#define PARAM_ch_M_lock_time 81
#define PARAM_ch_M_autooff_time 82
#define PARAM_ch_M_switchvalues 83
#define PARAM_ch_N_sw_on_dim 84
#define PARAM_ch_N_fade_time 85
#define PARAM_ch_N_lock_mode 86
#define PARAM_ch_N_lock_time 87
#define PARAM_ch_N_autooff_time 88
#define PARAM_ch_N_switchvalues 89
#define PARAM_ch_O_sw_on_dim 90
#define PARAM_ch_O_fade_time 91
#define PARAM_ch_O_lock_mode 92
#define PARAM_ch_O_lock_time 93
#define PARAM_ch_O_autooff_time 94
#define PARAM_ch_O_switchvalues 95
#define PARAM_ch_P_sw_on_dim 96
#define PARAM_ch_P_fade_time 97
#define PARAM_ch_P_lock_mode 98
#define PARAM_ch_P_lock_time 99
#define PARAM_ch_P_autooff_time 100
#define PARAM_ch_P_switchvalues 101
#define PARAM_ch_Q_sw_on_dim 102
#define PARAM_ch_Q_fade_time 103
#define PARAM_ch_Q_lock_mode 104
#define PARAM_ch_Q_lock_time 105
#define PARAM_ch_Q_autooff_time 106
#define PARAM_ch_Q_switchvalues 107
#define PARAM_ch_R_sw_on_dim 108
#define PARAM_ch_R_fade_time 109
#define PARAM_ch_R_lock_mode 110
#define PARAM_ch_R_lock_time 111
#define PARAM_ch_R_autooff_time 112
#define PARAM_ch_R_switchvalues 113
#define PARAM_ch_S_sw_on_dim 114
#define PARAM_ch_S_fade_time 115
#define PARAM_ch_S_lock_mode 116
#define PARAM_ch_S_lock_time 117
#define PARAM_ch_S_autooff_time 118
#define PARAM_ch_S_switchvalues 119
#define PARAM_ch_T_sw_on_dim 120
#define PARAM_ch_T_fade_time 121
#define PARAM_ch_T_lock_mode 122
#define PARAM_ch_T_lock_time 123
#define PARAM_ch_T_autooff_time 124
#define PARAM_ch_T_switchvalues 125
#define PARAM_ch_U_sw_on_dim 126
#define PARAM_ch_U_fade_time 127
#define PARAM_ch_U_lock_mode 128
#define PARAM_ch_U_lock_time 129
#define PARAM_ch_U_autooff_time 130
#define PARAM_ch_U_switchvalues 131
#define PARAM_ch_V_sw_on_dim 132
#define PARAM_ch_V_fade_time 133
#define PARAM_ch_V_lock_mode 134
#define PARAM_ch_V_lock_time 135
#define PARAM_ch_V_autooff_time 136
#define PARAM_ch_V_switchvalues 137
#define PARAM_ch_W_sw_on_dim 138
#define PARAM_ch_W_fade_time 139
#define PARAM_ch_W_lock_mode 140
#define PARAM_ch_W_lock_time 141
#define PARAM_ch_W_autooff_time 142
#define PARAM_ch_W_switchvalues 143
#define PARAM_ch_X_sw_on_dim 144
#define PARAM_ch_X_fade_time 145
#define PARAM_ch_X_lock_mode 146
#define PARAM_ch_X_lock_time 147
#define PARAM_ch_X_autooff_time 148
#define PARAM_ch_X_switchvalues 149
#define PARAM_ch_ABC_sw_on_dim 150
#define PARAM_ch_ABC_fade_time 151
#define PARAM_ch_ABC_lock_mode 152
#define PARAM_ch_ABC_lock_time 153
#define PARAM_ch_ABC_autooff_time 154
#define PARAM_ch_ABC_switchvalues 155
#define PARAM_ch_EFG_sw_on_dim 156
#define PARAM_ch_EFG_fade_time 157
#define PARAM_ch_EFG_lock_mode 158
#define PARAM_ch_EFG_lock_time 159
#define PARAM_ch_EFG_autooff_time 160
#define PARAM_ch_EFG_switchvalues 161
#define PARAM_ch_IJK_sw_on_dim 162
#define PARAM_ch_IJK_fade_time 163
#define PARAM_ch_IJK_lock_mode 164
#define PARAM_ch_IJK_lock_time 165
#define PARAM_ch_IJK_autooff_time 166
#define PARAM_ch_IJK_switchvalues 167
#define PARAM_ch_MNO_sw_on_dim 168
#define PARAM_ch_MNO_fade_time 169
#define PARAM_ch_MNO_lock_mode 170
#define PARAM_ch_MNO_lock_time 171
#define PARAM_ch_MNO_autooff_time 172
#define PARAM_ch_MNO_switchvalues 173
#define PARAM_ch_QRS_sw_on_dim 174
#define PARAM_ch_QRS_fade_time 175
#define PARAM_ch_QRS_lock_mode 176
#define PARAM_ch_QRS_lock_time 177
#define PARAM_ch_QRS_autooff_time 178
#define PARAM_ch_QRS_switchvalues 179
#define PARAM_ch_UVW_sw_on_dim 180
#define PARAM_ch_UVW_fade_time 181
#define PARAM_ch_UVW_lock_mode 182
#define PARAM_ch_UVW_lock_time 183
#define PARAM_ch_UVW_autooff_time 184
#define PARAM_ch_UVW_switchvalues 185