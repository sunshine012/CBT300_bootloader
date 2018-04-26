/*******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:             Key.c
 *
 * Designed by:   King Chen
 *
 * Description:
 *
 * This file implements the driver functions to detect key presses. 
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
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
//#include "AppData.h"
#include "DrvKey.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

_Keys KeyDebounced;     	// Stores the debounced state of the keys.
_Keys KeyBounced;       	// Keeps track of the bounced state of the keys.
INT16 KeyCounter;       	// Used to time a detected state.
UINT8 LastKeysPressed;          //used in key debounce routine
UINT8 KeyDebounceCounter;       //counter used to debounce the keypad
_KeyPad KeyPad;                   //debounced keypad port


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



void DrvKeyInit( void )
{
   // Direction of IO lines.
   KEY_SW1_TRIS            = TRIS_BIT_INPUT;
   KEY_SW2_TRIS            = TRIS_BIT_INPUT;
   KEY_SW3_TRIS            = TRIS_BIT_INPUT;

}
void ReadKeys(void)
{     
   UINT8 KeysPressed = 0;
        
   if(!EnterKeyInput)
      KeysPressed = ENTER_KEY;
   if(!UpArrowInput)
      KeysPressed |= UP_ARROW_KEY;
   if(!DownArrowInput)
      KeysPressed |= DOWN_ARROW_KEY;

   if(KeysPressed == 0)                      //check if any keys pressed
   {                                                  //no keys pressed
      KeyDebounceCounter = 0;          //reset the debounce counter
      KeyPad.Keys = 0;                       //set keypad register to no keys pressed
      //Status.Bit.KeysReleased = TRUE;  //indicate no keys pressed
   }
   else if(KeysPressed == LastKeysPressed)
   {                                   //check if key held long enough
      if(KeyDebounceCounter < _20MILLISECONDS)//(20ms))
         KeyDebounceCounter++;         //not held long enough, increment the
      else                             //debounce counter otherwise,
         KeyPad.Keys = KeysPressed;    //valid key(s), update KeysPressed register
   }
   else
   {    
      KeyDebounceCounter = 0;          //reset the debounce counter
   }
   LastKeysPressed = KeysPressed;
}     


