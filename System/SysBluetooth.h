/*
 * SysBluetooth.h
 *
 *  Created on: Apr 20, 2015
 *      Author: King Chen
 */

#ifndef _SYSBLUETOOTH_H_
#define _SYSBLUETOOTH_H_

#include "DrvPan1026.h"
#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "AppData.h"
#include "DrvUsart_18F67J10.h"

#define BTReset               1
#define Firmware              2
#define I2C                   3
#define EnableEEPROM          4
#define ReadEEPROM            5
#define WriteBDAddress        6
#define SetMode               7
#define MNGInit               8
#define CoD                   9
#define SPPSetup              10
#define MNGScan               11
#define BTReady               12
#define SPPConnect            13
#define ControlSSP            14
#define ControlSSP2           15
#define SPPDataTransfer       16
#define MNGDiscoverRemote     17
#define ConnectionRequested   19
#define HCIIOCapRequest       20
#define TestConnection        21
#define SPPDisconnect         22
#define BTReady2              23
#define BTReady3              24
#define ConnectionRequested2  25
#define ControlSSP3           26
#define SPPConnectSuccess     27
#define PairingComplete       28
#define WaitingState          29
#define SleepModeEnable       30
#define SleepModeDisable      31
#define BTReady4              32
#define BTSPPReady            33
#define BTSPPReady2           34
#define BTSPPReady3           35
#define BTM2WriteEEProm       36
#define REMOTE_DEVICE_NOTIFY  37
#define HCI_IO_CAPABILITY_REQUEST_EVENT 38
#define BT_PAIR_DONE            39
#define DEF_TCU_MNG_SSP_INFO_EVENT  40
#define Pairing_Waiting             41
#define SET_BAUDRATE                42

#define DATA_LINK_ESCAPE                           0x10
#define END_OF_TEXT                                0x03
#define END_OF_MESSAGE                             0x1003

#define ACK                                        0x06
#define NAK                                        0x15

#define WRAPPED_MESSAGE_NO_ERROR                   0x00
#define WRAPPED_MESSAGE_ERROR_1                    0x01
#define WRAPPED_MESSAGE_ERROR_2                    0x02
#define WRAPPED_MESSAGE_ERROR_3                    0x03

#define PID_ACK                                 0x0006
#define PID_NAK                                 0x0015
#define PID_CHECK_STATE               				0x00FB
#define PID_INITIAL_BATTERY_TEST                		0x00FC
#define PID_PERFORM_BATTERY_TEST                    	0x00FD
#define PID_RETURN_BATTERY_RESULT               	0x00FE
#define PID_PACKET_REQUEST                      		0x00FF

//#define BATTERY_STATE_INITIAL    0X01
#define BATTERY_STATE_READY      0X01
#define BATTERY_STATE_BUSY    	  0X02
#define BATTERY_STATE_FINISH      0X04
#define BYTE_SWAP_UINT16(a) (UINT16)((((UINT16)(a)&0xFF00)>>8) | \
                                    (((UINT16)(a)&0x00FF)<<8))

#define BYTE_SWAP_UINT32(a) (UINT32)((((UINT32)(a)&0xFF000000)>>24) | \
                                     (((UINT32)(a)&0x00FF0000)>>8) | \
                                     (((UINT32)(a)&0x0000FF00)<<8) | \
                                     (((UINT32)(a)&0x000000FF)<<24))

extern UINT8    BTState;
extern UINT8  WrapperBufferSize;

extern void SysInitBlueToothRadio(void);
extern void SysBTSetState(UINT8 newState);
extern void SysBTReset(void);
extern void BlueToothStatemachine(void);
extern UINT8 SysProcessBluetoothCommand(CHAR* pBuffer);
extern UINT8 SysBTConnectTest(void);
extern void SysBTWrapData(UINT8* Message, UINT16 Length);
extern void SysBTSendData(UINT8* Message, UINT16 Length);
extern void SysWrapperWrapMessage(UINT8* pData, UINT16 DataLength, UINT16 PacketId);
extern UINT8 SysBTGetState( void );
#endif /* SYSBLUETOOTH_H_ */
