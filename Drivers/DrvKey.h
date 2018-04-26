/*******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:          DrvKey.h
 *
 * Designed by:   Kees Hemmes
 *
 * References:
 *
 * None.
 *
*******************************************************************************/

#ifndef _DRV_KEY_H_
#define _DRV_KEY_H_

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

// Structure to store the key status and flags
typedef struct {
   BITS  States:      5; // Holds 5 bits for the 5 switches
   _Bool New:         1; // If true, indicates a new state.
   _Bool Repeat:      1; // If true, indicates a repeat situation.
   BITS  NotUsed:     1;
} _Keys, *_KeysPtr;

typedef struct {
   UINT8 Keys;
}_Key;

typedef union {                        //union to access the keys as a byte
   UINT8 Keys;                         //or by individual bits
   _Key Key;
}_KeyPad;


////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

//
// I/O line definitions.
//

// I/O lines.
#define KEY_SW1_IO               MDX_SW1_IO
#define KEY_SW2_IO               MDX_SW2_IO
#define KEY_SW3_IO               MDX_SW3_IO
   
// I/O line direction bits.   
#define KEY_SW1_TRIS             MDX_SW1_TRIS
#define KEY_SW2_TRIS             MDX_SW2_TRIS
#define KEY_SW3_TRIS             MDX_SW3_TRIS

/* Keypad definitions */

#define _20MILLISECONDS     	1
#define PRESSED            		1
#define NOT_PRESSED        	0

#define UP_ARROW_KEY       		0x01
#define DOWN_ARROW_KEY     	0x02
#define ENTER_KEY          			0x04

#define UpArrowInput         		MDX_SW1_IO
#define DownArrowInput       		MDX_SW2_IO
#define EnterKeyInput        		MDX_SW3_IO

/* Key input routine function prototypes */
extern void ReadKeys(void);
extern void  DrvKeyInit(  void );

#endif

