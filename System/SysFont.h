/******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          SysFont.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: SysFont.h $
 * $Archive: /MDXP600/BootLoader/System/SysFont.h $
 * $History: SysFont.h $
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
 * Contains all required definitions for the keys module 
 * 
 * References:
 *
 * None.
 *
*******************************************************************************/

#ifndef _SYS_FONT_H_
#define _SYS_FONT_H_

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

typedef enum 
{
   FONT_IN_ROM,
   FONT_IN_FLASH
} _FontLocation, *FontLocationPtr;

typedef struct
{
   UINT8 Width;
   UINT8 Height;
   UINT8 BytesPerChar;
   UINT8 CharOffset;
   UINT8 CharCount;
   const far rom BYTE* FontAddress;
} _FontHeader, *_FontHeaderPtr;

///////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

#define FONT_COUNT                 5
#define FONT_MIN_CHAR_WIDTH        6
#define FONT_MAX_CHAR_WIDTH       12
#define FONT_MAX_CHAR_HEIGHT      16
#define FONT_MAX_BYTES_PER_CHAR   16
#define FOMT_MAX_CHAR_COUNT      255

// Font id definitions.
#define FONT_STANDARD_6X8          0
#define FONT_STANDARD_8X8          1
#define FONT_STANDARD_12X16        2
#define FONT_CHINESE_12X16         3
#define FONT_JAPANESE_12X16        4

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

void  SysFontSelect( UINT8 Font, _FontLocation Location );
UINT8 SysFontGetCharData( CHAR Char, BYTE *Buffer );
UINT8 SysFontGetStringWidth( const CHAR *String );

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif

