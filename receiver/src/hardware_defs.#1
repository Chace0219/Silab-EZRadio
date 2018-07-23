/*! @file hardware_defs.h
 * @brief This file contains hardware specific definitions defined by the platform.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#ifndef HARDWARE_DEFS_H
#define HARDWARE_DEFS_H

/*-------------------------------------------------------------*/
/*						      Global definitions				                 */
/*-------------------------------------------------------------*/


/*!* LED state Type definition */
typedef enum
{
  ILLUMINATE,
  EXTINGUISH
} eLEDStates;

#define HW_NUMOF_LEDS             3u
#define NUMOF_PUSHBUTTONS         1u

#define M_P0_UART_TX 0x10
#define M_P0_UART_RX 0x20

#define B_P0_SPI0_SCK   6u
//#define B_P1_SPI0_MISO  6u
#define B_P0_SPI0_MOSI  3u

#define M_P0_SPI0_SCK   (1 << B_P0_SPI0_SCK )
//#define M_P1_SPI0_MISO  (1 << B_P1_SPI0_MISO)
#define M_P0_SPI0_MOSI  (1 << B_P0_SPI0_MOSI)

#define MASK_SPI0_MOSI     M_P0_SPI0_MOSI
#define PIN_SPI0_MOSI      B_P0_SPI0_MOSI
#define PORT_SPI0_MOSI                 P0
#define PXMDOUT_SPI0_MOSI         P0MDOUT
#define PXSKIP_SPI0_MOSI           P0SKIP

#define MASK_SPI0_SCK       M_P0_SPI0_SCK
#define PIN_SPI0_SCK        B_P0_SPI0_SCK
#define PORT_SPI0_SCK                  P0
#define PXMDOUT_SPI0_SCK          P0MDOUT
#define PXSKIP_SPI0_SCK            P0SKIP

#define B_P1_SPI1_SCK   0u
#define B_P1_SPI1_MISO  1u
#define B_P1_SPI1_MOSI  2u

#define M_P1_SPI1_SCK   (1 << B_P1_SPI1_SCK )
#define M_P1_SPI1_MISO  (1 << B_P1_SPI1_MISO)
#define M_P1_SPI1_MOSI  (1 << B_P1_SPI1_MOSI)

#define MASK_SPI1_MOSI     M_P1_SPI1_MOSI
#define PIN_SPI1_MOSI      B_P1_SPI1_MOSI
#define PORT_SPI1_MOSI                 P1
#define PXMDOUT_SPI1_MOSI         P1MDOUT
#define PXSKIP_SPI1_MOSI           P1SKIP

#define MASK_SPI1_MISO     M_P1_SPI1_MISO
#define PIN_SPI1_MISO      B_P1_SPI1_MISO
#define PORT_SPI1_MISO                 P1
#define PXMDOUT_SPI1_MISO         P1MDOUT
#define PXSKIP_SPI1_MISO           P1SKIP

#define MASK_SPI1_SCK       M_P1_SPI1_SCK
#define PIN_SPI1_SCK        B_P1_SPI1_SCK
#define PORT_SPI1_SCK                  P1
#define PXMDOUT_SPI1_SCK          P1MDOUT
#define PXSKIP_SPI1_SCK            P1SKIP

#define B_P0_LCD_NSEL   2u
#define B_P1_LCD_A0     6u

#define M_P0_LCD_NSEL   (1 << B_P0_LCD_NSEL)
#define M_P1_LCD_A0     (1 << B_P1_LCD_A0)

#define B_P1_I2C_SDA    4u
#define B_P1_I2C_SCL    5u

#define M_P1_I2C_SCL    (1 << B_P1_I2C_SDA)
#define M_P1_I2C_SDA    (1 << B_P1_I2C_SCL)

// button pin definition
#define B_P0_PB1        2u

// LED pin definitions
#define B_P1_LED1       4u
#define B_P1_LED2       5u
#define B_P1_LED3       6u

#define M_P1_LED1       (1 << B_P1_LED1)
#define M_P1_LED2       (1 << B_P1_LED2)
#define M_P1_LED3       (1 << B_P1_LED3)

#define M_LED1          M_P1_LED1
#define M_LED2          M_P1_LED2
#define M_LED3          M_P1_LED3

// 
#define B_P1_RF_NSEL    3u
#define B_P0_RF_PWRDN   7u

#define B_P0_RF_NIRQ    1u

#define M_P1_RF_NSEL    (1 << B_P1_RF_NSEL)
#define M_P0_RF_PWRDN   (1 << B_P0_RF_PWRDN)
#define M_P0_RF_NIRQ    (1 << B_P0_RF_NIRQ)

/* In WMB RF_GPIO0 is not connected to the MCU by default,
 * the input pin is interchangeable with the buzzer.
 * It is defined here for consistency with DCP_Module.
 */
#define B_P0_RF_GPIO0   0u
#define B_P0_RF_GPIO1   6u
#define B_P0_RF_GPIO2   2u
#define B_P0_RF_GPIO3   3u

#define M_P0_RF_GPIO0   (1 << B_P0_RF_GPIO0)
#define M_P0_RF_GPIO1   (1 << B_P0_RF_GPIO1)
#define M_P0_RF_GPIO2   (1 << B_P0_RF_GPIO2)
#define M_P0_RF_GPIO3   (1 << B_P0_RF_GPIO3)

#define PIN_MCU_MOSI      PIN_SPI1_MOSI
#define PORT_MCU_MOSI     PORT_SPI1_MOSI
#define PXMDOUT_MCU_MOSI  PXMDOUT_SPI1_MOSI

#define PIN_MCU_MISO      PIN_SPI1_MISO
#define PORT_MCU_MISO     PORT_SPI1_MISO
#define PXMDOUT_MCU_MISO  PXMDOUT_SPI1_MISO

#define PIN_MCU_SCK       PIN_SPI1_SCK
#define PORT_MCU_SCK      PORT_SPI1_SCK
#define PXMDOUT_MCU_SCK   PXMDOUT_SPI1_SCK

#define PIN_MCU_NSEL        B_P1_RF_NSEL
#define PORT_MCU_NSEL                 P1
#define PXMDOUT_MCU_NSEL         P1MDOUT

#define PIN_MCU_SDA         B_P1_I2C_SDA
#define PORT_MCU_SDA                  P1
#define PXMDOUT_MCU_SDA          P1MDOUT

#define PIN_MCU_SCL         B_P1_I2C_SCL
#define PORT_MCU_SCL                  P1
#define PXMDOUT_MCU_SCL          P1MDOUT

/* In WMB RF_GPIO0 is not connected to the MCU by default,
 * the input pin is interchangeable with the buzzer.
 * It is defined here for consistency with DCP_Module.
 */
#define PIN_MCU_GPIO0      B_P0_RF_GPIO0
#define PORT_MCU_GPIO0                P0
#define PXMDOUT_MCU_GPIO0        P0MDOUT

#define PIN_MCU_GPIO1      B_P0_RF_GPIO1
#define PORT_MCU_GPIO1                P0
#define PXMDOUT_MCU_GPIO1        P0MDOUT

#define PIN_MCU_GPIO2      B_P0_RF_GPIO0
#define PORT_MCU_GPIO2                P0
#define PXMDOUT_MCU_GPIO2        P0MDOUT

#define PIN_MCU_GPIO3      B_P0_RF_GPIO3
#define PORT_MCU_GPIO3                P0
#define PXMDOUT_MCU_GPIO3        P0MDOUT

#define PIN_MCU_SDN        B_P0_RF_PWRDN
#define PORT_MCU_SDN                  P0
#define PXMDOUT_MCU_SDN          P0MDOUT



#define PIN_MCU_NIRQ        B_P0_RF_NIRQ
#define PORT_MCU_NIRQ                 P0
#define PXMDOUT_MCU_NIRQ         P0MDOUT

//SBIT(RF_GPIO0,  SFR_P0, B_P0_RF_GPIO0);
SBIT(RF_GPIO1,  SFR_P0, B_P0_RF_GPIO1);
SBIT(RF_GPIO2,  SFR_P0, B_P0_RF_GPIO2);
SBIT(RF_GPIO3,  SFR_P0, B_P0_RF_GPIO3);

/* SMBus */
SBIT(MCU_SDA,   SFR_P1, B_P1_I2C_SDA);
SBIT(MCU_SCL,   SFR_P1, B_P1_I2C_SCL);

/* LEDs */
SBIT(LED1,      SFR_P1, B_P1_LED1);
SBIT(LED2,      SFR_P1, B_P1_LED2);
SBIT(LED3,      SFR_P1, B_P1_LED3);

/* MCU SPI0 */
SBIT(SPI0_SCK,  SFR_P0, B_P0_SPI0_SCK);
//SBIT(SPI0_MISO, SFR_P1, B_P1_SPI1_MISO);
SBIT(SPI0_MOSI, SFR_P0, B_P0_SPI0_MOSI);

/* MCU SPI1 */
SBIT(SPI1_SCK,  SFR_P1, B_P1_SPI1_SCK);
SBIT(SPI1_MISO, SFR_P1, B_P1_SPI1_MISO);
SBIT(SPI1_MOSI, SFR_P1, B_P1_SPI1_MOSI);

SBIT(RF_PWRDN,  SFR_P0, B_P0_RF_PWRDN);
SBIT(RF_NSEL,   SFR_P1, B_P1_RF_NSEL);
SBIT(RF_IRQ,    SFR_P0, B_P0_RF_NIRQ);
SBIT(RF_NIRQ,   SFR_P0, B_P0_RF_NIRQ);

/* LCD related */
SBIT(LCD_NSEL,  SFR_P0, B_P0_LCD_NSEL);
SBIT(LCD_A0,    SFR_P1, B_P1_LCD_A0);

SBIT(PB1,       SFR_P0, B_P0_PB1);

#endif //HARDWARE_DEFS_H
