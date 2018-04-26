/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          DrvTimer_18F67J10.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvTimer_18F67J10.h $
 * $Archive: /MDXP600/192-000039 PCB/192-110276 Hella/Drivers/DrvTimer_18F67J10.h $
 * $History: DrvTimer_18F67J10.h $
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
 * User: Bbroer       Date: 1-12-10    Time: 18:13
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

#ifndef _DRV_TIMER_18F67J10_H_
#define _DRV_TIMER_18F67J10_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////

typedef enum {
   TIMER0_SEC_COUNTER_1 = 0,
   TIMER0_SEC_COUNTER_2 = 1,
   TIMER0_MS_COUNTER_1  = 2,
   TIMER0_MS_COUNTER_2  = 3,
   TIMER0_MS_COUNTER_BT  = 4
} _Timer0CounterId, *_Timer0CounterIdPtr;

typedef far rom void (*_IsrFunction)( void );
////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Timer 0 definitions
//

// Configuration values.
#define TIMER0_DISABLE              0
#define TIMER0_ENABLE               1

#define TIMER0_16BIT_COUNTER        0
#define TIMER0_8_BIT_COUNTER        1

#define TIMER0_CLKC_TRANSITION      0
#define TIMER0_T0CKI_TRANSITION     1

#define TIMER0_INC_ON_LOW_TO_HIGH   0
#define TIMER0_INC_ON_HIGH_TO_LOW   1

#define TIMER0_USE_PRESCALER        0  
#define TIMER0_BYPASS_PRESCALER     1
   
#define TIMER0_PRESCALER_2          0b000
#define TIMER0_PRESCALER_4          0b001
#define TIMER0_PRESCALER_8          0b010
#define TIMER0_PRESCALER_16         0b011
#define TIMER0_PRESCALER_32         0b100
#define TIMER0_PRESCALER_64         0b101
#define TIMER0_PRESCALER_128        0b110
#define TIMER0_PRESCALER_256        0b111

// Counter definitions.
// The counter must be set so that every 10ms an interrupt is generated. Since 
// the interrupt is generated on an overflow the initial counter value is the 
// maximum counter value minus the number of counts required. 
// For an acurate timer the counter should be compensated for the loss of
// instruction time when resetting the counter on interrupt.
// Prescaler input:        32MHz / 4   = 8MHz
// Prescaler output:       8MHz / 8    = 1MHz
// Single count:           1 / 1MHz    = 1us
// Counts per interrupt:   10ms / 1us  = 10000
#define TIMER0_COUNTS            2000       // 2ms
#define TIMER0_COUNTER_MAX       0xFFFF
#define TIMER0_COUNTER_START     (TIMER0_COUNTER_MAX - TIMER0_COUNTS)
#define TIMER0_COUNTER_LOW       (TIMER0_COUNTER_START & 0xFF)
#define TIMER0_COUNTER_HIGH      ((TIMER0_COUNTER_START >> 8) & 0xFF)
#define TIMER0_INTS_PER_SECOND   500

// Timer 0 counter definitions.
#define TIMER_SEC_COUNTER_1_FLAG    0b00000001
#define TIMER_SEC_COUNTER_2_FLAG    0b00000010
#define TIMER_MS_COUNTER_1_FLAG     0b00000100
#define TIMER_MS_COUNTER_2_FLAG     0b00001000
#define TIMER_MS_COUNTER_BT_FLAG   0b00010000
#define TIMER_COUNTER_FLAGS_CLEAR   0b00000000

//
// Timer 1 definitions
//

//
// Control registers status values.
// 

// T1CON: Timer 1 control register.
// TMR1ON: On bit.
#define TIMER1_DISABLE              0     // Stops timer 1.
#define TIMER1_ENABLE               1     // Enables timer 1.
//TMR1CS: Clock source select bit.
#define TIMER1_INTERNAL_CLOCK       0     // Internal clock (Fosc/4).
#define TIMER1_EXTERNAL_CLOCK       1     // External clock from pin RC0.
// T1SYNC: External clock input synchronization select bit.
#define TIMER1_SYNC                 0     // Synchronize external clock input.
#define TIMER1_NO_SYNC              1     // Do not synchronize external clock input.
// T1OSCEN: Oscillator enable bit.
#define TIMER1_DISABLE_OSCILLATOR   0     // Oscillator is shut off.
#define TIMER1_ENABLE_OSCILLATOR    1     // Oscillator is enabled.
// T1CKPS: Input clock prescale select bits.
#define TIMER1_PRESCALER_1          0b00  // 1:1 Prescale value.
#define TIMER1_PRESCALER_2          0b01  // 1:2 Prescale value.
#define TIMER1_PRESCALER_3          0b10  // 1:4 Prescale value.
#define TIMER1_PRESCALER_8          0b11  // 1:8 Prescale value.
//T1RUN: System clock status bit.
#define TIMER1_IS _NOT_DEVICE_CLOCK 0     // Device clock is derrived from another source.
#define TIMER1_IS_DEVICE_CLOCK      1     // Device clock is derrived from Timer 1 oscillator.
// RD16: 16-bit read/write mode enable bit.
#define TIMER1_DUAL_8_BIT_RW        0     // Enables register read/write in two 8-bit operations.
#define TIMER1_SINGLE_16_BIT_RW     1     // Enables register read/write in one 16-bit operation.

// Counter definitions.
// The counter must be set so that every 6.51us an interrupt is generated. Since 
// the interrupt is generated on an overflow the initial counter value is the 
// maximum counter value minus the number of counts required. 
// For an acurate timer the counter should be compensated for the loss of
// instruction time when resetting the counter on interrupt.
// Prescaler input:           32MHz / 4         = 8MHz
// Prescaler output:          8MHz / 1          = 8MHz
// Single count:              1 / 8MHz          = 125ns
//
// Bit time @ 9600 baud:      1 / 9600          = 104.17us
// 8/16th bit time:           104.17us / 16 * 8 =  52.08us
// 3/16th bit time:           104.17us / 16 * 3 =  19.53us
// 5/16th bit time:           104.17us / 16 * 5 =  32.55us
// 
// Bit counter:               104.17us / 125ns  = 833.36
// 8/16th bit counter:         52.08us / 125ns  = 416.4
// 3/16th bit counter:         19.53us / 125ns  = 156.24
// 5/16th bit counter:         32.55us / 125ns  = 260.4
#define TIMER1_COUNTER_MAX             0xFFFF

#define TIMER1_BIT_COUNTS                 (833 - 47 - 16 - 8)
#define TIMER1_BIT_COUNTER_START          (TIMER1_COUNTER_MAX - TIMER1_BIT_COUNTS)
#define TIMER1_BIT_COUNTER_LOW            (TIMER1_BIT_COUNTER_START & 0xFF)
#define TIMER1_BIT_COUNTER_HIGH           ((TIMER1_BIT_COUNTER_START >> 8) & 0xFF)

#define TIMER1_8_16TH_BIT_COUNTS          (416 - 10)
#define TIMER1_8_16TH_BIT_COUNTER_START   (TIMER1_COUNTER_MAX - TIMER1_8_16TH_BIT_COUNTS)
#define TIMER1_8_16TH_BIT_COUNTER_LOW     (TIMER1_8_16TH_BIT_COUNTER_START & 0xFF)
#define TIMER1_8_16TH_BIT_COUNTER_HIGH    ((TIMER1_8_16TH_BIT_COUNTER_START >> 8) & 0xFF)

#define TIMER1_3_16TH_BIT_COUNTS          (156 - 12)
#define TIMER1_3_16TH_BIT_COUNTER_START   (TIMER1_COUNTER_MAX - TIMER1_3_16TH_BIT_COUNTS)
#define TIMER1_3_16TH_BIT_COUNTER_LOW     (TIMER1_3_16TH_BIT_COUNTER_START & 0xFF)
#define TIMER1_3_16TH_BIT_COUNTER_HIGH    ((TIMER1_3_16TH_BIT_COUNTER_START >> 8) & 0xFF)

#define TIMER1_5_16TH_BIT_COUNTS          (260 - 44 - 16 - 8)
#define TIMER1_5_16TH_BIT_COUNTER_START   (TIMER1_COUNTER_MAX - TIMER1_5_16TH_BIT_COUNTS)
#define TIMER1_5_16TH_BIT_COUNTER_LOW     (TIMER1_5_16TH_BIT_COUNTER_START & 0xFF)
#define TIMER1_5_16TH_BIT_COUNTER_HIGH    ((TIMER1_5_16TH_BIT_COUNTER_START >> 8) & 0xFF)

#define TIMER1_INT_FLAG                   PIR1bits.TMR1IF

//
// Timer 2 definitions
//

// Configuration values.
#define TIMER2_DISABLE              0
#define TIMER2_ENABLE               1

#define TIMER2_PRESCALER_1          0b00
#define TIMER2_PRESCALER_4          0b01
#define TIMER2_PRESCALER_16         0b10

#define TIMER2_POSTSCALER_1         0b0000
#define TIMER2_POSTSCALER_2         0b0001
#define TIMER2_POSTSCALER_3         0b0010
#define TIMER2_POSTSCALER_4         0b0011
#define TIMER2_POSTSCALER_5         0b0100
#define TIMER2_POSTSCALER_6         0b0101
#define TIMER2_POSTSCALER_7         0b0110
#define TIMER2_POSTSCALER_8         0b0111
#define TIMER2_POSTSCALER_9         0b1000
#define TIMER2_POSTSCALER_10        0b1001
#define TIMER2_POSTSCALER_11        0b1010
#define TIMER2_POSTSCALER_12        0b1011
#define TIMER2_POSTSCALER_13        0b1100
#define TIMER2_POSTSCALER_14        0b1101
#define TIMER2_POSTSCALER_15        0b1110
#define TIMER2_POSTSCALER_16        0b1111

// Counter definitions.
// The counter must be set so that every 200us an interrupt is generated. 
//
// Prescaler input:        32MHz / 4   = 8MHz
// Prescaler output:       8MHz / 16   = 500kHz
// Single count:           1 / 500kHz  = 2us
// Counts per interrupt:   200us / 2us = 100
// Postscaler:             1:1
#define TIMER2_COUNTS               100

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

#define TIMER1_SET_MODE( Mode )           (T1CONbits.TMR1ON = Mode)
#define TIMER1_SET_COUNTER( High, Low )   {TMR1H = High; TMR1L = Low;}

////////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

extern _IsrFunction   IsrFunction;

extern UINT8 Timer0SecCounter1;
extern UINT8 Timer0SecCounter2;

void  DrvTimer0Init( void );
void  DrvTimer0Isr( void );
void  DrvTimer0SetCounter( _Timer0CounterId Counter, UINT16 Value );
void  DrvTimer0Reset(void);
_Bool DrvTimer0CounterDone( _Timer0CounterId Counter );

void  DrvTimer1Init( void );
void  DrvTimer1Isr( void );


void  DrvTimer2Init( void );
void  DrvTimer2Isr( void );

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif





