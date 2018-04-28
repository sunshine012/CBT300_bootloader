/*******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:          AppData.h
 *
 * Designed by:   Chad He
 *
 *
 * Description: Easy to add Global variables
 *
 * References:
 *
*******************************************************************************/


#ifndef _APP_DATA_H_
#define _APP_DATA_H_

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
#define BTADDRESSLENGTH     6
#define BTLINKKEYLENGTH     16


typedef struct { 
   UINT8    RemoteBDAdress[BTADDRESSLENGTH];           //Remote address
   UINT8 	RemoteLinkKey[BTLINKKEYLENGTH];              //Remote Link-key
   UINT8	PairFlg; 
}_BTRemoteData;

typedef struct{
   UINT8    BTDataLength;
   UINT8    BTDataBuffer[255];
}_BTData;


////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

#define OPERATE_SYSTEM_ANDROID  0
#define OPERATE_SYSTEM_IOS      1
#define OPERATE_SYSTEM_NONE     0xFF

#define CBT300_CONFIG          0x00
#define CBT100_COMFIG          0x04

#define SERIALNUMBER 10

#define UPDATE_SOURCE_NONE  0
#define UPDATE_SOURCE_UART1 1
#define UPDATE_SOURCE_UART2 2

#define BT_DEVICE_RECORDED_NUM_MAX      10

#define EESerialNumberDataAddress      	(0x0000+0x70)//11Byte
#define EEBTRemoteDataAddress           (0x0000+0x300)

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////
//
// External declerations.
//
////////////////////////////////////////////////////////////////////////////////


extern UINT8 ConfigData;
extern UINT8 UpdateSrcSerialNum;

extern UINT8 ConnectionFlag;   
extern UINT8 ConnectionCounter;

extern CHAR  SerialRxBuffer1[40];
extern UINT8 SerialPort2DrvBuffer[160];


extern UINT8 TempBTBuffer[128];  
extern UINT8 WrapperBuffer[128];

extern UINT8 BLOperatingState;

extern _BTData BTData;

////////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif


