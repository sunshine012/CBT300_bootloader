/*******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:          AppData.c
 *
 * Designed by:   Chad He
 *
 *
 * Description: Easy to add Global variables
 *
 * References:
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Include files.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include "AppData.h"


////////////////////////////////////////////////////////////////////////////////
//
// Mirco.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////


UINT8 ConfigData;
UINT8 UpdateSrcSerialNum;

UINT8 ConnectionFlag;   
UINT8 ConnectionCounter;

CHAR  SerialRxBuffer1[40];
UINT8 SerialPort2DrvBuffer[160];

UINT8 TempBTBuffer[128];  
UINT8 WrapperBuffer[128];

UINT8 BTSystemConfig = OPERATE_SYSTEM_ANDROID;

UINT8 BLOperatingState; // Bootloader operating state
UINT8 BLDataStatus;

#pragma udata GlobalBTDataBuffer
    _BTData BTData;
#pragma udata

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

