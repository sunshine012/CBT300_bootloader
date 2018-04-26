/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvTimer_18F67J10.c $
 * $Archive: /MDXP600/192-000039 PCB/192-110276 Hella/Drivers/DrvTimer_18F67J10.c $
 * $History: DrvTimer_18F67J10.c $
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 5/29/12    Time: 6:02a
 * Created in $/MDXP600/192-000039 PCB/192-110276 Hella/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 10/03/11   Time: 4:14a
 * Created in $/MDXP600/192-000039 PCB/192-110276 Hella/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Abremen      Date: 4/19/11    Time: 8:38a
 * Created in $/MDXP600/192-000039 PCB/192-110240 MDX-645P_YUASA/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 1-12-10    Time: 18:11
 * Created in $/MDXP600/192-000039 PCB/192-110223 MDX-645P KRAMP/Drivers/Standard
 * Added driver files from the master
 * 
 * *****************  Version 2  *****************
 * User: Rick         Date: 2/29/08    Time: 4:42p
 * Updated in $/MDXP600/192-000039 PCB/Master/Drivers/Standard
 * File comment format for Source Safe
 * 
 * *****************  Version 1  *****************
 * User: Rick         Date: 2/26/08    Time: 8:04a
 * Created in $/MDXP600/192-000039 PCB/Master/Drivers
 *
 * Description:
 *
 * References:
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
//#include "AppData.h"
//#include "DrvCca.h"
#include "DrvInt_18F67J10.h"
#include "DrvKey.h"
#include "DrvTimer_18F67J10.h"
//#include "DrvCca.h"


////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////

UINT8    Timer0IntCounter;

UINT8    Timer0SecCounter1;
UINT8    Timer0SecCounter2;

UINT16   Timer0MsCounter1;
UINT16   Timer0MsCounter2;

UINT16   Timer0MsBTCounter;


UINT8     Timer0CounterFlags;

_IsrFunction   IsrFunction;
////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Function:      
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvTimer0Init( void ) 
{
   // Disable the timer.
   T0CONbits.TMR0ON  = TIMER0_DISABLE;             // On/Off control.

   // Reset the software timers.
   Timer0IntCounter     = 0;
   Timer0MsCounter1     = 0;
   Timer0MsCounter2     = 0;  
   Timer0SecCounter1    = 0;
   Timer0SecCounter2    = 0;  
   Timer0MsBTCounter   = 0;

   Timer0CounterFlags   = TIMER_COUNTER_FLAGS_CLEAR;
   
   // Configure the timer.
   T0CONbits.T08BIT  = TIMER0_16BIT_COUNTER;       // 8-bit/16-bit control.
   T0CONbits.T0CS    = TIMER0_CLKC_TRANSITION;     // Clock source select.
   T0CONbits.PSA     = TIMER0_USE_PRESCALER;       // Prescaler assignment.
   T0CONbits.T0PS    = TIMER0_PRESCALER_8;         // Prescaler selection.

   // Initialize the counter, high byte MUST be written first.
   TMR0H = TIMER0_COUNTER_HIGH;
   TMR0L = TIMER0_COUNTER_LOW;
   
   // Enable the timer interupt.
   DrvIntEnable( INT_ID_TIMER0, TRUE );

   // Enable the timer.
   T0CONbits.TMR0ON  = TIMER0_ENABLE; // On/Off control.
}

//
// Function:      10ms interrupt handle
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvTimer0Isr( void )// 10ms Timer
{

   // Reset the counter.
   TMR0H = TIMER0_COUNTER_HIGH;
   TMR0L = TIMER0_COUNTER_LOW;

   // Call the key scan function.
   //DrvKeyScan10msIsr();   

   // Increment interrupt counter and call 
   if( ++Timer0IntCounter == TIMER0_INTS_PER_SECOND )
   {
      Timer0IntCounter = 0;

      if( Timer0SecCounter1 ) 
      {
         Timer0SecCounter1--;
      }
      else
      {
         Timer0CounterFlags |= TIMER_SEC_COUNTER_1_FLAG;
      }

      if( Timer0SecCounter2 ) 
      {
         Timer0SecCounter2--;
      }
      else
      {
         Timer0CounterFlags |= TIMER_SEC_COUNTER_2_FLAG;
      }
   }

   // Decrement the software timers if larger than zero.
   if( Timer0MsCounter1 ) 
   {
      Timer0MsCounter1--;
   }
   else
   {
      Timer0CounterFlags |= TIMER_MS_COUNTER_1_FLAG;
   }

   if( Timer0MsCounter2 )
   {
      Timer0MsCounter2--;
   }
   else
   {
      Timer0CounterFlags |= TIMER_MS_COUNTER_2_FLAG;
   }
   if( Timer0MsBTCounter )
   {
      Timer0MsBTCounter--;
   }
   else
   {
      	Timer0CounterFlags |= TIMER_MS_COUNTER_BT_FLAG;
   }
   
}

void DrvTimer0SetCounter( _Timer0CounterId Counter, UINT16 Value )
{
   DrvIntEnable( INT_ID_TIMER0, FALSE );

   switch( Counter )
   {
      case TIMER0_SEC_COUNTER_1:
         Timer0SecCounter1     = Value ;
         Timer0CounterFlags   &= ~TIMER_SEC_COUNTER_1_FLAG;
         break;
      case TIMER0_SEC_COUNTER_2:
         Timer0SecCounter2     = Value ;
         Timer0CounterFlags   &= ~TIMER_SEC_COUNTER_2_FLAG;
         break;
      case TIMER0_MS_COUNTER_1:
         Timer0MsCounter1      = Value / 2;
         Timer0CounterFlags   &= ~TIMER_MS_COUNTER_1_FLAG;

         break;
      case TIMER0_MS_COUNTER_2:
         Timer0MsCounter2      = Value / 2;
         Timer0CounterFlags   &= ~TIMER_MS_COUNTER_2_FLAG;
         break;
      case TIMER0_MS_COUNTER_BT:
         Timer0MsBTCounter      = Value / 2;
         Timer0CounterFlags   &= ~TIMER_MS_COUNTER_BT_FLAG;
         break;		 
   }

   DrvIntEnable( INT_ID_TIMER0, TRUE );
}

void DrvTimer0Reset(void)
{
    // Reset the counter.
    TMR0H = TIMER0_COUNTER_HIGH;
    TMR0L = TIMER0_COUNTER_LOW;
}

_Bool DrvTimer0CounterDone( _Timer0CounterId Counter )
{
   UINT16 Result;

   switch( Counter )
   {
      case TIMER0_SEC_COUNTER_1:
         Result = Timer0CounterFlags & TIMER_SEC_COUNTER_1_FLAG;
         break;
      case TIMER0_SEC_COUNTER_2:
         Result = Timer0CounterFlags & TIMER_SEC_COUNTER_2_FLAG;
         break;
      case TIMER0_MS_COUNTER_1:
         Result = Timer0CounterFlags & TIMER_MS_COUNTER_1_FLAG;
         break;
      case TIMER0_MS_COUNTER_2:
         Result = Timer0CounterFlags & TIMER_MS_COUNTER_2_FLAG;
         break;
      case TIMER0_MS_COUNTER_BT:
         Result = Timer0CounterFlags & TIMER_MS_COUNTER_BT_FLAG;
         break;		 
      default:
         Result = FALSE;
         break;
   }

   return( Result );
}

// 
// Timer 1 functions.
//

//
// Function:      
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvTimer1Init( void ) 
{
   // Disable the timer.
   T1CONbits.TMR1ON  = TIMER1_DISABLE;

   // Configure the timer.
   T1CONbits.TMR1CS  = TIMER1_INTERNAL_CLOCK ;
   T1CONbits.T1OSCEN = TIMER1_DISABLE_OSCILLATOR;
   T1CONbits.T1CKPS  = TIMER1_PRESCALER_1;
   T1CONbits.RD16    = TIMER1_SINGLE_16_BIT_RW;

   // Enable the timer.
   T1CONbits.TMR1ON  = TIMER1_DISABLE;
}

void DrvEnableTimer1( _Bool Mode )
{
   // Reset the counter, high byte MUST be written first.
   

   //DrvIrda16thBitIsr();
}

//
// Function:      200us Timer interrupt
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvTimer2Init( void ) // 200us Timer
{
   // Disable the timer.
   T2CONbits.TMR2ON  = TIMER2_DISABLE;             // On/Off control.

   // Configure the timer.
   T2CONbits.T2CKPS  = TIMER2_PRESCALER_16;        // Clock prescale select bits.
   T2CONbits.T2OUTPS = TIMER2_POSTSCALER_1;        // Output postscaler select bits.
   PR2               = TIMER2_COUNTS;              // Period register.

   // Initialize the counter.
   TMR2              = 0;
   
   // Enable the timer.
   T2CONbits.TMR2ON  = TIMER2_ENABLE;              // On/Off control.
}

//
// Function:      
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvTimer2Isr( void )
{
   //check for valid Isr function address
     //IsrFunction();
   //DrvCcaIsr();
}

