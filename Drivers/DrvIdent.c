/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          DrvIdent.c
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvIdent.c $
 * $Archive: /MDXP600/BootLoader/Drivers/DrvIdent.c $
 * $History: DrvIdent.c $
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

#include "DrvIdent.h"

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

void DrvIdentInit( void ) 
{
   IDENT_CONTROL_TRIS   = TRIS_BIT_INPUT;
}

BIT DrvIdentGet( void ) 
{
   return( IDENT_CONTROL_IO );
}
