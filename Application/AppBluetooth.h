/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Error definitions.
;
*******************************************************************/
#ifndef APPBLUETOOTH_H
#define APPBLUETOOTH_H

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

#define BL_BLUETOOTH_INIT          		0
#define BL_BLUETOOTH_INIT_WAIT          1
#define BL_BLUETOOTH_INIT_DONE          2
#define BL_UPDATE_WAIT                  3
#define BL_BLUETOOTH_PAIR_DONE          4
#define BL_BLUETOOTH_PAIR_DONE_WAIT     5
#define BL_BLUETOOTH_CONNECTED          6
#define BL_BLUETOOTH_CONNECTED_WAIT     7
#define BL_UPDATE_FROM_BLUETOOTH        8

#define BLUETOOTH_DATA_NORMAL   0
#define BLUETOOTH_DATA_SPECIAL  1

#define BLUETOOTH_IDLE      0
#define BLUETOOTH_DATA_RECEIVED     1
#define BLUETOOTH_DATA_PROCESSING   2
#define BLUETOOTH_DATA_SENDING_1      3
#define BLUETOOTH_DATA_SENDING_2      4
#define BLUETOOTH_DATA_SEND_COMPLETE  5

#define BL_VERSION     0
#define BL_ADDRESS     1
#define BL_FLASH       2
#define BL_NONE        3

extern CHAR  SerialRxBuffer2[160];
extern UINT8 BLDataStatus;


extern void BlueToothState(void);

#endif
