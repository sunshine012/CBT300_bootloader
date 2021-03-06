/******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          DrvLoad.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvLoad.h $
 * $Archive: /MDXP600/BootLoader/Drivers/DrvLoad.h $
 * $History: DrvLoad.h $
 * 
 * *****************  Version 2  *****************
 * User: Rick         Date: 7/09/08    Time: 4:35p
 * Updated in $/MDXP600/BootLoader/Drivers
 * New LCD display.   Code will work with the original LCD ES13BA0FLY and
 * new China LCD MID184-310
 * 
 * *****************  Version 1  *****************
 * User: Rick         Date: 1/24/08    Time: 8:21a
 * Created in $/MDXP600/BootLoader/Drivers
 *
 * Description:
 *
 * References:
 *
 * 
 *
*******************************************************************************/

#ifndef _DRV_LOAD_H_
#define _DRV_LOAD_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"

#include "MplabC18.h"
#include "DrvMdxP600.h"

////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
////////////////////////////////////////////////////////////////////////////////

//
// I/O line definitions.
//

// I/O lines.
#define LOAD_CONTROL_IO    MDX_TESTOSC_IO

// I/O line direction bits.
#define LOAD_CONTROL_TRIS  MDX_TESTOSC_TRIS

// I/O line states
#define LOAD_OFF           0
#define LOAD_ON            1

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

void DrvLoadInit( void );
void DrvLoadOn( void ); 
void DrvLoadOff( void ); 

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif
