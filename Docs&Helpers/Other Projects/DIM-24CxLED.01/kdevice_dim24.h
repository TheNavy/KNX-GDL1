KnxComObject KnxDevice::_comObjectsList[] = {
    /* Index 0 - ch_A_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 1 - ch_A_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 2 - ch_A_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 3 - ch_A_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 4 - ch_A_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 5 - ch_A_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 6 - ch_A_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 7 - ch_B_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 8 - ch_B_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 9 - ch_B_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 10 - ch_B_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 11 - ch_B_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 12 - ch_B_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 13 - ch_B_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 14 - ch_C_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 15 - ch_C_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 16 - ch_C_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 17 - ch_C_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 18 - ch_C_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 19 - ch_C_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 20 - ch_C_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 21 - ch_D_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 22 - ch_D_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 23 - ch_D_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 24 - ch_D_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 25 - ch_D_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 26 - ch_D_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 27 - ch_D_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 28 - ch_E_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 29 - ch_E_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 30 - ch_E_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 31 - ch_E_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 32 - ch_E_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 33 - ch_E_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 34 - ch_E_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 35 - ch_F_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 36 - ch_F_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 37 - ch_F_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 38 - ch_F_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 39 - ch_F_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 40 - ch_F_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 41 - ch_F_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 42 - ch_G_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 43 - ch_G_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 44 - ch_G_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 45 - ch_G_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 46 - ch_G_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 47 - ch_G_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 48 - ch_G_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 49 - ch_H_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 50 - ch_H_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 51 - ch_H_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 52 - ch_H_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 53 - ch_H_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 54 - ch_H_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 55 - ch_H_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 56 - ch_I_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 57 - ch_I_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 58 - ch_I_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 59 - ch_I_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 60 - ch_I_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 61 - ch_I_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 62 - ch_I_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 63 - ch_J_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 64 - ch_J_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 65 - ch_J_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 66 - ch_J_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 67 - ch_J_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 68 - ch_J_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 69 - ch_J_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 70 - ch_K_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 71 - ch_K_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 72 - ch_K_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 73 - ch_K_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 74 - ch_K_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 75 - ch_K_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 76 - ch_K_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 77 - ch_L_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 78 - ch_L_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 79 - ch_L_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 80 - ch_L_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 81 - ch_L_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 82 - ch_L_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 83 - ch_L_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 84 - ch_M_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 85 - ch_M_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 86 - ch_M_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 87 - ch_M_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 88 - ch_M_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 89 - ch_M_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 90 - ch_M_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 91 - ch_N_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 92 - ch_N_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 93 - ch_N_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 94 - ch_N_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 95 - ch_N_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 96 - ch_N_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 97 - ch_N_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 98 - ch_O_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 99 - ch_O_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 100 - ch_O_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 101 - ch_O_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 102 - ch_O_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 103 - ch_O_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 104 - ch_O_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 105 - ch_P_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 106 - ch_P_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 107 - ch_P_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 108 - ch_P_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 109 - ch_P_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 110 - ch_P_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 111 - ch_P_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 112 - ch_Q_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 113 - ch_Q_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 114 - ch_Q_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 115 - ch_Q_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 116 - ch_Q_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 117 - ch_Q_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 118 - ch_Q_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 119 - ch_R_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 120 - ch_R_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 121 - ch_R_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 122 - ch_R_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 123 - ch_R_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 124 - ch_R_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 125 - ch_R_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 126 - ch_S_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 127 - ch_S_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 128 - ch_S_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 129 - ch_S_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 130 - ch_S_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 131 - ch_S_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 132 - ch_S_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 133 - ch_T_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 134 - ch_T_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 135 - ch_T_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 136 - ch_T_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 137 - ch_T_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 138 - ch_T_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 139 - ch_T_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 140 - ch_U_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 141 - ch_U_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 142 - ch_U_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 143 - ch_U_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 144 - ch_U_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 145 - ch_U_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 146 - ch_U_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 147 - ch_V_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 148 - ch_V_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 149 - ch_V_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 150 - ch_V_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 151 - ch_V_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 152 - ch_V_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 153 - ch_V_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 154 - ch_W_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 155 - ch_W_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 156 - ch_W_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 157 - ch_W_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 158 - ch_W_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 159 - ch_W_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 160 - ch_W_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 161 - ch_X_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 162 - ch_X_dim */ KnxComObject(KNX_DPT_5_001, 0x28),
    /* Index 163 - ch_X_dimrel */ KnxComObject(KNX_DPT_3_007, 0x28),
    /* Index 164 - ch_X_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 165 - ch_X_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 166 - ch_X_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 167 - ch_X_stat_dim */ KnxComObject(KNX_DPT_5_001, 0x34),
    /* Index 168 - ch_ABC_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 169 - ch_ABC_dim */ KnxComObject(KNX_DPT_232_600, 0x28),
    /* Index 170 - ch_ABC_animation */ KnxComObject(KNX_DPT_5_010, 0x38),
    /* Index 171 - ch_ABC_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 172 - ch_ABC_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 173 - ch_ABC_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 174 - ch_ABC_stat_dim */ KnxComObject(KNX_DPT_232_600, 0x34),
    /* Index 175 - ch_EFG_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 176 - ch_EFG_dim */ KnxComObject(KNX_DPT_232_600, 0x28),
    /* Index 177 - ch_EFG_animation */ KnxComObject(KNX_DPT_5_010, 0x38),
    /* Index 178 - ch_EFG_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 179 - ch_EFG_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 180 - ch_EFG_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 181 - ch_EFG_stat_dim */ KnxComObject(KNX_DPT_232_600, 0x34),
    /* Index 182 - ch_IJK_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 183 - ch_IJK_dim */ KnxComObject(KNX_DPT_232_600, 0x28),
    /* Index 184 - ch_IJK_animation */ KnxComObject(KNX_DPT_5_010, 0x38),
    /* Index 185 - ch_IJK_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 186 - ch_IJK_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 187 - ch_IJK_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 188 - ch_IJK_stat_dim */ KnxComObject(KNX_DPT_232_600, 0x34),
    /* Index 189 - ch_MNO_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 190 - ch_MNO_dim */ KnxComObject(KNX_DPT_232_600, 0x28),
    /* Index 191 - ch_MNO_animation */ KnxComObject(KNX_DPT_5_010, 0x38),
    /* Index 192 - ch_MNO_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 193 - ch_MNO_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 194 - ch_MNO_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 195 - ch_MNO_stat_dim */ KnxComObject(KNX_DPT_232_600, 0x34),
    /* Index 196 - ch_QRS_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 197 - ch_QRS_dim */ KnxComObject(KNX_DPT_232_600, 0x28),
    /* Index 198 - ch_QRS_animation */ KnxComObject(KNX_DPT_5_010, 0x38),
    /* Index 199 - ch_QRS_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 200 - ch_QRS_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 201 - ch_QRS_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 202 - ch_QRS_stat_dim */ KnxComObject(KNX_DPT_232_600, 0x34),
    /* Index 203 - ch_UVW_sw */ KnxComObject(KNX_DPT_1_001, 0x28),
    /* Index 204 - ch_UVW_dim */ KnxComObject(KNX_DPT_232_600, 0x28),
    /* Index 205 - ch_UVW_animation */ KnxComObject(KNX_DPT_5_010, 0x38),
    /* Index 206 - ch_UVW_lock */ KnxComObject(KNX_DPT_1_003, 0x38),
    /* Index 207 - ch_UVW_scene */ KnxComObject(KNX_DPT_17_001, 0x38),
    /* Index 208 - ch_UVW_stat_sw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 209 - ch_UVW_stat_dim */ KnxComObject(KNX_DPT_232_600, 0x34),
    /* Index 210 - gen_casetemp */ KnxComObject(KNX_DPT_9_001, 0x30),
    /* Index 211 - gen_temp_alarm */ KnxComObject(KNX_DPT_1_005, 0x34),
    /* Index 212 - gen_daynight */ KnxComObject(KNX_DPT_1_001, 0x2A),
    /* Index 213 - gen_datetime */ KnxComObject(KNX_DPT_19_001, 0x2A),
    /* Index 214 - error_code */ KnxComObject(KNX_DPT_12_001, 0x34)
};
const byte KnxDevice::_numberOfComObjects = sizeof (_comObjectsList) / sizeof (KnxComObject); // do not change this code
       
byte KonnektingDevice::_paramSizeList[] = {
    /* Index 0 - ch_ABC_mode */ PARAM_UINT8,
    /* Index 1 - ch_EFG_mode */ PARAM_UINT8,
    /* Index 2 - ch_IJK_mode */ PARAM_UINT8,
    /* Index 3 - ch_MNO_mode */ PARAM_UINT8,
    /* Index 4 - ch_QRS_mode */ PARAM_UINT8,
    /* Index 5 - ch_UVW_mode */ PARAM_UINT8,
    /* Index 6 - ch_A_sw_on_dim */ PARAM_UINT8,
    /* Index 7 - ch_A_fade_time */ PARAM_UINT8,
    /* Index 8 - ch_A_lock_mode */ PARAM_UINT8,
    /* Index 9 - ch_A_lock_time */ PARAM_UINT16,
    /* Index 10 - ch_A_autooff_time */ PARAM_UINT16,
    /* Index 11 - ch_A_switchvalues */ PARAM_RAW2,
    /* Index 12 - ch_B_sw_on_dim */ PARAM_UINT8,
    /* Index 13 - ch_B_fade_time */ PARAM_UINT8,
    /* Index 14 - ch_B_lock_mode */ PARAM_UINT8,
    /* Index 15 - ch_B_lock_time */ PARAM_UINT16,
    /* Index 16 - ch_B_autooff_time */ PARAM_UINT16,
    /* Index 17 - ch_B_switchvalues */ PARAM_RAW2,
    /* Index 18 - ch_C_sw_on_dim */ PARAM_UINT8,
    /* Index 19 - ch_C_fade_time */ PARAM_UINT8,
    /* Index 20 - ch_C_lock_mode */ PARAM_UINT8,
    /* Index 21 - ch_C_lock_time */ PARAM_UINT16,
    /* Index 22 - ch_C_autooff_time */ PARAM_UINT16,
    /* Index 23 - ch_C_switchvalues */ PARAM_RAW2,
    /* Index 24 - ch_D_sw_on_dim */ PARAM_UINT8,
    /* Index 25 - ch_D_fade_time */ PARAM_UINT8,
    /* Index 26 - ch_D_lock_mode */ PARAM_UINT8,
    /* Index 27 - ch_D_lock_time */ PARAM_UINT16,
    /* Index 28 - ch_D_autooff_time */ PARAM_UINT16,
    /* Index 29 - ch_D_switchvalues */ PARAM_RAW2,
    /* Index 30 - ch_E_sw_on_dim */ PARAM_UINT8,
    /* Index 31 - ch_E_fade_time */ PARAM_UINT8,
    /* Index 32 - ch_E_lock_mode */ PARAM_UINT8,
    /* Index 33 - ch_E_lock_time */ PARAM_UINT16,
    /* Index 34 - ch_E_autooff_time */ PARAM_UINT16,
    /* Index 35 - ch_E_switchvalues */ PARAM_RAW2,
    /* Index 36 - ch_F_sw_on_dim */ PARAM_UINT8,
    /* Index 37 - ch_F_fade_time */ PARAM_UINT8,
    /* Index 38 - ch_F_lock_mode */ PARAM_UINT8,
    /* Index 39 - ch_F_lock_time */ PARAM_UINT16,
    /* Index 40 - ch_F_autooff_time */ PARAM_UINT16,
    /* Index 41 - ch_F_switchvalues */ PARAM_RAW2,
    /* Index 42 - ch_G_sw_on_dim */ PARAM_UINT8,
    /* Index 43 - ch_G_fade_time */ PARAM_UINT8,
    /* Index 44 - ch_G_lock_mode */ PARAM_UINT8,
    /* Index 45 - ch_G_lock_time */ PARAM_UINT16,
    /* Index 46 - ch_G_autooff_time */ PARAM_UINT16,
    /* Index 47 - ch_G_switchvalues */ PARAM_RAW2,
    /* Index 48 - ch_H_sw_on_dim */ PARAM_UINT8,
    /* Index 49 - ch_H_fade_time */ PARAM_UINT8,
    /* Index 50 - ch_H_lock_mode */ PARAM_UINT8,
    /* Index 51 - ch_H_lock_time */ PARAM_UINT16,
    /* Index 52 - ch_H_autooff_time */ PARAM_UINT16,
    /* Index 53 - ch_H_switchvalues */ PARAM_RAW2,
    /* Index 54 - ch_I_sw_on_dim */ PARAM_UINT8,
    /* Index 55 - ch_I_fade_time */ PARAM_UINT8,
    /* Index 56 - ch_I_lock_mode */ PARAM_UINT8,
    /* Index 57 - ch_I_lock_time */ PARAM_UINT16,
    /* Index 58 - ch_I_autooff_time */ PARAM_UINT16,
    /* Index 59 - ch_I_switchvalues */ PARAM_RAW2,
    /* Index 60 - ch_J_sw_on_dim */ PARAM_UINT8,
    /* Index 61 - ch_J_fade_time */ PARAM_UINT8,
    /* Index 62 - ch_J_lock_mode */ PARAM_UINT8,
    /* Index 63 - ch_J_lock_time */ PARAM_UINT16,
    /* Index 64 - ch_J_autooff_time */ PARAM_UINT16,
    /* Index 65 - ch_J_switchvalues */ PARAM_RAW2,
    /* Index 66 - ch_K_sw_on_dim */ PARAM_UINT8,
    /* Index 67 - ch_K_fade_time */ PARAM_UINT8,
    /* Index 68 - ch_K_lock_mode */ PARAM_UINT8,
    /* Index 69 - ch_K_lock_time */ PARAM_UINT16,
    /* Index 70 - ch_K_autooff_time */ PARAM_UINT16,
    /* Index 71 - ch_K_switchvalues */ PARAM_RAW2,
    /* Index 72 - ch_L_sw_on_dim */ PARAM_UINT8,
    /* Index 73 - ch_L_fade_time */ PARAM_UINT8,
    /* Index 74 - ch_L_lock_mode */ PARAM_UINT8,
    /* Index 75 - ch_L_lock_time */ PARAM_UINT16,
    /* Index 76 - ch_L_autooff_time */ PARAM_UINT16,
    /* Index 77 - ch_L_switchvalues */ PARAM_RAW2,
    /* Index 78 - ch_M_sw_on_dim */ PARAM_UINT8,
    /* Index 79 - ch_M_fade_time */ PARAM_UINT8,
    /* Index 80 - ch_M_lock_mode */ PARAM_UINT8,
    /* Index 81 - ch_M_lock_time */ PARAM_UINT16,
    /* Index 82 - ch_M_autooff_time */ PARAM_UINT16,
    /* Index 83 - ch_M_switchvalues */ PARAM_RAW2,
    /* Index 84 - ch_N_sw_on_dim */ PARAM_UINT8,
    /* Index 85 - ch_N_fade_time */ PARAM_UINT8,
    /* Index 86 - ch_N_lock_mode */ PARAM_UINT8,
    /* Index 87 - ch_N_lock_time */ PARAM_UINT16,
    /* Index 88 - ch_N_autooff_time */ PARAM_UINT16,
    /* Index 89 - ch_N_switchvalues */ PARAM_RAW2,
    /* Index 90 - ch_O_sw_on_dim */ PARAM_UINT8,
    /* Index 91 - ch_O_fade_time */ PARAM_UINT8,
    /* Index 92 - ch_O_lock_mode */ PARAM_UINT8,
    /* Index 93 - ch_O_lock_time */ PARAM_UINT16,
    /* Index 94 - ch_O_autooff_time */ PARAM_UINT16,
    /* Index 95 - ch_O_switchvalues */ PARAM_RAW2,
    /* Index 96 - ch_P_sw_on_dim */ PARAM_UINT8,
    /* Index 97 - ch_P_fade_time */ PARAM_UINT8,
    /* Index 98 - ch_P_lock_mode */ PARAM_UINT8,
    /* Index 99 - ch_P_lock_time */ PARAM_UINT16,
    /* Index 100 - ch_P_autooff_time */ PARAM_UINT16,
    /* Index 101 - ch_P_switchvalues */ PARAM_RAW2,
    /* Index 102 - ch_Q_sw_on_dim */ PARAM_UINT8,
    /* Index 103 - ch_Q_fade_time */ PARAM_UINT8,
    /* Index 104 - ch_Q_lock_mode */ PARAM_UINT8,
    /* Index 105 - ch_Q_lock_time */ PARAM_UINT16,
    /* Index 106 - ch_Q_autooff_time */ PARAM_UINT16,
    /* Index 107 - ch_Q_switchvalues */ PARAM_RAW2,
    /* Index 108 - ch_R_sw_on_dim */ PARAM_UINT8,
    /* Index 109 - ch_R_fade_time */ PARAM_UINT8,
    /* Index 110 - ch_R_lock_mode */ PARAM_UINT8,
    /* Index 111 - ch_R_lock_time */ PARAM_UINT16,
    /* Index 112 - ch_R_autooff_time */ PARAM_UINT16,
    /* Index 113 - ch_R_switchvalues */ PARAM_RAW2,
    /* Index 114 - ch_S_sw_on_dim */ PARAM_UINT8,
    /* Index 115 - ch_S_fade_time */ PARAM_UINT8,
    /* Index 116 - ch_S_lock_mode */ PARAM_UINT8,
    /* Index 117 - ch_S_lock_time */ PARAM_UINT16,
    /* Index 118 - ch_S_autooff_time */ PARAM_UINT16,
    /* Index 119 - ch_S_switchvalues */ PARAM_RAW2,
    /* Index 120 - ch_T_sw_on_dim */ PARAM_UINT8,
    /* Index 121 - ch_T_fade_time */ PARAM_UINT8,
    /* Index 122 - ch_T_lock_mode */ PARAM_UINT8,
    /* Index 123 - ch_T_lock_time */ PARAM_UINT16,
    /* Index 124 - ch_T_autooff_time */ PARAM_UINT16,
    /* Index 125 - ch_T_switchvalues */ PARAM_RAW2,
    /* Index 126 - ch_U_sw_on_dim */ PARAM_UINT8,
    /* Index 127 - ch_U_fade_time */ PARAM_UINT8,
    /* Index 128 - ch_U_lock_mode */ PARAM_UINT8,
    /* Index 129 - ch_U_lock_time */ PARAM_UINT16,
    /* Index 130 - ch_U_autooff_time */ PARAM_UINT16,
    /* Index 131 - ch_U_switchvalues */ PARAM_RAW2,
    /* Index 132 - ch_V_sw_on_dim */ PARAM_UINT8,
    /* Index 133 - ch_V_fade_time */ PARAM_UINT8,
    /* Index 134 - ch_V_lock_mode */ PARAM_UINT8,
    /* Index 135 - ch_V_lock_time */ PARAM_UINT16,
    /* Index 136 - ch_V_autooff_time */ PARAM_UINT16,
    /* Index 137 - ch_V_switchvalues */ PARAM_RAW2,
    /* Index 138 - ch_W_sw_on_dim */ PARAM_UINT8,
    /* Index 139 - ch_W_fade_time */ PARAM_UINT8,
    /* Index 140 - ch_W_lock_mode */ PARAM_UINT8,
    /* Index 141 - ch_W_lock_time */ PARAM_UINT16,
    /* Index 142 - ch_W_autooff_time */ PARAM_UINT16,
    /* Index 143 - ch_W_switchvalues */ PARAM_RAW2,
    /* Index 144 - ch_X_sw_on_dim */ PARAM_UINT8,
    /* Index 145 - ch_X_fade_time */ PARAM_UINT8,
    /* Index 146 - ch_X_lock_mode */ PARAM_UINT8,
    /* Index 147 - ch_X_lock_time */ PARAM_UINT16,
    /* Index 148 - ch_X_autooff_time */ PARAM_UINT16,
    /* Index 149 - ch_X_switchvalues */ PARAM_RAW2,
    /* Index 150 - ch_ABC_sw_on_dim */ PARAM_UINT8,
    /* Index 151 - ch_ABC_fade_time */ PARAM_UINT8,
    /* Index 152 - ch_ABC_lock_mode */ PARAM_UINT8,
    /* Index 153 - ch_ABC_lock_time */ PARAM_UINT16,
    /* Index 154 - ch_ABC_autooff_time */ PARAM_UINT16,
    /* Index 155 - ch_ABC_switchvalues */ PARAM_RAW6,
    /* Index 156 - ch_EFG_sw_on_dim */ PARAM_UINT8,
    /* Index 157 - ch_EFG_fade_time */ PARAM_UINT8,
    /* Index 158 - ch_EFG_lock_mode */ PARAM_UINT8,
    /* Index 159 - ch_EFG_lock_time */ PARAM_UINT16,
    /* Index 160 - ch_EFG_autooff_time */ PARAM_UINT16,
    /* Index 161 - ch_EFG_switchvalues */ PARAM_RAW6,
    /* Index 162 - ch_IJK_sw_on_dim */ PARAM_UINT8,
    /* Index 163 - ch_IJK_fade_time */ PARAM_UINT8,
    /* Index 164 - ch_IJK_lock_mode */ PARAM_UINT8,
    /* Index 165 - ch_IJK_lock_time */ PARAM_UINT16,
    /* Index 166 - ch_IJK_autooff_time */ PARAM_UINT16,
    /* Index 167 - ch_IJK_switchvalues */ PARAM_RAW6,
    /* Index 168 - ch_MNO_sw_on_dim */ PARAM_UINT8,
    /* Index 169 - ch_MNO_fade_time */ PARAM_UINT8,
    /* Index 170 - ch_MNO_lock_mode */ PARAM_UINT8,
    /* Index 171 - ch_MNO_lock_time */ PARAM_UINT16,
    /* Index 172 - ch_MNO_autooff_time */ PARAM_UINT16,
    /* Index 173 - ch_MNO_switchvalues */ PARAM_RAW6,
    /* Index 174 - ch_QRS_sw_on_dim */ PARAM_UINT8,
    /* Index 175 - ch_QRS_fade_time */ PARAM_UINT8,
    /* Index 176 - ch_QRS_lock_mode */ PARAM_UINT8,
    /* Index 177 - ch_QRS_lock_time */ PARAM_UINT16,
    /* Index 178 - ch_QRS_autooff_time */ PARAM_UINT16,
    /* Index 179 - ch_QRS_switchvalues */ PARAM_RAW6,
    /* Index 180 - ch_UVW_sw_on_dim */ PARAM_UINT8,
    /* Index 181 - ch_UVW_fade_time */ PARAM_UINT8,
    /* Index 182 - ch_UVW_lock_mode */ PARAM_UINT8,
    /* Index 183 - ch_UVW_lock_time */ PARAM_UINT16,
    /* Index 184 - ch_UVW_autooff_time */ PARAM_UINT16,
    /* Index 185 - ch_UVW_switchvalues */ PARAM_RAW6
};
const int KonnektingDevice::_numberOfParams = sizeof (_paramSizeList); // do not change this code