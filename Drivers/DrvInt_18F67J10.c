/*******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:          
 *
 * Designed by:   Kees Hemmes
 * 
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
#include "DrvInt_18F67J10.h"
#include "DrvTimer_18F67J10.h"
#include "DrvUsart_18F67J10.h"
#include "Bootload.h"
#include "Appdata.h"

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

////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
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
// 07/08/15    KC         Developed
// 02/01/2018  CH         jump 
//

#define USE_BOOT_LOADER

#pragma interrupt IntIsrHigh

void IntIsrHigh( void )
{
   //do not use in the boot loader
}

//
// The following defines the interrupt vector for the high level interrupt.
//

#pragma code high_vector=0x08

void IntVectorHigh( void )
{
/*#ifdef USE_BOOT_LOADER
   _asm GOTO (P18F87_FLASH_START_ADDRESS + 0x08) _endasm //location of the application interrupt vector   
#else
   _asm GOTO IntIsrHigh _endasm
#endif*/
                                      
_asm                                   
BTFSC WDTCONbits, 0, 0
GOTO (P18F87_FLASH_START_ADDRESS + 0x08)
GOTO IntIsrHigh
_endasm

}

#pragma code

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

#pragma interruptlow IntIsrLow

void IntIsrLow( void )
{
   if( INTCONbits.TMR0IF && INTCONbits.TMR0IE )
    {
       DrvTimer0Isr();

      INTCONbits.TMR0IF = INT_FLAG_CLEAR;
   }

   if( PIR1bits.RC1IF && PIE1bits.RC1IE )
   {
       DrvUsart1Isr();

      PIR1bits.RC1IF = INT_FLAG_CLEAR;
   }
    
   if( PIR3bits.RC2IF && PIE3bits.RC2IE )
   {
       DrvUsart2Isr();

      PIR3bits.RC2IF = INT_FLAG_CLEAR;
   }

   if( INTCONbits.RBIF && INTCONbits.RBIE )
    {
       //DrvPriMotorIsr();

      INTCONbits.RBIF = INT_FLAG_CLEAR;
   }

}


//
// The following defines the interruopt vector for the low level interrupt.
//

#pragma code low_vector=0x18

void IntVectorLow( void )
{
/*#ifdef USE_BOOT_LOADER
   _asm GOTO (P18F87_FLASH_START_ADDRESS + 0x18) _endasm  //location of the application interrupt vector
#else
   _asm GOTO IntIsrLow _endasm
#endif*/

_asm                                   
BTFSC WDTCONbits, 0, 0
GOTO (P18F87_FLASH_START_ADDRESS + 0x18)
GOTO IntIsrLow
_endasm  

}


#pragma code


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

void DrvIntInit( void ) 
{
   // Disable all interrupts.
   INTCONbits.GIEH      = INT_DISABLE;  // Disbable all high priority interrupts.
   INTCONbits.GIEL      = INT_DISABLE;  // Disbable all low priority interrupts.

   // Clear all interrupt control registers.
   INTCON   = 0b00000000;
   INTCON2  = 0b00000000;
   INTCON3  = 0b00000000;
   // Clear all peripheral interrupt request.
   PIR1     = 0b00000000;
   PIR2     = 0b00000000;
   PIR3     = 0b00000000;
   // Disable all peripheral interrupts.
   PIE1     = 0b00000000;
   PIE2     = 0b00000000;
   PIE3     = 0b00000000;
   // Set all peripheral interrupt priorities to low.
   IPR1     = 0b00000000;
   IPR2     = 0b00000000;
   IPR3     = 0b00000000;

   // Timer 0 interrupt settings.
   INTCON2bits.TMR0IP   = INT_PRIORITY_LOW;
   INTCONbits.TMR0IE    = INT_DISABLE;  
   INTCONbits.TMR0IF    = INT_FLAG_CLEAR;

   // Timer 1 interrupt settings.
   IPR1bits.TMR1IP      = INT_PRIORITY_LOW;
   PIE1bits.TMR1IE      = INT_DISABLE;  
   PIR1bits.TMR1IF      = INT_FLAG_CLEAR;

   // Timer 2 interrupt settings.
   IPR1bits.TMR2IP      = INT_PRIORITY_HIGH;
   PIE1bits.TMR2IE      = INT_DISABLE;  
   PIR1bits.TMR2IF      = INT_FLAG_CLEAR;
   
   // USART 1 interrupt settings.
   IPR1bits.RC1IP       = INT_PRIORITY_LOW;
   PIE1bits.RC1IE       = INT_DISABLE;  
   PIR1bits.RC1IF       = INT_FLAG_CLEAR;

   // USART 2 interrupt settings.
   IPR3bits.RC2IP       = INT_PRIORITY_LOW;
   PIE3bits.RC2IE       = INT_DISABLE;  
   PIR3bits.RC2IF       = INT_FLAG_CLEAR;

   // Port B change interrupt settings.
   INTCON2bits.RBIP     = INT_PRIORITY_LOW;
   INTCONbits.RBIE      = INT_DISABLE;  
   INTCONbits.RBIF      = INT_FLAG_CLEAR;

   // Enable priority levels on interrupts.
   RCONbits.IPEN        = INT_PRIORITY_LEVELS_ENABLE;     

   // INTCON
   INTCONbits.GIEL      = INT_ENABLE;  // Enable all low priority interrupts.
   INTCONbits.GIEH      = INT_ENABLE;  // Enable all high priority interrupts.
}

//
//
//

void DrvIntEnable( _IntId Id, _Bool Enable )
{
   BIT   Mode;

   Mode = (Enable ? INT_ENABLE : INT_DISABLE);

   switch( Id )
   {
      case INT_ID_TIMER0:
         INTCONbits.TMR0IF = INT_FLAG_CLEAR;
         INTCONbits.TMR0IE = Mode;
         break;
      case INT_ID_TIMER1:
         PIR1bits.TMR1IF   = INT_FLAG_CLEAR;
         PIE1bits.TMR1IE   = Mode;  
         break;
      case INT_ID_TIMER2:
         PIR1bits.TMR2IF   = INT_FLAG_CLEAR;
         PIE1bits.TMR2IE   = Mode;  
         break;
      case INT_ID_USART_1_RX:
         PIR1bits.RC1IF    = INT_FLAG_CLEAR;
         PIE1bits.RC1IE    = Mode;  
         break;
      case INT_ID_USART_2_RX:
         PIR3bits.RC2IF    = INT_FLAG_CLEAR;
         PIE3bits.RC2IE    = Mode;  
         break;
      case INT_ID_RB:
         INTCONbits.RBIF   = INT_FLAG_CLEAR;
         INTCONbits.RBIE   = Mode;  
         break;
      case INT_ID_ALL:
         INTCONbits.TMR0IF = INT_FLAG_CLEAR;
         INTCONbits.RBIF   = INT_FLAG_CLEAR;
         PIR1              = 0b00000000;
         PIR2              = 0b00000000;
         PIR3              = 0b00000000;
         INTCONbits.GIE    = Mode;
   };
}
         
