/********************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          Load.c
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvLoad.c $
 * $Archive: /MDXP600/BootLoader/Drivers/DrvLoad.c $
 * $History: DrvLoad.c $
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

#include "DrvLoad.h"

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

void DrvLoadInit( void ) 
{
   LOAD_CONTROL_TRIS = TRIS_BIT_OUTPUT;
   
   LOAD_CONTROL_IO   = LOAD_OFF;
}

void DrvLoadOn( void )
{
   LOAD_CONTROL_IO   = LOAD_ON;
}

void DrvLoadOff( void )
{
   LOAD_CONTROL_IO   = LOAD_OFF;
}