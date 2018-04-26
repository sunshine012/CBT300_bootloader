/********************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          DrvMcc18.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvMcc18.h $
 * $Archive: /MDXP600/BootLoader/Application/DrvMcc18.h $
 * $History: DrvMcc18.h $
 * 
 * *****************  Version 2  *****************
 * User: Rick         Date: 7/09/08    Time: 4:35p
 * Updated in $/MDXP600/BootLoader/Application
 * New LCD display.   Code will work with the original LCD ES13BA0FLY and
 * new China LCD MID184-310
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

#ifndef _MPLABC18_H_
#define _MPLABC18_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"

////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////

// Numeric types for signed or unsigned numeric data of known sizes.
typedef  signed 	char 			INT8;
typedef  signed 	int 			INT16;
typedef  signed 	short long  INT24;
typedef  signed 	long 			INT32;
typedef  signed	void			INT64;

typedef  unsigned char 			UINT8;
typedef  unsigned int 			UINT16;
typedef  unsigned short long 	UINT24;
typedef  unsigned long 			UINT32;
typedef  unsigned	void			UINT64;

// Numeric types for signed or unsigned numeric data of unknown or odd sizes.
typedef signed    int         INT;
typedef unsigned  int         UINT;

// Floating point types.
typedef  float						FLT32;
typedef  void						FLT64;

// Character types. These types are used for data that represent text characters.
typedef  unsigned char 			CHAR;
typedef  unsigned int 			WCHAR;

// Untyped data types of known sizes. These are to be used for data whose type 
// is unknown or has no meaning in the context where it is used.
typedef  unsigned char        BIT;
typedef  unsigned char 			BYTE;
typedef  unsigned int 			WORD;
typedef  unsigned long 			DWORD;
typedef  unsigned short long 	TWORD;
typedef  unsigned void			QWORD;

// Untyped data types of unknow size used to define bit fields.
typedef  unsigned int         BITS;

// Boolean type.
typedef enum {
	BOOL_FALSE  = 0,
	BOOL_TRUE	= 1
} _Bool, *BoolPtr;

#ifndef TRUE
#define TRUE   BOOL_TRUE
#endif

#ifndef FALSE
#define FALSE  BOOL_FALSE
#endif

#ifndef BOOL
#define BOOL   _Bool
#endif

//
// Date/time types.
//

typedef struct
{
   UINT8    Seconds;
   UINT8    Minutes;
   UINT8    Hours;
   UINT8    Date;
   UINT8    Month;
   UINT16   Year;
} _DateTime, *_DateTimePtr;

////////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
////////////////////////////////////////////////////////////////////////////////

// I/O port direction definitions.
#define TRIS_BIT_OUTPUT         0b0    // Defines a single IO pin as output.
#define TRIS_BIT_INPUT          0b1    // Defines a single IO pin as input.
#define TRIS_PORT_OUTPUT        0x00   // Defines a complete port as output.
#define TRIS_PORT_INPUT         0xFF   // Defines a complete port as input.

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

#define CLRWDT()              {_asm clrwdt _endasm}

#define GET_BYTE_0( Value )      (Value & 0xFF)
#define GET_BYTE_1( Value )      ((Value >> 8)  & 0xFF)
#define GET_BYTE_2( Value )      ((Value >> 16) & 0xFF)
#define GET_BYTE_3( Value )      ((Value >> 14) & 0xFF)

#define GET_LOW_BYTE( Value )    GET_BYTE_0( Value )
#define GET_HIGH_BYTE( Value )   GET_BYTE_1( Value )

//
// Macro's to create PORT and TRIS bit references used by the C compiler.
//
// E.g. PORT_BIT( C, 7 ) expands to PORTCbits.RC7 which is defined in the 
// processor header file.
//

#define PORT_BIT( Port, Bit )    PORT##Port##bits.R##Port##Bit
#define TRIS_BIT( Port, Bit )    TRIS##Port##bits.TRIS##Port##Bit

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif
