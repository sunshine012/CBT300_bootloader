/******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          MdxP600.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: MdxP600.h $
 * $Archive: /MDXP600/BootLoader/Application/MdxP600.h $
 * $History: MdxP600.h $
 * 
 * *****************  Version 1  *****************
 * User: Rick         Date: 1/24/08    Time: 8:20a
 * Created in $/MDXP600/BootLoader/Application
 *
 * Description:
 *
 * References:
 *
 * 
 *
*******************************************************************************/

#ifndef _MDXP600_H
#define _MDXP600_H

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"

#include <delays.h>

////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

//
// I/O pin definitions.
//
// The following defines MDX names for the IO pins. The MDX names refer to the 
// names on the schematic.
//

// Port A
#define MDX_VDIFF1_IO				  	PORT_BIT( A, 0 )
#define MDX_IDIFF_IO					PORT_BIT( A, 1 )
#define MDX_D_GND_IO					PORT_BIT( A, 2 )
#define MDX_VREF_POS_IO			  	PORT_BIT( A, 3 )
#define MDX_RA4_IO		      				PORT_BIT( A, 4 )
#define MDX_AB_VOLTS_IO				PORT_BIT( A, 5 )

#define MDX_VDIFF1_TRIS				TRIS_BIT( A, 0 )
#define MDX_IDIFF_TRIS					TRIS_BIT( A, 1 )
#define MDX_D_GND_TRIS					TRIS_BIT( A, 2 )
#define MDX_VREF_POS_TRIS				TRIS_BIT( A, 3 )
#define MDX_RA4_TRIS		    			TRIS_BIT( A, 4 )
#define MDX_ABVOLTS_TRIS				TRIS_BIT( A, 5 )
		
// Port B 
#define MDX_RB0_IO					  	PORT_BIT( B, 0 )
#define MDX_SW1_IO    					PORT_BIT( B, 1 )// UP Key
#define MDX_RB2_IO    					PORT_BIT( B, 2 )
#define MDX_SW3_IO    					PORT_BIT( B, 3 )// Enter Key
#define MDX_RB4_IO    					PORT_BIT( B, 4 )
#define MDX_SW2_IO		        			PORT_BIT( B, 5 )// Down Key
#define MDX_PGC_IO					  	PORT_BIT( B, 6 )
#define MDX_PGD_IO					  	PORT_BIT( B, 7 )
#define MDX_KEY_IO            				PORTB

#define MDX_RB0_TRIS					TRIS_BIT( B, 0 )
#define MDX_SW1_TRIS    				TRIS_BIT( B, 1 )
#define MDX_RB2_TRIS  					TRIS_BIT( B, 2 )
#define MDX_SW3_TRIS    				TRIS_BIT( B, 3 )
#define MDX_RB4_TRIS    					TRIS_BIT( B, 4 )
#define MDX_SW2_TRIS	  	    			TRIS_BIT( B, 5 )
#define MDX_PGC_TRIS					TRIS_BIT( B, 6 )
#define MDX_PGD_TRIS					TRIS_BIT( B, 7 )

#define MDX_KEY_IO               PORTB

// Port C
#define MDX_TESTOSC_IO				   	PORT_BIT( C, 0 ) // TESTOSC CLOCK PWM
#define MDX_RC1_IO		       			PORT_BIT( C, 1 ) // CALIBATION CALLMODE
#define MDX_CALMODE_IO               		PORT_BIT( C, 2 )
#define MDX_SCK_IO               				PORT_BIT( C, 3 )
#define MDX_MISO_IO               			PORT_BIT( C, 4 )
#define MDX_MOSI_IO               			PORT_BIT( C, 5 )
#define MDX_TX1_IO				       	PORT_BIT( C, 6 )
#define MDX_RX1_IO				       	PORT_BIT( C, 7 )
#define MDX_TX1_RELAY0_IO				PORT_BIT( C, 6 )
#define MDX_RX1_RELAY1_IO				PORT_BIT( C, 7 )

#define MDX_TESTOSC_TRIS			   	TRIS_BIT( C, 0 )
#define MDX_RC1_TRIS		     			TRIS_BIT( C, 1 )
#define MDX_CALMODE_TRIS             		TRIS_BIT( C, 2 )
#define MDX_SCK_TRIS             			TRIS_BIT( C, 3 )
#define MDX_MISO_TRIS             			TRIS_BIT( C, 4 )
#define MDX_MOSI_TRIS             			TRIS_BIT( C, 5 )
#define MDX_TX1_RELAY0_TRIS			TRIS_BIT( C, 6 )
#define MDX_RX1_RELAY1_TRIS			TRIS_BIT( C, 7 )

// Port D
#define MDX_RD0_IO				       	PORT_BIT( D, 0 )
#define MDX_LCDCSB_IO		         		PORT_BIT( D, 1 )
#define MDX_LCDRST_IO            			PORT_BIT( D, 2 )
#define MDX_LCDEN_IO             			PORT_BIT( D, 3 )
#define MDX_LCDBD4_IO            			PORT_BIT( D, 4 )
#define MDX_LCDSDA_IO            			PORT_BIT( D, 5 )
#define MDX_LCDSCL_IO				     	PORT_BIT( D, 6 )
#define MDX_LCDAO_IO				     	PORT_BIT( D, 7 )
    
#define MDX_RD0_TRIS   		       	TRIS_BIT( D, 0 )
#define MDX_LCDCSB_TRIS          		TRIS_BIT( D, 1 )
#define MDX_LCDRST_TRIS          		TRIS_BIT( D, 2 )
#define MDX_LCDEN_TRIS           		TRIS_BIT( D, 3 )
#define MDX_LCDBD4_TRIS          		TRIS_BIT( D, 4 )
#define MDX_LCDSDA_TRIS          		TRIS_BIT( D, 5 )
#define MDX_LCDSCL_TRIS          		TRIS_BIT( D, 6 )
#define MDX_LCDAO_TRIS			     	TRIS_BIT( D, 7 )

//#define MDX_LCD_IO               PORTD
#define MDX_LCD_TRIS             TRISD

// Port E
#define MDX_EECS_IO              PORT_BIT( E, 0 )
#define MDX_EEWP_IO              PORT_BIT( E, 1 )
#define MDX_EEHOLD_IO              PORT_BIT( E, 2 )
#define MDX_RE3_IO              PORT_BIT( E, 3 )
#define MDX_RE4_IO              PORT_BIT( E, 4 )
#define MDX_CONFIG1_IO          PORT_BIT( E, 5 )
#define MDX_CONFIG2_IO          PORT_BIT( E, 6 )
#define MDX_CONFIG3_IO          PORT_BIT( E, 7 )

#define MDX_EECS_TRIS            TRIS_BIT( E, 0 )
#define MDX_EEWP_TRIS            TRIS_BIT( E, 1 )
#define MDX_EEHOLD_TRIS            TRIS_BIT( E, 2 )
#define MDX_RE3_TRIS            TRIS_BIT( E, 3 )
#define MDX_RE4_TRIS            TRIS_BIT( E, 4 )
#define MDX_CONFIG1_TRIS   		  TRIS_BIT( E, 5 )
#define MDX_CONFIG2_TRIS   		  TRIS_BIT( E, 6 )
#define MDX_CONFIG3_TRIS   		  TRIS_BIT( E, 7 )

// Port F
#define MDX_RF1_VDIFF2_IO              	PORT_BIT( F, 1 )
#define MDX_CDVOLTS_IO          		PORT_BIT( F, 2 )
#define MDX_RF3_IO              			PORT_BIT( F, 3 )
#define MDX_RF4_IO              			PORT_BIT( F, 4 )
#define MDX_RF5_IO              			PORT_BIT( F, 5 )
#define MDX_BT_WP_IO            		PORT_BIT( F, 6 )
#define MDX_BT_CLKREQ_IO        		PORT_BIT( F, 7 )

#define MDX_RF1_VDIFF2_TRIS            TRIS_BIT( F, 1 )
#define MDX_CDVOLTS_TRIS        		TRIS_BIT( F, 2 )
#define MDX_RF3_TRIS            		TRIS_BIT( F, 3 )
#define MDX_RF4_TRIS            		TRIS_BIT( F, 4 )
#define MDX_RF5_TRIS            		TRIS_BIT( F, 5 )
#define MDX_BT_WP_TRIS          		TRIS_BIT( F, 6 )
#define MDX_BT_CLKREQ_TRIS      		TRIS_BIT( F, 7 )

// Port G
#define MDX_RG0_IO              PORT_BIT( G, 0 )
#define MDX_BT_TXD_IO           PORT_BIT( G, 1 )
#define MDX_BT_RXD_IO           PORT_BIT( G, 2 )
#define MDX_BT_RESET_IO         PORT_BIT( G, 3 )
#define MDX_BT_PWR_ENABLE_IO		PORT_BIT( G, 4 )

#define MDX_RG0_TRIS            TRIS_BIT( G, 0 )
#define MDX_BT_TXD_TRIS         TRIS_BIT( G, 1 )
#define MDX_BT_RXD_TRIS         TRIS_BIT( G, 2 )
#define MDX_BT_RESET_TRIS       TRIS_BIT( G, 3 )
#define MDX_BT_PWR_ENABLE_TRIS	TRIS_BIT( G, 4 )

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

//
// Delay macro's. Timing is based on an Fosc of 32MHz.
//

// Based on NOP instructions.
#define MDX_DELAY_125NS()     {_asm nop _endasm}
#define MDX_DELAY_250NS()     {_asm nop nop _endasm}
#define MDX_DELAY_500NS()     {_asm nop nop nop nop _endasm}
#define MDX_DELAY_1US()         {_asm nop nop nop nop nop nop nop nop _endasm}

// Based on library functions defined in delays.h
#define MDX_DELAY_10US( n )   Delay10TCYx( (n) << 3 )  // Delays from 10us to 310us.
#define MDX_DELAY_100US( n )  Delay100TCYx( (n) << 3 ) // Delays from 100us to 3.2ms.
#define MDX_DELAY_1MS( n )    Delay1KTCYx( (n) << 3 )  // Delays from 1ms to 32ms.
#define MDX_DELAY_10MS( n )   Delay10KTCYx( (n) << 3 ) // Delays from 10ms to 320ms

#define ShortDelay()     MDX_DELAY_10US( 3 )               // for MMC routines

////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes.
//
////////////////////////////////////////////////////////////////////////////////

void DrvCBT300Init( void );



////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif
