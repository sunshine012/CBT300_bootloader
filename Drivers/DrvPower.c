/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          Power.c
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvPower.c $
 * $Archive: /MDXP600/BootLoader/Drivers/DrvPower.c $
 * $History: DrvPower.c $
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

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"

#include "MplabC18.h"
#include "DrvMdxP600.h"

#include "DrvPower.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

UINT8 PowerAutoOffTimeSec;
UINT8 PowerAutoOffCounter;

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

void DrvPowerInit( UINT8 AutoOffTimeSec ) 
{
   POWER_CONTROL_TRIS   = TRIS_BIT_OUTPUT;
   POWER_CONTROL_IO     = POWER_OFF;

   PowerAutoOffTimeSec  = AutoOffTimeSec;
   PowerAutoOffCounter  = 0;
}

void DrvPower1sIsr( void ) 
{
}

void DrvPowerOn( void ) 
{
   PowerAutoOffCounter  = PowerAutoOffTimeSec;
   
   POWER_CONTROL_IO     = POWER_ON;
}

void DrvPowerOff( void ) 
{
   POWER_CONTROL_IO     = POWER_OFF;

   PowerAutoOffCounter  = 0;
}
