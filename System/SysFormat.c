/******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          SysFormat.c
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: SysFormat.c $
 * $Archive: /MDXP600/BootLoader/System/SysFormat.c $
 * $History: SysFormat.c $
 * 
 * *****************  Version 2  *****************
 * User: Rick         Date: 7/09/08    Time: 4:35p
 * Updated in $/MDXP600/BootLoader/System
 * New LCD display.   Code will work with the original LCD ES13BA0FLY and
 * new China LCD MID184-310
 * 
 * *****************  Version 1  *****************
 * User: Rick         Date: 1/24/08    Time: 8:22a
 * Created in $/MDXP600/BootLoader/System
 *
 * Description:
 *
 * 
 * References:
 *
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

#include "SysFormat.h"

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
// Gobal functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Function:      
// 
// Parameters:    
// Return Value:  
// 
// Description:   
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void  SysFormatHexToString( UINT32 Value, CHAR *String, UINT8 Size )
{
   INT8  Index;
   UINT8 Digit;

   Index = Size - 1;
   do
   {
      if( Index > 7 )
      {
         *String++ = '0';
      }
      else
      {
         Digit = (Value >> (Index * 4)) & 0x0F;
         if( Digit < 0x0A )
         {
            *String++ = '0' + Digit;
         }
         else
         {
            *String++ = 'A' + (Digit - 0x0A);
         }
      }

      Index--;
   }
   while( Index >= 0 );

   *String = 0;
}
