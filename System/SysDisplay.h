/******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:          SysDisplay
 *
 * Designed by:   King Chen
 *
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

#ifndef _SYS_DISPLAY_H_
#define _SYS_DISPLAY_H_

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

///////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

      
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

//extern const CHAR  TestShow[15];


extern void SysClear_Line(unsigned char Line);
extern void SysClear_Line_S(unsigned char Line);
extern void DisplayString_S(const unsigned char *string, unsigned char row, unsigned char Mask);
extern void DisplayRomString(UINT8 row, const rom char* string);

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif

