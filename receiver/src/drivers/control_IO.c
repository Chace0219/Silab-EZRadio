/*! @file control_IO.c
 * @brief This file contains functions for controlling LEDs and PBs.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#include "..\bsp.h"

/*------------------------------------------------------------------------*/
/*                          Global variables                              */
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*/
/*                           Local variables                              */
/*------------------------------------------------------------------------*/
#if (!(defined SILABS_PLATFORM_RFSTICK) && !(defined SILABS_PLATFORM_LCDBB))
volatile SEGMENT_VARIABLE(bDelay, U8, SEG_XDATA);
#endif

SEGMENT_VARIABLE(bCio_IoPortState, U8, SEG_DATA);


/*------------------------------------------------------------------------*/
/*                             Local macros                               */
/*------------------------------------------------------------------------*/
#if (!(defined SILABS_PLATFORM_RFSTICK) && !(defined SILABS_PLATFORM_LCDBB))
  #define mCio_WaitIOSteadyState  \
                              for (bDelay = 0u; bDelay < 0x01; bDelay++)  ;

  #if (defined SILABS_MCU_DC_EMIF_F930)
    #define mCio_WaitIOSteadyState_long \
                              for (bDelay = 0u; bDelay < 0x3F; bDelay++)  ;
  #endif
#endif

/*------------------------------------------------------------------------*/
/*                          Function implementations                      */
/*------------------------------------------------------------------------*/

/*!
 * This function is used to initialize specific IO port for LED & PB.
 *
 *  @return None
 *
 *  @note It has to be called from the initialization section.
 */
void vCio_InitIO(void)
{
    bCio_IoPortState = (M_LED1) | (M_LED2) | (M_LED3);
}

/*!
 * This function is used to switch the selected LED on.
 *
 * @param[in] biLedNum  Number of the LED to be switched on (1 ... 4).
 *
 * @return None
 */
void vCio_SetLed(U8 biLedNum)
{
  switch(biLedNum)
  {
    case 1:
      LED1 = ILLUMINATE;
      bCio_IoPortState &= (~M_LED1);
      break;

    case 2:
      bCio_IoPortState &= (~M_LED2);
      LED2 = ILLUMINATE;
      break;

    case 3:
      bCio_IoPortState &= (~M_LED3);
      LED3 = ILLUMINATE;
      break;

    default:
      break;
  }

}

/*!
 * This function is used to switch the selected LED off.
 *
 * @param[in] biLedNum Number of the LED to be switched off (1 ... 4).
 *
 * @return None
 */
void vCio_ClearLed(U8 biLedNum)
{
  switch(biLedNum)
  {
    case 1:
      LED1 = EXTINGUISH;
      bCio_IoPortState |= M_LED1;
      break;

    case 2:
      bCio_IoPortState |= M_LED2;
      LED2 = EXTINGUISH;
      break;

    case 3:
      bCio_IoPortState |= M_LED3;
      LED3 = EXTINGUISH;
      break;

    default:
      break;
  }
}

/**
 * Function to toggle the given LED state.
 *
 * @param[in] biLedNum Number of the LED to be toggled off (1 ... 4).
 *
 * @return None.
 */
void vCio_ToggleLed(U8 biLedNum)
{
  switch(biLedNum)
  {
    case 1:
      if (bCio_IoPortState & M_LED1)
        vCio_SetLed(biLedNum);
      else
        vCio_ClearLed(biLedNum);
      break;

    case 2:
      if (bCio_IoPortState & M_LED2)
        vCio_SetLed(biLedNum);
      else
        vCio_ClearLed(biLedNum);
      break;

    case 3:
      if (bCio_IoPortState & M_LED3)
        vCio_SetLed(biLedNum);
      else
        vCio_ClearLed(biLedNum);
      break;

    default:
      break;
  }

}

/*!
 * This function is used to read the status of the selected push-button.
 *
 * @param[in] biPbNum Number of the push-button to be switched on (1 ... 4).
 *
 * @return State of the selected PB.
 *
 * @note If SILABS_IO_WITH_EXTENDER defined the function implements a "cache"
 * algorithm to eliminate the SMBus communication overhead. As the IOExt returns
 * all PB states in one byte queries for each PB state is unnecessary. The SMBus
 * fetch takes place only in case the PB state has been already read.
 */
BIT gCio_GetPB(U8 biPbNum)
{
  BIT s;
  //check whether the selected button was pressed or not
  switch (biPbNum)
  {
    case 1:
      s = PB1;
    break;

    default:
      s = 1;
    break;
  }

  return s;
}
