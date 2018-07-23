
#include "..\bsp.h"

#define PACKET_SEND_INTERVAL  250u



// Power Management Bit Definitions
#define SLEEP        0x80              // Sleep Mode Select
#define SUSPEND      0x40              // Suspend Mode Select
#define CLEAR        0x20              // Wake-Up Flag Clear
#define RSTWK        0x10              // Reset Pin Falling Edge Wake-Up
#define RTCFWK       0x08              // SmaRTClock Failure Wake-Up
#define RTCAWK       0x04              // SmaRTClock Alarm Wake-Up
#define PMATWK       0x02              // Port Match Wake-Up
#define CPT0WK       0x01              // Comparator0 Wake-Up

// Friendly names for the LPM function arguments
#define PORT_MATCH   PMATWK
#define RTC          RTCFWK + RTCAWK
#define COMPARATOR   CPT0WK

// FLSCL Bit Definition
#define BYPASS    0x40
#define NON_ZERO  0x01



//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

// Variables used for the RTC interface
U8 PMU0CF_Local;                       // Holds the desired Wake-up sources
 
// Define Wake-Up Flags
U8 RTC_Alarm;
U8 RTC_Failure;
U8 Comparator_Wakeup;
U8 Port_Match_Wakeup;

void LPM_Init (void)
{
  PMU0CF = CLEAR;
  PMU0CF_Local = 0;
  RTC_Alarm = 0;
  RTC_Failure = 0;
  Comparator_Wakeup = 0;
  Port_Match_Wakeup = 0;
  P2MDOUT |= 0x01;
}

void LPM_Enable_Wakeup(U8 wakeup)
{
  PMU0CF_Local |= (wakeup & (RTC | PORT_MATCH | COMPARATOR));
}

void LPM_Disable_Wakeup (U8 wakeup)
{
  PMU0CF_Local &= ~(wakeup & (RTC | PORT_MATCH | COMPARATOR));
}


void LPM(U8 mode)
{
   U8 b;
   U8 CLKSEL_save;
   U8 EA_save;
   U8 PMU0CF_snapshot;
   U8 RTC0CN_snapshot;
   
   // Save current interrupt state and disable interrupts 
   EA_save = EA;
   EA = 0;
   
   // Save current system clock selection and select the low power oscillator
   // divided by 2 as the system clock
   CLKSEL_save = CLKSEL;
   CLKSEL = 0x14;
   
   // Enable the Flash read one-shot timer   
   FLSCL &= ~BYPASS;                   // Clear the one-shot bypass bit
   FLWR  =   NON_ZERO;                 // Write a "dummy" value to FLWR
   
   // Verify that the system clock setting has been applied
   while(!(CLKSEL & 0x80));            // Wait until CLKRDY -> 1
   

   //----------------------------------
   // ~~~ Device in Low Power Mode ~~~
   //
       PMU0CF = (mode | PMU0CF_Local);
   //
   // ~~~   Device is now Awake    ~~~
   //----------------------------------

   // Restore the System Clock
   CLKSEL = CLKSEL_save;

   
   // Disable (Bypass) the Flash Read one-shot timer if the system clock
   // frequency is higher than 10 MHz
   // if(SYSCLK > 10000000)
   {
      FLSCL |= BYPASS;                 // Set the one-shot bypass bit                     
   }
  
   // Capture the wake-up source and clear all wake-up source flags   
   PMU0CF_snapshot = PMU0CF;
   PMU0CF = CLEAR;

   // Check for a Port Match Wakeup
   if(PMU0CF_snapshot & PMATWK)
   {
      Port_Match_Wakeup = 1;  
   }
   // Restore Interrupt State
   EA = EA_save;
   
   // Check for a reset pin Wakeup
   if(PMU0CF_snapshot & RSTWK)
   {
      // Delay 15uS per datasheet recommendation
      for(b = 255; b > 0; b--);
   }
   // */
}               


/*------------------------------------------------------------------------*/
/*                          Local variables                               */
/*------------------------------------------------------------------------*/
SEGMENT_VARIABLE(lPer_SecCntr, U32, SEG_DATA);  /**< Demo sec time holder */
SEGMENT_VARIABLE(transmittCount, U16, SEG_DATA);  /**< Demo sec time holder */
SEGMENT_VARIABLE(lPktSending, U8, SEG_DATA);
SEGMENT_VARIABLE(sendingData, U8, SEG_DATA);

/*------------------------------------------------------------------------*/
/*                      Local function prototypes                         */
/*------------------------------------------------------------------------*/
void vPlf_McuInit        (void);
void vInitializeHW       (void);
void DemoApp_Pollhandler (void);

void OSCILLATOR_Init (void)
{
   RSTSRC = 0x06;                      // Enable missing clock detector and
                                       // leave VDD Monitor enabled.
   CLKSEL = 0x04;                      // Select low power internal osc.
                                       // divided by 1 as the system clock
   FLSCL |= 0x40;                      // Set the BYPASS bit for operation > 10MHz
}

void wakeupPORT_Init (void)
{
   P0MDIN |= 0x04;                     // P0.2 are digital
   P0MDOUT &= ~0x04;                   // P0.2 are open-drain
   P0     |= 0x04;                     // Set P0.2, P0.3 latches to '1'

   P1MDIN |= 0x70;                     // P1.4, P1.5, P1.6 are digital
   P1MDOUT |= 0x70;                    // P1.4, P1.5, P1.6 are push-pull


   LED1 = 1;
   LED2 = 1;
   LED3 = 1;

   // Setup the Port Match Wake-up Source to wake up on the falling
   // edge of P0.2 (when the switch is pressed)
   P0MASK = 0x04;                      // Mask out all pins except for P0.2
   P0MAT = 0x04;                       // P0.2 should be HIGH while the device
                                       // is in the low power mode

   XBR2    = 0x40;                     // Enable crossbar and enable
                                       // weak pull-ups
}

void main(void)
{
  // initiazlie for only sleep and wakeup interrupt
  OSCILLATOR_Init();                 // Initialize Oscillator
  wakeupPORT_Init();
  LPM_Init();                         // Initialize Power Management
  LPM_Enable_Wakeup(PORT_MATCH);      // Enable Port Match wake-up source
  EA = 1;                             // Enable global interrupts
  // enable sleep 
  LPM(SUSPEND);

  // vInitializeHW();
  lPktSending = 0u;
  sendingData = 0u;
  while (TRUE)
  {
    if(Port_Match_Wakeup)
    {
      Port_Match_Wakeup = 0;        // Reset Port Match Flag to indicate 
                                    // that we have detected an event
      // Initialize the Hardware and Radio
      vInitializeHW();
      sendingData = 1u;
      // LED1 = 0;
    }
    // The following Handlers requires care on invoking time interval
    if (wIsr_Timer2Tick)
    {
      if (lPer_SecCntr < 0xFFFFFFF)
        lPer_SecCntr++;
      wIsr_Timer2Tick = FALSE;
      // vHmi_PbHandler();
      // vHmi_LedHandler();

    }

    if(sendingData)
    {
      // Check if the radio packet sent successfully
      if (TRUE == gRadio_CheckTransmitted())
      {
        lPktSending = 0u;
      }
      if ((lPer_SecCntr >= PACKET_SEND_INTERVAL) && (0u == lPktSending))
      {
        if(transmittCount < 5u)
        {
          vSampleCode_SendFixPacket();
          lPer_SecCntr = 0u;
          lPktSending = 1u;
		      transmittCount++;
        }
        else
        {
          sendingData = 0u;
          transmittCount = 0;
          OSCILLATOR_Init();                 // Initialize Oscillator
          wakeupPORT_Init();
          LPM_Init();                         // Initialize Power Management
          LPM_Enable_Wakeup(PORT_MATCH);      // Enable Port Match wake-up source
          EA = 1;                             // Enable global interrupts
          LPM(SUSPEND);
        }
      }
    }
    else
    {
      OSCILLATOR_Init();                 // Initialize Oscillator
      wakeupPORT_Init();
      LPM_Init();                         // Initialize Power Management
      LPM_Enable_Wakeup(PORT_MATCH);      // Enable Port Match wake-up source
      EA = 1;                             // Enable global interrupts
      LPM(SUSPEND);
    } // */
  }

}

/**
 *  Demo Application Poll-Handler
 *
 *  @note This function must be called periodically.
 *
 */
void DemoApp_Pollhandler()
{

  
}

/**
 *  Calls the init functions for the used peripherals/modules
 *
 *  @note Should be called at the beginning of the main().
 *
 */
void vInitializeHW()
{
  // Initialize the MCU peripherals
  vPlf_McuInit();

  // Initialize IO ports
  vCio_InitIO();

  // Start Timer2 peripheral with overflow interrupt
  vTmr_StartTmr2(eTmr_SysClkDiv12_c, wwTmr_Tmr2Periode.U16, TRUE, bTmr_TxXCLK_00_c);

  // Start the push button handler
  vHmi_InitPbHandler();

  // Start the Led handler
  vHmi_InitLedHandler();

  // Initialize the Radio
  vRadio_Init();

  // Enable configured interrupts
  mIsr_EnableAllIt();
}

//
void vPlf_McuInit(void)
{
  U16 wDelay = 0xFFFF;

  /* disable F930 watchdog */
  PCA0MD &= (~M_WDTE);

  /* Init Internal Precision Oscillator (24.5MHz) */
  SFRPAGE = LEGACY_PAGE;
  FLSCL   = M_BYPASS;

  OSCICN |= M_IOSCEN; // p7: Internal Prec. Osc. enabled
  CLKSEL  = 0x00;     // Int. Prec. Osc. selected (24.5MHz)

  /* P0: 4,7 push-pull */
  /* P1: 0,2,3,4,5,6 push-pull */
  P0MDOUT   = 0x90;
  P1MDOUT   = 0x7D;

  /* P0: 0,1,2,3,4,7 skipped */
  /* P1: 3,4,5,6 skipped */
  P0SKIP    = 0x9F;
  P1SKIP    = 0x78;

  /* Set SMBUS clock speed */
  Set115200bps_24MHZ5;
  /* Start Timer1 */
  TR1 = 1;
  /* Initialize SMBus */
  vSmbus_InitSMBusInterface();

  P0MDIN  = 0xFF; // All pin configured as digital port
  P1MDIN  = 0xFF; // All pin configured as digital port

  /* Set Drive Strenght */
  SFRPAGE = CONFIG_PAGE;
  P0DRV   = 0x00;
  P1DRV   = 0x00;

  SFRPAGE = LEGACY_PAGE;
  /* Crossbar configuration */
  XBR0    = M_URT0E | M_SMB0E; //p0: UART enabled on XBAR
  XBR1    = M_SPI1E ; //p6: SPI1 enabled on XBAR

  XBR2    = M_XBARE; //p6: XBAR enable

  /* latch all inputs to '1' */
  P0      = ~P0MDOUT;
  P1      = ~P1MDOUT;

  /* set all output to its default state */
  LED1      = EXTINGUISH;
  RF_NSEL   = TRUE;
  RF_PWRDN  = FALSE;

  SPI1CFG   = 0x40;
  SPI1CN    = 0x01;
  SPI1CKR   = 0x0B;
  /* De-select radio SPI */
  vSpi_SetNsel(eSpi_Nsel_RF);
#if ((defined SILABS_LCD_DOG_GLCD) || (defined SILABS_MCU_DC_EMIF_F930) || (defined SILABS_PLATFORM_WMB))
  /* De-select LCD SPI */
  vSpi_SetNsel(eSpi_Nsel_LCD);

  LCD_A0    = FALSE;
#endif

  /* Startup delay */
  for (; wDelay; wDelay--)  ;

}

#ifdef SDCC
/**
 * \brief External startup function of SDCC.
 *
 * It performs operations
 * prior static and global variable initialization.
 * Watchdog timer should be disabled this way, otherwise it
 * can expire before variable initialization is carried out,
 * and may prevent program execution jumping into main().
 *
 * \param None
 * \return None
 */
void _sdcc_external_startup(void)
{
  PCA0MD &= ~0x40;      // Disable Watchdog timer
}
#endif
