/*! @file radio.c
 * @brief This file contains functions to interface with the radio chip.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#include "..\bsp.h"

/*****************************************************************************
 *  Local Macros & Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variables
 *****************************************************************************/
const SEGMENT_VARIABLE(Radio_Configuration_Data_Array[], U8, SEG_CODE) = \
              RADIO_CONFIGURATION_DATA_ARRAY;

const SEGMENT_VARIABLE(RadioConfiguration, tRadioConfiguration, SEG_CODE) = \
                        RADIO_CONFIGURATION_DATA;

const SEGMENT_VARIABLE_SEGMENT_POINTER(pRadioConfiguration, tRadioConfiguration, SEG_CODE, SEG_CODE) = \
                        &RadioConfiguration;

SEGMENT_VARIABLE(fixRadioPacket[RADIO_MAX_PACKET_LENGTH], U8, SEG_XDATA);

/*****************************************************************************
 *  Local Function Declarations
 *****************************************************************************/
void vRadio_PowerUp(void);

/*!
 *  Power up the Radio.
 *
 *  @note
 *
 */
void vRadio_PowerUp(void)
{
  SEGMENT_VARIABLE(wDelay,  U16, SEG_XDATA) = 0u;

  /* Hardware reset the chip */
  si4455_reset();

  /* Wait until reset timeout or Reset IT signal */
  for (; wDelay < pRadioConfiguration->Radio_Delay_Cnt_After_Reset; wDelay++);
}

/*!
 *  Radio Initialization.
 *
 *  @author Sz. Papp
 *
 *  @note
 *
 */
void vRadio_Init(void)
{
  U16 wDelay;

  /* Power Up the radio chip */
  vRadio_PowerUp();

  /* Load radio configuration */
  while (SI4455_SUCCESS != si4455_configuration_init(pRadioConfiguration->Radio_ConfigurationArray))
  {
    /* Error hook */
#if !(defined SILABS_PLATFORM_WMB912)
    LED4 = !LED4;
#else
    vCio_ToggleLed(eHmi_Led4_c);
#endif
    for (wDelay = 0x7FFF; wDelay--; ) ;

    /* Power Up the radio chip */
    vRadio_PowerUp();
  }

  // Read ITs, clear pending ones
  si4455_get_int_status(0u, 0u, 0u);
}

/*!
 *  Check if Packet received IT flag is pending.
 *
 *  @return   TRUE - Packet successfully received / FALSE - No packet pending.
 *
 *  @note
 *
 */
BIT gRadio_CheckReceived(void)
{
  U8 lCnt;

  if (RF_NIRQ == FALSE)
  {
    /* Read ITs, clear pending ones */
    si4455_get_int_status(0u, 0u, 0u);

    /* check the reason for the IT */
    if (Si4455Cmd.GET_INT_STATUS.PH_PEND & SI4455_CMD_GET_INT_STATUS_REP_PACKET_RX_PEND_BIT)
    {
      /* Packet RX */
      si4455_read_rx_fifo(RadioConfiguration.Radio_PacketLength, (U8 *) &fixRadioPacket[0u]);

      /* Send it to UART */
      for (lCnt = 0u; lCnt < RadioConfiguration.Radio_PacketLength; lCnt++)
      {
        Comm_IF_SendUART(*((U8 *) &fixRadioPacket[0u] + lCnt));
      }
      Comm_IF_SendUART('\n');

      return TRUE;
    }

    /* Reset FIFO */
    si4455_fifo_info(0x02);
  }

  return FALSE;
}

/*!
 *  Check if Packet sent IT flag is pending.
 *
 *  @return   TRUE / FALSE
 *
 *  @note
 *
 */
BIT gRadio_CheckTransmitted(void)
{
  if (RF_NIRQ == FALSE)
  {
    /* Read ITs, clear pending ones */
    si4455_get_int_status(0u, 0u, 0u);

    /* check the reason for the IT */
    if (Si4455Cmd.GET_INT_STATUS.PH_PEND & SI4455_CMD_GET_INT_STATUS_REP_PACKET_SENT_PEND_BIT)
    {
      return TRUE;
    }
  }

  return FALSE;
}

/*!
 *  Set Radio to RX mode, fixed packet length.
 *
 *  @param channel Freq. Channel
 *
 *  @note
 *
 */
void vRadio_StartRX(U8 channel)
{
  // Read ITs, clear pending ones
  si4455_get_int_status(0u, 0u, 0u);

  /* Start Receiving packet, channel 0, START immediately, Packet n bytes long */
  si4455_start_rx(channel, 0u, RadioConfiguration.Radio_PacketLength,
                  SI4455_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_NOCHANGE,
                  SI4455_CMD_START_RX_ARG_RXVALID_STATE_ENUM_RX,
                  SI4455_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX );
}

/*!
 *  Set Radio to TX mode, fixed packet length.
 *
 *  @param channel Freq. Channel, Packet to be sent
 *
 *  @note
 *
 */
void  vRadio_StartTx(U8 channel, U8 *pioFixRadioPacket)
{
  // Read ITs, clear pending ones
  si4455_get_int_status(0u, 0u, 0u);

  /* Fill the TX fifo with datas */
  si4455_write_tx_fifo(RadioConfiguration.Radio_PacketLength, pioFixRadioPacket);

  /* Start sending packet, channel 0, START immediately, Packet n bytes long, go READY when done */
  si4455_start_tx(channel, 0x30,  RadioConfiguration.Radio_PacketLength);
}
