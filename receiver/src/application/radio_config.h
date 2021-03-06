/*! @file radio_config.h
 * @brief This file contains the automatically generated
 * configurations.
 *
 * @n WDS GUI Version: 3.2.11.0
 * @n Device: Si1064 Rev.: A0                                 
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2017 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#ifndef RADIO_CONFIG_H_
#define RADIO_CONFIG_H_

// USER DEFINED PARAMETERS
// Define your own parameters here

// INPUT DATA
/*
// Crys_freq(Hz): 30000000    Crys_tol(ppm): 30    IF_mode: 2    High_perf_Ch_Fil: 1    OSRtune: 0    Ch_Fil_Bw_AFC: 0    ANT_DIV: 0    PM_pattern: 0    
// MOD_type: 3    Rsymb(sps): 10000    Fdev(Hz): 30000    RXBW(Hz): 114000    Manchester: 0    AFC_en: 1    Rsymb_error: 0.0    Chip-Version: 2    
// RF Freq.(MHz): 434    API_TC: 28    fhst: 250000    inputBW: 0    BERT: 0    RAW_dout: 0    D_source: 0    Hi_pfm_div: 0    
// 
// # WB filter 1 (BW = 114.46 kHz);  NB-filter 1 (BW = 114.46 kHz) 
// 
// Modulation index: 6
*/


// CONFIGURATION PARAMETERS
#define RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ                     30000000L
#define RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER                    0x00
#define RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH               0x07
#define RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP        0x03
#define RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET       0xF000


// CONFIGURATION COMMANDS

/*
// Command:                  RF_POWER_UP
// Description:              Command to power-up the device and select the operational mode and functionality.
*/
#define RF_POWER_UP 0x02, 0x01, 0x00, 0x01, 0xC9, 0xC3, 0x80

/*
// Set properties:           RF_INT_CTL_ENABLE_2
// Number of properties:     2
// Group ID:                 0x01
// Start ID:                 0x00
// Default values:           0x04, 0x00, 
// Descriptions:
//   INT_CTL_ENABLE - This property provides for global enabling of the three interrupt groups (Chip, Modem and Packet Handler) in order to generate HW interrupts at the NIRQ pin.
//   INT_CTL_PH_ENABLE - Enable individual interrupt sources within the Packet Handler Interrupt Group to generate a HW interrupt on the NIRQ output pin.
*/
#define RF_INT_CTL_ENABLE_2 0x11, 0x01, 0x02, 0x00, 0x01, 0x18

/*
// Set properties:           RF_FRR_CTL_A_MODE_4
// Number of properties:     4
// Group ID:                 0x02
// Start ID:                 0x00
// Default values:           0x01, 0x02, 0x09, 0x00, 
// Descriptions:
//   FRR_CTL_A_MODE - Fast Response Register A Configuration.
//   FRR_CTL_B_MODE - Fast Response Register B Configuration.
//   FRR_CTL_C_MODE - Fast Response Register C Configuration.
//   FRR_CTL_D_MODE - Fast Response Register D Configuration.
*/
#define RF_FRR_CTL_A_MODE_4 0x11, 0x02, 0x04, 0x00, 0x08, 0x06, 0x04, 0x0A

/*
// Set properties:           RF_EZCONFIG_XO_TUNE_1
// Number of properties:     1
// Group ID:                 0x24
// Start ID:                 0x03
// Default values:           0x40, 
// Descriptions:
//   EZCONFIG_XO_TUNE - Configure the internal capacitor frequency tuning bank for the crystal oscillator.
*/
#define RF_EZCONFIG_XO_TUNE_1 0x11, 0x24, 0x01, 0x03, 0x3B

/*
// Command:                  RF_WRITE_TX_FIFO
// Description:              Writes data byte(s) to the TX FIFO.
*/
#define RF_WRITE_TX_FIFO 0x66, 0xCE, 0xA3, 0x43, 0xD9, 0xD0, 0x0F, 0xC8, 0x94, 0x3A, 0xE9, 0xC0, 0xE8, 0x29, 0x1B, 0xA5, 0xC5, 0x45, 0x0C, 0x91, \
0xE5, 0x52, 0xEC, 0x66, 0x44, 0x04, 0x07, 0x25, 0x79, 0x24, 0x96, 0x89, 0x64, 0x9E, 0x18, 0xC3, 0x7C, 0xD9, 0xF3, 0x1E, \
0x08, 0x84, 0x54, 0xC5, 0xA0, 0x2C, 0xE2, 0x31, 0x41, 0xF2, 0xA8, 0x7C, 0x6B, 0x18, 0x93, 0x08, 0xA3, 0xBA, 0x66, 0x6F, \
0x78, 0x85, 0x49, 0x91, 0x28, 0x53, 0xF7, 0x06, 0x70, 0x66, 0x72, 0x74, 0xB8, 0x0E, 0x99, 0x54, 0x84, 0xE4, 0x78, 0x6B, \
0xEC, 0x15, 0x18, 0x0A, 0xE7, 0xDF, 0x9D, 0x24, 0x32, 0x80, 0x80, 0xD4, 0x1D, 0x4A, 0x3D, 0xFB, 0x72, 0xAA, 0xDD, 0xB2, \
0xD8, 0xD4, 0x60, 0x4E, 0xB3, 0xED, 0x3E, 0xBC, 0xAB, 0x75, 0x57, 0xEC, 0xFD, 0x7C

/*
// Command:                  RF_NOP
// Description:              No Operation command.
*/
#define RF_NOP 0x00

/*
// Command:                  RF_WRITE_TX_FIFO_1
// Description:              Writes data byte(s) to the TX FIFO.
*/
#define RF_WRITE_TX_FIFO_1 0x66, 0x42, 0xCB, 0x95, 0x94, 0x1B, 0x53, 0x5A, 0x13, 0x4F, 0xFB, 0xEF, 0xFD, 0x69, 0x57, 0x7C, 0x3D, 0x99, 0x73, 0xBB, \
0x48, 0xC1, 0x16, 0xBD, 0x28, 0x4A, 0x0C, 0x15, 0x8B, 0x58, 0xD0, 0xB4, 0xF0, 0x8F, 0x39, 0xFD, 0x57, 0x32, 0x79, 0x17, \
0x66, 0xED, 0x16, 0xB3, 0x20, 0x6E, 0x8F, 0xEF, 0x8B, 0x6C, 0xDC, 0xA3, 0xF1, 0xE8, 0x60, 0x9F, 0xF6, 0x78, 0x00, 0xB5, \
0x46, 0x21, 0x7C, 0x6D, 0x9D, 0x22, 0xA5, 0xB4, 0x9B, 0xE9, 0x04, 0xCE, 0x4E, 0x07, 0x9D, 0xFF, 0xB1, 0xA3, 0x41, 0xEA, \
0x01, 0x78, 0x31, 0x1C, 0x1C, 0x0B, 0x50, 0x7C, 0x13, 0x6A, 0x3B, 0x54, 0xF1, 0x80, 0x48, 0x1D, 0x6C, 0x2D, 0xE1, 0x0E, \
0x99, 0x76, 0x40, 0x14, 0x06, 0x62, 0x7A, 0xFA, 0xFE, 0x1A, 0x79, 0xE9

/*
// Command:                  RF_EZCONFIG_CHECK
// Description:              Validates the EZConfig array was written correctly.
*/
#define RF_EZCONFIG_CHECK 0x19, 0x68, 0x24

/*
// Command:                  RF_GPIO_PIN_CFG
// Description:              Configures the GPIO pins.
*/
#define RF_GPIO_PIN_CFG 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00


// AUTOMATICALLY GENERATED CODE! 
// DO NOT EDIT/MODIFY BELOW THIS LINE!
// --------------------------------------------

#ifndef FIRMWARE_LOAD_COMPILE
#define RADIO_CONFIGURATION_DATA_ARRAY { \
        0x07, RF_POWER_UP, \
        0x06, RF_INT_CTL_ENABLE_2, \
        0x08, RF_FRR_CTL_A_MODE_4, \
        0x05, RF_EZCONFIG_XO_TUNE_1, \
        0x72, RF_WRITE_TX_FIFO, \
        0x01, RF_NOP, \
        0x70, RF_WRITE_TX_FIFO_1, \
        0x03, RF_EZCONFIG_CHECK, \
        0x08, RF_GPIO_PIN_CFG, \
        0x00 \
 }
#else
#define RADIO_CONFIGURATION_DATA_ARRAY { 0 }
#endif

// DEFAULT VALUES FOR CONFIGURATION PARAMETERS
#define RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ_DEFAULT                     30000000L
#define RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER_DEFAULT                    0x00
#define RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH_DEFAULT               0x10
#define RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP_DEFAULT        0x01
#define RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET_DEFAULT       0x1000

#define RADIO_CONFIGURATION_DATA_RADIO_PATCH_INCLUDED                      0x00
#define RADIO_CONFIGURATION_DATA_RADIO_PATCH_SIZE                          0x00
#define RADIO_CONFIGURATION_DATA_RADIO_PATCH                               {  }

#ifndef RADIO_CONFIGURATION_DATA_ARRAY
#error "This property must be defined!"
#endif

#ifndef RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ
#define RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ          RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER
#define RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER         RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH
#define RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH    RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP
#define RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP   RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET
#define RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET  RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET_DEFAULT 
#endif

#define RADIO_CONFIGURATION_DATA { \
                            Radio_Configuration_Data_Array,                            \
                            RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER,                   \
                            RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH,              \
                            RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP,       \
                            RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET       \
                            }

#endif /* RADIO_CONFIG_H_ */
