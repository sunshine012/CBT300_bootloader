/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          DrvInt_18F87J10.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvInt_18F87J10.h $
 * $Archive: /MDXP600/192-000039 PCB/192-110276 Hella/Drivers/DrvInt_18F87J10.h $
 * $History: DrvInt_18F87J10.h $
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
 * User: Bbroer       Date: 1-12-10    Time: 17:01
 * Created in $/MDXP600/192-000039 PCB/192-110223 MDX-645P KRAMP/Drivers/Standard
 * Added driver files from the master
 * 
 * *****************  Version 2  *****************
 * User: Rick         Date: 2/29/08    Time: 4:42p
 * Updated in $/MDXP600/192-000039 PCB/Master/Drivers/Standard
 * File comment format for Source Safe
 * 
 * *****************  Version 1  *****************
 * User: Rick         Date: 2/26/08    Time: 8:03a
 * Created in $/MDXP600/192-000039 PCB/Master/Drivers
 *
 * Description:
 *
 * References:
 * M41T94 Datasheet - August 2006 Rev 4
 *
*******************************************************************************/

#ifndef _DRV_INT_18F67J10_H_
#define _DRV_INT_18F67J10_H_

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

// Interrupt id type.
typedef enum {
   INT_ID_TIMER0,
   INT_ID_TIMER1,
   INT_ID_TIMER2,
   INT_ID_USART_1_RX,
   INT_ID_USART_2_RX,
   INT_ID_RB,
   INT_ID_ALL
} _IntId, *_IntIdPtr;

////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

// Configuration values.
#define INT_PRIORITY_LOW            0
#define INT_PRIORITY_HIGH           1

#define INT_DISABLE                 0
#define INT_ENABLE                  1

#define INT_FLAG_CLEAR              0
#define INT_FLAG_SET                1

#define INT_PRIORITY_LEVELS_DISABLE 0
#define INT_PRIORITY_LEVELS_ENABLE  1

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

void DrvIntInit( void );
void DrvIntEnable( _IntId Id, _Bool Enable );

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif





