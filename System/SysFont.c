/******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          SysFont.c
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: SysFont.c $
 * $Archive: /MDXP600/BootLoader/System/SysFont.c $
 * $History: SysFont.c $
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

#include <string.h>

#include "DrvMcc18.h"
#include "DrvMdxP600.h"

#include "SysFont.h"
#include "SysFont6x8.h"
//#include "SysFont8x8.h"
//#include "SysFont12x16.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

_FontHeader    FontHeader;
_FontLocation  FontLocation;

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

const far rom _FontHeader Font6x8Header =
{
   FONT6X8_WIDTH,
   FONT6X8_HEIGHT,   
   FONT6X8_BYTES_PER_CHAR,
   FONT6X8_CHAR_OFFSET,
   FONT6X8_CHAR_COUNT,
   &Font6x8[ 0 ][ 0 ]
};

const far rom _FontHeader Font8x8Header =
{
   FONT6X8_WIDTH,
   16,   
   12,
   FONT6X8_CHAR_OFFSET,
   FONT6X8_CHAR_COUNT,
   &Font6x8[ 0 ][ 0 ]
};

const far rom _FontHeader Font12x16Header =
{
   FONT6X8_WIDTH,
   16,   
   12,
   FONT6X8_CHAR_OFFSET,
   FONT6X8_CHAR_COUNT,
   &Font6x8[ 0 ][ 0 ]
};

const far rom _FontHeader* FontHeaders[ FONT_COUNT ] =
{
   &Font6x8Header,
   &Font6x8Header,
   &Font6x8Header,
   &Font6x8Header,
   &Font6x8Header
};

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

void SysFontSelect( UINT8 Font, _FontLocation Location )
{
   const far rom _FontHeader *Header;
   
   switch( Location )
   {
      case FONT_IN_ROM:
         Header = FontHeaders[ Font ];
         memcpypgm2ram( &FontHeader, Header, sizeof( _FontHeader ) );
         break;
      case FONT_IN_FLASH:
         break;
      default:
         break;
   }

   FontLocation = Location;
}

UINT8 SysFontGetCharData( CHAR Char, BYTE *Buffer )
{
   if( Char < FontHeader.CharOffset )
   {
      Char = 0;
   }
   else
   {
      Char = Char - FontHeader.CharOffset;
   }

   switch( FontLocation )
   {
      case FONT_IN_ROM:
         memcpypgm2ram( Buffer, Font6x8[ Char ], FontHeader.Width );
         break;
      case FONT_IN_FLASH:
         break;
      default:
         break;
   }

   return( FontHeader.Width );
}

UINT8 SysFontGetStringWidth( const CHAR *String )
{
   return( strlen( (char*)String ) * FontHeader.Width );
}


