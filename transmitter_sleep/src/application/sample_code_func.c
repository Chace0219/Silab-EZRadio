/*! @file sample_code_func.c
 * @brief This file contains functions to manage behavior of basic human module interfaces (push-buttons, switches, LEDs).
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
/*                          Function implementations                      */
/*------------------------------------------------------------------------*/
#ifdef HMI_DRIVER_EXTENDED_SUPPORT
  #if ((defined SILABS_PLATFORM_COMPONENT_PB) && (defined SILABS_PLATFORM_COMPONENT_LED) && (defined SILABS_PLATFORM_COMPONENT_BUZZER))
    /*!
     * This function is used to show the actual state of the push-buttons on the Buzzer.
     *
     * @return  None.
     */
    void vSampleCode_ShowPbOnBuzzer(void)
    {
      SEGMENT_VARIABLE(boPbPushTrack, U8 , SEG_DATA);
      SEGMENT_VARIABLE(woPbPushTime, U16 , SEG_DATA);
      SEGMENT_VARIABLE(bPbLedCnt, U8 , SEG_DATA);

      gHmi_PbIsPushed(&boPbPushTrack, &woPbPushTime);

      for (bPbLedCnt = 1; bPbLedCnt <= 4; bPbLedCnt++)
      {
        if (boPbPushTrack)
        {
          vHmi_ChangeBuzzState(eHmi_BuzzOnce_c);
        }
        else
        {
          vHmi_ChangeBuzzState(eHmi_BuzzOff_c);
        }
      }
    }
  #endif
#endif

#if ((defined SILABS_PLATFORM_COMPONENT_PB) && (defined SILABS_PLATFORM_COMPONENT_LED))
/*!
 * This function is used to show the actual state of the push-buttons on the LEDs.
 *
 * @return  TRUE - Started a packet TX / FALSE - Not packet to be sent.
 */
BIT vSampleCode_SendFixPacket(void)
{
  SEGMENT_VARIABLE(boPbPushTrack, U8, SEG_DATA);
  SEGMENT_VARIABLE(woPbPushTime, U16, SEG_DATA);

  gHmi_PbIsPushed(&boPbPushTrack, &woPbPushTime);

  fixRadioPacket[0]='B';
  fixRadioPacket[1]='U';
  fixRadioPacket[2]='T';
  fixRadioPacket[3]='T';
  fixRadioPacket[4]='O';
  fixRadioPacket[5]='N';

  if(boPbPushTrack & eHmi_Pb1_c)
  {
    fixRadioPacket[6]='1';
  }
  else if(boPbPushTrack & eHmi_Pb2_c)
  {
    fixRadioPacket[6]='2';
  }
  else if(boPbPushTrack & eHmi_Pb3_c)
  {
    fixRadioPacket[6]='3';
  }
  else if(boPbPushTrack & eHmi_Pb4_c)
  {
    fixRadioPacket[6]='4';
  }
  else
  {
    fixRadioPacket[6]='5';
  }

  vRadio_StartTx(pRadioConfiguration->Radio_ChannelNumber, (U8 *) fixRadioPacket);

  /* Packet sending initialized */
  return TRUE;
}
/*!
 * This function is used to compare the content of the received packet to a string.
 *
 * @return  None.
 */
BIT gSampleCode_StringCompare(U8* pbiPacketContent, U8* pbiString, U8 lenght)
{
  while(*pbiPacketContent++ == *pbiString++)
  {
    if( (--lenght) == 0 )
    {
      return TRUE;
    }
  }
  return FALSE;
}
#endif


