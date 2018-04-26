/*
 * DrvPan1026.c
 *
 *  Created on: Oct 10, 2015
 *     
 */

#include <stdlib.h>
#include <string.h>
#include "DrvPan1026.h"
#include "SysBluetooth.h"
#include "AppBluetooth.h"
#include "AppData.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvTimer_18F67J10.h"
#include "DrvPic18f67J10.h"
#include "MpLabC18.h"
#include "DrvMdxP600.h"
#include "SysDisplay.h"
#include "DrvEeprom_25AA320.h"
#include "DrvUsart_18F67J10.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////
UINT8 bdAddress[6]; 
UINT8 REMOTE_BDADDRESS[6];
UINT8 REMOTE_BDADDRESS_Paried[6];
UINT8 BTClassDevice[3];
UINT8 REMOTE_LINK_KEY[16];
const rom UINT8 ErrorCheck[5] = {0x09,0x00,0x00,0xe1,0xf2};
UINT8   WrapperBufferSize;
UINT8 SerialNumberData[SERIALNUMBER+1]="0216300000";



///////////////////////////////////////////////////////////////////////////////////////////
//   Reset 
const rom UINT8 TCU_HCI_RESET_REQ[4] = {0x01, 0x03, 0x0c, 0x00};
const rom UINT8 TCU_HCI_RESET_RESP[7] = {0x04,0x0e,0x04,0x04,0x03,0x0c,0x00};
//   Firmware Version Request
const rom UINT8 TCU_HCI_GET_FIRMWARE_VERSION_REQ[13] = {0x01, 0x08, 0xfc, 0x09, 0x00, 0xa1, 0x00, 0x00, 0x00, 0x14, 0x0d, 0xff, 0x00};
const rom UINT8 TCU_HCI_GET_FIRMWARE_VERSION_RESP[33] = {0x04,0xff,0x1e,0x08,0x00,0xa1,0x00,0x00,0x00,0x14,0x0d,0x00,0x0f,0x38,0x2e,0x30,0x30,0x2e,0x37,0x32,0x42,0x2d,0x30,0x36,0x20,0x52,0x4f,0x4d,0x3d,0x35,0x30,0x31,0x00};
//   Set I2C
const rom UINT8 TCU_HCI_M2_BTL_SET_I2C_ENABLE_REQ[15] = {0x01, 0x08, 0xfc, 0x0b, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x14, 0x5b, 0xff, 0x02, 0x03, 0x01};
const rom UINT8 TCU_HCI_M2_BTL_SET_I2C_ENABLE_RESP[13] = {0x04,0xff,0x0a,0x08,0x00,0xa0,0x00,0x00,0x00,0x14,0x5b,0x00,0x00}; 
//   Write EEPROM 
const rom UINT8 TCU_HCI_M2_BTL_EEPROM_WRITE_ENABLE_REQ[13] = {0x01, 0x08, 0xfc, 0x09, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x14, 0x83, 0xff, 0x00};
const rom UINT8 TCU_HCI_M2_BTL_EEPROM_WRITE_ENABLE_RESP[13] =  {0x04,0xff,0x0a,0x08,0x00,0xa0,0x00,0x00,0x00,0x14,0x83,0x00,0x00};
//   Read EEPROM 
const rom UINT8 TCU_HCI_M2_GENERAL_READ_EEPROM_REQ[20] = {0x01, 0x08, 0xfc, 0x10, 0x00, 0xa1, 0x00, 0x00, 0x00, 0x14, 0x88, 0xff, 0x10, 0x06, 0xa0, 0x01, 0x01, 0x06, 0x02, 0x00};
const rom UINT8 TCU_HCI_M2_GENERAL_READ_EEPROM_RESP[20] =  {0x04,0xff,0x11,0x08,0x00,0xa1,0x00,0x00,0x00,0x14,0x88,0x00,0x10,0x06,0x00,0x13,0x43,0x0E,0x3E,0x06};//0x0c,0x55,0x8e};
//  set baudrate 57600
const rom UINT8 TCU_HCI_M2_BTL_SET_BAUDRATE_REQ[20] = {0x08, 0xFC, 0x11, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x14, 0x42, 0xFF, 0x10, 0x07, 0x00, 0x34, 0x60, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 TCU_HCI_M2_BTL_SET_BAUDRATE_RESP[12] = {0xFF, 0x0A, 0x08, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x14, 0x42, 0x00, 0x00}; 

/////////////////////////////////////////////////////////////////////////////////////////////////
//   
const rom UINT8 TCU_HCI_WRITE_BD_ADDR_REQ[10] = {0x01, 0x13, 0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 TCU_HCI_WRITE_BD_ADDR_RESP[7] =  {0x04,0x0e,0x04,0x04,0x13,0x10,0x00};

const rom UINT8 TCU_HCI_SET_MODE_REQ[7] = {0x01, 0x08, 0xfc, 0x03, 0x00, 0x99, 0x01};
const rom UINT8 TCU_HCI_SET_MODE_RESP[8] =  {0x04,0xff,0x05,0x08,0x00,0x99,0x00,0x01};
// Local BT Device name CBT-350-1234567890
const rom UINT8 TCU_MNG_INIT_REQ[28] = {0x1C, 0x00, 0x00, 0xe1, 0x01, 0x15, 0x00, 0x04, 0x00, 0x12, 0x43, 0x42, 0x54, 0x2d, 0x33, 0x35, 0x30, 0x2d, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30};
const rom UINT8 TCU_MNG_INIT_RESP[14] =  {0x0e,0x00,0x00,0xe1,0x81,0x07,0x00,0x00,0xd1,0xef,0x0b,0x43,0x13,0x00};

const rom UINT8 TCU_MNG_STANDARD_HCI_SET_REQ_Write_Class_of_Device[13] = {0x0d, 0x00, 0x00, 0xe1, 0x3d, 0x06, 0x00, 0x24, 0x0c, 0x03, 0x18, 0x11, 0xc0};
const rom UINT8 TCU_MNG_STANDARD_HCI_SET_RESP_Write_Class_of_Device[15] =  {0x0f,0x00,0x00,0xe1,0xbd,0x08,0x00,0x00,0x06,0x0e,0x04,0x01,0x24,0x0c,0x00};

const rom UINT8 TCU_SPP_SETUP_REQ[7] = {0x07, 0x00, 0x00, 0xe5, 0x01, 0x00, 0x00};
const rom UINT8 TCU_SPP_SETUP_RESP[8] =  {0x08,0x00,0x00,0xe5,0x81,0x01,0x00,0x00};
		
const rom UINT8 TCU_MNG_SET_SCAN_REQ[8] = {0x08, 0x00, 0x00, 0xe1, 0x0c, 0x01, 0x00, 0x03};   //Read and discover SCAN_MODE = 0x03;
const rom UINT8 TCU_MNG_SET_SCAN_RESP[8] =  {0x08,0x00,0x00,0xe1,0x8c,0x01,0x00,0x00};

//////////////////////////////////////////////////////////////////////////////////////

const rom UINT8 HCI_FIRST_STRING_LUMP_SET[76] = {0x08, 0x00, 0x00, 0xe1, 0x93, 0x01, 0x00, 0x00,0x0f,0x00,0x00,0xe1,0x47,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00, 0x00, 0xe1, 0x7d, 0x0b, 0x00, 0x32, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x01, 0x00, 0x03,0x14, 0x00, 0x00, 0xe1, 0x6e, 0x0d, 0x00, 0x8b, 0x44, 0x9b, 0x7e, 0x90, 0xe4, 0x06, 0x58, 0x54, 0x31, 0x32, 0x35, 0x34,0x0f, 0x00, 0x00, 0xe1, 0x7d, 0x08, 0x00, 0x31, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 TCU_MNG_SET_SCANREADY_RESP[8] =  {0x08,0x00,0x00,0xe1,0x8c,0x01,0x00,0x00};

               UINT8 TCU_MNG_DISCOVER_REMOTE_SERVICE_REQ[15] = {0x0F,0x00,0x00,0xe1,0x05,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const rom UINT8 TCU_MNG_DISCOVER_REMOTE_SERVICE_ACCEPT[10] = {0x0a,0x00,0x00,0xe1,0xf1,0x03,0x00,0x00,0xe1,0x03};
const rom UINT8 TCU_MNG_CONNECTION_STATUS_EVENT[15] = {0x0f,0x00,0x00,0xe1,0x47,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const rom UINT8 TCU_MNG_CONNECTION_STATUS_EVENT2[15] = {0x0f,0x00,0x00,0xe1,0x47,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01};
const rom UINT8 TCU_MNG_DISCOVER_REMOTE_SERVICE_EVENT[14] = {0x14, 0x00, 0x00, 0xe1, 0x45, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
/// get Remode Address                                               
const rom UINT8 TCU_MNG_CONNECTION_ACCEPT_REQUEST_EVENT[7] = {0x10, 0x00, 0x00, 0xe1, 0x55, 0x09, 0x00};
const rom UINT8 TCU_MNG_CONNECTION_ACCEPT_REQ[15] 			= {0x0f, 0x00, 0x00, 0xe1, 0x13, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 TCU_MNG_CONNECTION_ACCEPT_REQ_LINK_KEY[15] 	= {0x1f, 0x00, 0x00, 0xe1, 0x13, 0x18, 0x00, 0x00, 0xd5, 0xd4, 0x17, 0x88, 0x74, 0x90, 0x01};

const rom UINT8 TCU_MNG_CONNECTION_ACCEPT_RESP[8] = {0x08, 0x00, 0x00, 0xe1, 0x93, 0x01, 0x00, 0x00};

               UINT8 TCU_SPP_CONNECT_REQ[23] = {0x17, 0x00, 0x00, 0xe5, 0x03, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x00};
const rom UINT8 TCU_SPP_CONNECT_RESP[10] = {0x0a,0x00,0x00,0xe1,0xf1,0x03,0x00,0x00,0xe5,0x03};

//const rom UINT8 TCU_MNG_DEEP_SLEEP_RESP[8] = {0x08 , 0x00 , 0x00 , 0xe1 , 0xb7 , 0x01 , 0x00 , 0x00};
//const rom UINT8 TCU_MNG_CONNECTION_ACCEPT_REQUEST_EVENT_ERROR[10] = {0x00, 0x00, 0x00, 0xe1, 0x8c, 0x01, 0x00, 0x00, 0x00, 0x0e};

const rom UINT8 TCU_MNG_SSP_SET_REQ_HCI_IO_Capability_Request_Reply[19] = {0x13, 0x00, 0x00, 0xe1, 0x3d, 0x0c, 0x00, 0x2b, 0x04, 0x09, 0x8b, 0x44, 0x9b, 0x7e, 0x90, 0xe4, 0x01, 0x00, 0x03};// 0x03, 0x00, 0x00};// 
const rom UINT8 HCI_IO_Capability_Response_Event[18] = {0x12, 0x00, 0x00, 0xe1, 0x7d, 0x0b, 0x00, 0x32, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x01, 0x00, 0x03};//0x03, 0x00, 0x00};//
const rom UINT8 HCI_IO_Capability_Request_Event[15] = {0x0f, 0x00, 0x00, 0xe1, 0x7d, 0x08, 0x00, 0x31, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//UINT8 HCI_IO_Capability_Request_Event[12] = {0xe1, 0x7d, 0x08, 0x00, 0x31, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 TCU_MNG_REMOTE_DEVICE_NAME_AUTO_NOTIFY_EVENT[20] = {0x00, 0x00, 0x00, 0xe1, 0x6e, 0x0d, 0x00, 0x8b, 0x44, 0x9b, 0x7e, 0x90, 0xe4, 0x06, 0x58, 0x54, 0x31, 0x32, 0x35, 0x34};

const rom UINT8 TCU_MNG_SSP_SET_REQ_HCI_User_Confirmation_Request_Reply[17] = {0x11, 0x00, 0x00, 0xe1, 0x3d, 0x0a, 0x00, 0x2c, 0x04, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//UINT8 TCU_MNG_REMOTE_DEVICE_NAME_AUTO_NOTIFY_EVENT[22] = {0x16, 0x00, 0x00, 0xe1, 0x6e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x50, 0x41, 0x4e, 0x31, 0x30, 0x32, 0x36, 0x41};
//UINT8 TCU_MNG_REMOTE_DEVICE_NAME_AUTO_NOTIFY_EVENT[2] = { 0xe1, 0x6e };
const rom UINT8 TCU_MNG_SSP_SET_RESP_HCI_IO_Capability_Request_Reply[21] = {0x15, 0x00, 0x00, 0xe1, 0xbd, 0x0e, 0x00, 0x00, 0x0c, 0x0e, 0x0a, 0x01, 0x2b, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//UINT8 HCI_IO_User_Confirmation_Request_Event[19] = {0x13, 0x00, 0x00, 0xe1, 0x7d, 0x0c, 0x00, 0x33, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x3d,0x43,0x04,0x00};
const rom UINT8 HCI_IO_User_Confirmation_Request_Event[15] = {0X13, 0x00, 0x00, 0xe1, 0x7d, 0x0c, 0x00, 0x33, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00 ,0xe4};
const rom UINT8 TCU_MNG_SSP_SET_RESP_HCI_User_Confirmation_Request_Reply[21] = {0x15,0x00, 0x00, 0xe1, 0xbd, 0x0e, 0x00, 0x00, 0x0c, 0x0e, 0x0a, 0x01, 0x2c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 HCI_Simple_Pairing_Complete_Event[16] = {0x10, 0x00, 0x00, 0xe1, 0x7d, 0x09, 0x00, 0x36, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 HCI_Simple_Pairing_Complete_Cancel_Event[16] = {0x10, 0x00, 0x00, 0xe1, 0x7d, 0x09, 0x00, 0x36, 0x07, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 TCU_MNG_CONNECTION_STATUS_EVENT3[15] = {0x20, 0x00, 0x00, 0xe1, 0x47, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x03};
const rom UINT8 TCU_SPP_CONNECT_EVENT[14] = {0x19, 0x00, 0x00, 0xe5, 0x43, 0x12, 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x00, 0x00};
const rom UINT8 TCU_SPP_CONNECT_EVENT2[2] = {0xe5, 0x43};
const rom UINT8 TCU_SPP_DATA_TRANSFER_REQ[23] = {0x17, 0x00, 0x00, 0xe5, 0x08, 0x10, 0x00, 0x0e, 0x00, 0x43, 0x42, 0x54, 0x2d, 0x33, 0x30, 0x30, 0x20, 0x52, 0x45, 0x41, 0x44, 0x4d, 0x45};
const rom UINT8 TCU_SPP_DISCONNECT_EVENT1[15] = {0x0f, 0x00, 0x00, 0xe5, 0x44, 0x08, 0x00, 0x00, 0x52, 0x75, 0x23, 0x2b, 0xa7, 0x50, 0x01};
const rom UINT8 TCU_SPP_DISCONNECT_EVENT2[15] = {0x0f, 0x00, 0x00, 0xe5, 0x44, 0x08, 0x00, 0x00, 0x52, 0x75, 0x23, 0x2b, 0xa7, 0x50, 0x02};
const rom UINT8 TCU_ACCEPT_SEND_EVENT[10] = {0x0a, 0x00, 0x00, 0xe1, 0xf1, 0x03, 0x00, 0x00, 0xe5, 0x08};
const rom UINT8 TCU_SPP_DATA_SEND_EVENT[7] = {0x07, 0x00, 0x00, 0xe5, 0xf1, 0x00, 0x00};
const rom UINT8 INCOMING_DATA[2] = {0xe5 , 0x48};
const rom UINT8 TCU_SPP_DISCONNECT_REQ[7] = {0x07, 0x00, 0x00, 0xe5, 0x04, 0x00, 0x00};
const rom UINT8 HCI_Encryption_Key_Refresh_Complete_Event[12] = {0x0C, 0x00, 0x00, 0xE1, 0x7D, 0x05, 0x00, 0x30, 0x03, 0x00, 0x01, 0x00};
const rom UINT8 TCU_ACCEPT[2] = {0xe5 , 0x48};
//////////////////////////////////////////////////



//////////////////////////////////////////////////
///////////For changing BT address///////////////////
const rom UINT8 TCU_HCI_M2_GENERAL_WRITE_EEPROM_REQ[26]={
0x01, 0x08, 0xfc, 0x16, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x14, 
0x89, 0xff, 0x10, 0x0c, 0xa0, 0x00, 0x01, 0x06, 0x02, 0x00, 
0x00, 0x13, 0x43, 0x0a, 0xee, 0xa7};
const rom UINT8 TCU_HCI_M2_GENERAL_WRITE_EEPROM_RESP[13]={
0x04, 0xff, 0x0a, 0x08, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x14, 0x89, 0x00, 0x00};
const rom UINT8 BTAdjustAddress[6]={0x97, 0xee, 0x0a, 0x43, 0x13, 0x00};

//////////////////////////////////////////////////

UINT8    BTState;
_BTRemoteData BTRemoteData;
UINT8    BTDeviceRecordedNum;


////////////////////////Debug information////////////////////////
/*
UINT8 TempUsart1[36][3]={"00",
"01","02","03","04","05","06","07","08","09","10",
"11","12","13","14","15","16","17","18","19","20",
"21","22","23","24","25","26","27","28","29","30",
"31","32","33","34","35"};*/


//UINT8 TempBTOK[]="OK";
//UINT8  TempCompair[2]={0xe1, 0x7d};

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
//UINT8 TempBTBuffer[50];

void BlueToothStatemachine(void)
{
	UINT8    i = 0;
	UINT8    TempBTValue;
   // State control
   switch (BTState) 
   {
      case BTReset:
         // Send reset command
         memcpypgm2ram( TempBTBuffer, TCU_HCI_RESET_REQ, 4 );
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,4);
         break;
      
      case Firmware:
         // Send firmware request command
         memcpypgm2ram( TempBTBuffer, TCU_HCI_GET_FIRMWARE_VERSION_REQ, 13 );
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,13);
         break;
   
      case I2C:
         // Send enable i2c request
         memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_BTL_SET_I2C_ENABLE_REQ, 15 );
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,15);
         break;
      
      case EnableEEPROM:
         // Send enable EEPROM request
         memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_BTL_EEPROM_WRITE_ENABLE_REQ, 13 );
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,13);
         break;
      
      case ReadEEPROM:
         // Send read EEPROM request
         memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_GENERAL_READ_EEPROM_REQ, 20 );
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,20);
         break;

      case SET_BAUDRATE:    
        // set baudrate
          memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_BTL_SET_BAUDRATE_REQ, 20 );
          DrvUsartSendData( USART_PORT_2,TempBTBuffer,20);
          DrvUsartInit( USART_PORT_2, USART_BAUD_RATE_57600, SerialPort2DrvBuffer, sizeof(SerialPort2DrvBuffer) );
          break;
///////////////////////////////////////////////////////////////////////////////////      
      case WriteBDAddress:
          //Assemble BD Address to TCU_HCI_WRITE_BD_ADDR_REQ
         memcpypgm2ram( TempBTBuffer, TCU_HCI_WRITE_BD_ADDR_REQ, 10 );
         for (i=0; i<6; i++) 
         {
            TempBTBuffer[4+i] = bdAddress[5-i];
         }
         /////////////////////////for change BD address////////////////////////////
          //Send write BD Address request
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,10);
         break;
      
      case SetMode:
         // Send set mode request
         memcpypgm2ram( TempBTBuffer, TCU_HCI_SET_MODE_REQ, 7 );
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,7);
         break;
      
      case MNGInit:
         // Send MNG initialisation request (Device Name: CBT-300-1234567890, Length 0x15)
        memcpypgm2ram( TempBTBuffer, TCU_MNG_INIT_REQ, sizeof(TCU_MNG_INIT_REQ) );
        for(i=0; i<10; i++)
        {
            TempBTBuffer[18+i] = SerialNumberData[i];
        }
        DrvUsartSendData( USART_PORT_2,TempBTBuffer, sizeof(TCU_MNG_INIT_REQ));
        break;
      
      case CoD:
         // Send Class of Device
         memcpypgm2ram( TempBTBuffer, TCU_MNG_STANDARD_HCI_SET_REQ_Write_Class_of_Device, 13 );
         DrvUsartSendData( USART_PORT_2, TempBTBuffer,13);
         break;
      
      case SPPSetup:
         // Send SPP setup request
         memcpypgm2ram( TempBTBuffer, TCU_SPP_SETUP_REQ, 7 );
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,7);
         break;
      
      case MNGScan:
         // Send inquiry and page scan request
         memcpypgm2ram( TempBTBuffer, TCU_MNG_SET_SCAN_REQ, 8 );
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,8);
         break;
////////////////////////////////////Initial completely//////////////////////////////////////////////////////////////
      case BTReady:
         break;

      case BTReady2:
         break;

      case BTReady3:
         break;
      case BTReady4:
		 break;

      case ConnectionRequested:
        if(BTRemoteData.PairFlg == TRUE)
        {
            memcpypgm2ram( TempBTBuffer, TCU_MNG_CONNECTION_ACCEPT_REQ_LINK_KEY, sizeof(TCU_MNG_CONNECTION_ACCEPT_REQ_LINK_KEY)); 
            for(i=0; i<6; i++)
            {
               TempBTBuffer[8+i] = BTRemoteData.RemoteBDAdress[i];// get the Remote Bdaddress
            }
            for(i=0; i<16; i++)
            {
               TempBTBuffer[15+i] = BTRemoteData.RemoteLinkKey[i];// get the Remote Bdaddress
            }
             // Send Connect with link-key
             DrvUsartSendData( USART_PORT_2,TempBTBuffer,31); 
        }
        else
        {
         	memcpypgm2ram( TempBTBuffer, TCU_MNG_CONNECTION_ACCEPT_REQ, 15 );
         	for(i=0; i<6; i++) 
         	{
        		TempBTBuffer[8+i] = REMOTE_BDADDRESS[i];
         	}
         	DrvUsartSendData(USART_PORT_2, TempBTBuffer,15);
        }
        break;

      case ConnectionRequested2:
         // Add BD address defined in commands.h to HCI IO capability reply HCI_IO_Capability_Request_Event
         memcpypgm2ram( TempBTBuffer, TCU_MNG_SSP_SET_REQ_HCI_IO_Capability_Request_Reply, 19 );
         for(i=0; i<6; i++) 
         {
            TempBTBuffer[10+i] = REMOTE_BDADDRESS[i];
         }
         // Send secure simple pairing reply
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,19);
         break;

      case SPPConnect:
         for(i=0; i<6; i++) 
         {
            TCU_SPP_CONNECT_REQ[7+i] = REMOTE_BDADDRESS[i];
         }
            // Send ACL and SPP connection request
         DrvUsartSendData( USART_PORT_2,TCU_SPP_CONNECT_REQ,23);
         break;

      case SPPConnectSuccess: 
        memcpypgm2ram( TempBTBuffer, TCU_MNG_CONNECTION_ACCEPT_REQ_LINK_KEY, sizeof(TCU_MNG_CONNECTION_ACCEPT_REQ_LINK_KEY)); 
        for(i=0; i<6; i++)
        {
           TempBTBuffer[8+i] = REMOTE_BDADDRESS[i];// get the Remote Bdaddress
        }
        for(i=0; i<16; i++)
        {
           TempBTBuffer[15+i] = REMOTE_LINK_KEY[i];// get the Remote Bdaddress
        }
         // Send Connect with link-key
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,31);         
         break;
      
      case MNGDiscoverRemote:
         for(i=0; i<6; i++) 
         {
            TCU_MNG_DISCOVER_REMOTE_SERVICE_REQ[8+i] = REMOTE_BDADDRESS[i];
         }
            // Send ACL and SPP connection request
         DrvUsartSendData( USART_PORT_2,TCU_MNG_DISCOVER_REMOTE_SERVICE_REQ,15);
	   
         break;

      case ControlSSP2:
         // Add BD address defined in commands.h to HCI user confirmation request reply
         memcpypgm2ram( TempBTBuffer, TCU_MNG_SSP_SET_REQ_HCI_User_Confirmation_Request_Reply, sizeof(TCU_MNG_SSP_SET_REQ_HCI_User_Confirmation_Request_Reply) );
         for(i=0; i<6; i++) 
         {
            TempBTBuffer[10+i] = REMOTE_BDADDRESS[i];
         }
         // Send user confirmation request reply
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,17);
         break;

      case ControlSSP3:
         // 	  	
         break;
      
      case SPPDataTransfer:
         // Send user confirmation request reply
         break;
      
      case BTSPPReady2:
         break;

      case BTSPPReady3:
         // 	  	
         break;		 

      case TestConnection:  

         break;

      case SPPDisconnect:  
         // Add BD address defined in commands.h to HCI IO capability reply HCI_IO_Capability_Request_Event
         memcpypgm2ram( TempBTBuffer, TCU_SPP_DISCONNECT_REQ, sizeof(TCU_SPP_DISCONNECT_REQ));
         // Send disconect
         DrvUsartSendData( USART_PORT_2,TempBTBuffer,sizeof(TCU_SPP_DISCONNECT_REQ)); 	
         break;

      case Pairing_Waiting:
        break;

      case PairingComplete:
         break;

      case WaitingState:
         break;
	  
	case BTM2WriteEEProm:
     	memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_GENERAL_WRITE_EEPROM_REQ, 26 );
     	memcpypgm2ram( &TempBTBuffer[19], BTAdjustAddress, 6 );
     	DrvUsartSendData( USART_PORT_2,TempBTBuffer,26);
	    break;
        
    default:
        break;
	  
   }
}

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

void SysInitBlueToothRadio(void)
{
	SysBTReset();
    memset((void *)BTRemoteData.RemoteBDAdress, 0x00, sizeof(BTRemoteData.RemoteBDAdress));
    memset((void *)BTRemoteData.RemoteLinkKey, 0x00, sizeof(BTRemoteData.RemoteLinkKey));
    BTRemoteData.PairFlg = FALSE;
    memset((void *)&BTData, 0x00, sizeof(_BTData));
}

//
//
//

UINT8 SysProcessBluetoothCommand( CHAR* pBuffer)
{
   UINT8 Result = 0, i = 0;
   UINT32 size;
   CHAR* commandBuffer;
   _BTRemoteData BTRemoteDataTemp;
   
   switch (BTState)
   {
      case BTReset:
        if(memcmppgm2ram((void *)pBuffer, (rom void *)TCU_HCI_RESET_RESP,7) == 0)	 	
        {
	        SysBTSetState(Firmware); 
           	BlueToothStatemachine();  
           	Result = 1;
         }
         break;

      case Firmware:
	  if(memcmppgm2ram((void *)pBuffer, (rom void *)TCU_HCI_GET_FIRMWARE_VERSION_RESP,33) == 0)		 	
         {
        	SysBTSetState(I2C);
        	BlueToothStatemachine();
        	Result = 1;
         }
         break;

      case I2C:
         memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_BTL_SET_I2C_ENABLE_RESP, sizeof(TCU_HCI_M2_BTL_SET_I2C_ENABLE_RESP));
         if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_HCI_M2_BTL_SET_I2C_ENABLE_RESP))==0)	
         {
            SysBTSetState(EnableEEPROM);
            BlueToothStatemachine();
            Result = 1;
         }
         break;

      case EnableEEPROM:
         memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_BTL_EEPROM_WRITE_ENABLE_RESP, sizeof(TCU_HCI_M2_BTL_EEPROM_WRITE_ENABLE_RESP));
         if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_HCI_M2_BTL_EEPROM_WRITE_ENABLE_RESP))==0)	 	
         {
            SysBTSetState(ReadEEPROM);
            BlueToothStatemachine();
            Result = 1;
         }
         break;

      case ReadEEPROM:
         memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_GENERAL_READ_EEPROM_RESP, sizeof(TCU_HCI_M2_GENERAL_READ_EEPROM_RESP));
         if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_HCI_M2_GENERAL_READ_EEPROM_RESP)-6)==0)// it should be read local BD
         {
         	for(i=0; i<6; i++)
         	{
         		bdAddress[i] = pBuffer[14+i]; // read Local BDadress
         	}
         	    SysBTSetState(WriteBDAddress);			
            	BlueToothStatemachine();
            	Result = 1;
         }
         break;

      case SET_BAUDRATE:
          memcpypgm2ram( TempBTBuffer, TCU_HCI_M2_BTL_SET_BAUDRATE_RESP, sizeof(TCU_HCI_M2_BTL_SET_BAUDRATE_RESP));
          if(memcmp((void *)(pBuffer + 2), (void *)(TempBTBuffer + 2), 10)==0)       
          {
             SysBTSetState(WriteBDAddress);
             BlueToothStatemachine();
             Result = 1;
          }
////////////////////////////////////////////////////////////////////////////////////
      case WriteBDAddress:
         memcpypgm2ram( TempBTBuffer, TCU_HCI_WRITE_BD_ADDR_RESP, sizeof(TCU_HCI_WRITE_BD_ADDR_RESP));
         if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_HCI_WRITE_BD_ADDR_RESP))==0)
         {
            	SysBTSetState(SetMode);
            	BlueToothStatemachine();
            	Result = 1;
         }
         break;

      case SetMode:
         memcpypgm2ram( TempBTBuffer, TCU_HCI_SET_MODE_RESP, sizeof(TCU_HCI_SET_MODE_RESP));
         if(memcmp((void *)pBuffer, (void *)TempBTBuffer, sizeof(TCU_HCI_SET_MODE_RESP))==0)
         {
            	SysBTSetState(MNGInit);
            	BlueToothStatemachine();
            	Result = 1;
         }
         break;

      case MNGInit:
         memcpypgm2ram( TempBTBuffer, TCU_MNG_INIT_RESP, sizeof(TCU_MNG_INIT_RESP));
         for(i=0; i<6; i++)
		 {
            TempBTBuffer[8+i] = bdAddress[5-i];
         }
		 commandBuffer = TempBTBuffer;      
         if(memcmp((void *)pBuffer, (void *)commandBuffer,sizeof(TCU_MNG_INIT_RESP))==0)
         {
            	SysBTSetState(CoD);
            	BlueToothStatemachine();
            	Result = 1;
         }
         break;

      case CoD:
         memcpypgm2ram( TempBTBuffer, TCU_MNG_STANDARD_HCI_SET_RESP_Write_Class_of_Device, sizeof(TCU_MNG_STANDARD_HCI_SET_RESP_Write_Class_of_Device));
         if(memcmp((void *)pBuffer, (void *)TempBTBuffer, sizeof(TCU_MNG_STANDARD_HCI_SET_RESP_Write_Class_of_Device))==0)
         {
            SysBTSetState(SPPSetup);
            BlueToothStatemachine();
            Result = 1;
         }  
         break;

      case SPPSetup:
         memcpypgm2ram( TempBTBuffer, TCU_SPP_SETUP_RESP, sizeof(TCU_SPP_SETUP_RESP));
         if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_SPP_SETUP_RESP))==0)
         {
           	SysBTSetState(MNGScan);
           	BlueToothStatemachine();
            	Result = 1;
         }
         break;
	   case MNGScan:
        memcpypgm2ram( TempBTBuffer, TCU_MNG_SET_SCAN_RESP, sizeof(TCU_MNG_SET_SCAN_RESP));
        if(memcmp((void *)pBuffer, (void *)TempBTBuffer, sizeof(TCU_MNG_SET_SCAN_RESP))==0)
        {
            SysBTSetState(BTReady);  
            BlueToothStatemachine();
            Result = 1;
			BLOperatingState = BL_BLUETOOTH_INIT_DONE;
        }
		 break;
	//////////////////////////////////Prepair for pair////////////////////////////////////////
      case BTReady:
            memcpypgm2ram( TempBTBuffer, TCU_MNG_CONNECTION_ACCEPT_REQUEST_EVENT, sizeof(TCU_MNG_CONNECTION_ACCEPT_REQUEST_EVENT));//{0x10, 0x00, 0x00, 0xe1, 0x55, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x11, 0xc0};	 
            if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_MNG_CONNECTION_ACCEPT_REQUEST_EVENT))==0)
            {
                for(i=0; i<6; i++)
                {
                    REMOTE_BDADDRESS[i]= pBuffer[7+i];// get the Remote Bdaddress
                }
                for(i=0; i<3; i++)
                {
                    BTClassDevice[i]= pBuffer[13+i];
                }
                if((BTRemoteData.PairFlg == TRUE) &&
                    (memcmp((void *)BTRemoteData.RemoteBDAdress, (void *)REMOTE_BDADDRESS,sizeof(REMOTE_BDADDRESS)) == 0))
                {
                    SysBTSetState(ConnectionRequested);  
                    BlueToothStatemachine();
                    Result = 1; 
                }
                else
                {
                    BTRemoteData.PairFlg = FALSE;
                    for(i = 0; i < BT_DEVICE_RECORDED_NUM_MAX; i++)
                    {
                        DrvEepromRead(EEBTRemoteDataAddress + (sizeof(_BTRemoteData) * i), (UINT8*)&BTRemoteDataTemp, sizeof(_BTRemoteData));
                        if((BTRemoteDataTemp.PairFlg == TRUE) &&
                            (memcmp((void *)BTRemoteDataTemp.RemoteBDAdress, (void *)REMOTE_BDADDRESS,sizeof(REMOTE_BDADDRESS)) == 0))
                        {
                            memcpy((void *)BTRemoteData.RemoteBDAdress, (void *)BTRemoteDataTemp.RemoteBDAdress,sizeof(BTRemoteDataTemp.RemoteBDAdress));
                            memcpy((void *)BTRemoteData.RemoteLinkKey, (void *)BTRemoteDataTemp.RemoteLinkKey,sizeof(BTRemoteDataTemp.RemoteLinkKey));
                            BTRemoteData.PairFlg = TRUE;
                            BTDeviceRecordedNum = i;
                            break;
                        }
                    }
                    SysBTSetState(ConnectionRequested);  
                    BlueToothStatemachine();
                    Result = 1;  
                }
            }
            break;

      case ConnectionRequested:
            memcpypgm2ram( TempBTBuffer, TCU_MNG_CONNECTION_ACCEPT_RESP, sizeof(TCU_MNG_CONNECTION_ACCEPT_RESP));
            if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_MNG_CONNECTION_ACCEPT_RESP))==0)
            {
                Result = 1;
                SysBTSetState(BTReady2);
                BlueToothStatemachine();
            }
            break;

      case BTReady2: 	
         	memcpypgm2ram(TempBTBuffer,TCU_MNG_CONNECTION_STATUS_EVENT, 15 );
            for(i=0; i<6; i++)
            {
               TempBTBuffer[8+i] = REMOTE_BDADDRESS[i];
            }
            if(memcmp((void *)pBuffer, (void *)TempBTBuffer, 14)==0)
            {
                SysBTSetState(BTReady3);
                BlueToothStatemachine();
                Result = 1;
            }		
            break;

      case BTReady3:
            memcpypgm2ram(TempBTBuffer,HCI_IO_Capability_Response_Event, 18 );
            for(i=0; i<6; i++)
            {
               	TempBTBuffer[9+i] = REMOTE_BDADDRESS[i];
            }
            commandBuffer = TempBTBuffer;
            if(memcmp((void *)pBuffer, (void *)commandBuffer,15)==0)
            {
                SysBTSetState(REMOTE_DEVICE_NOTIFY);
                BlueToothStatemachine();
                Result = 1;
                break;
            }
            else
            {
                // the bluetooth device is found and the link key is correct
                memcpypgm2ram(TempBTBuffer,TCU_SPP_CONNECT_EVENT2, sizeof(TCU_SPP_CONNECT_EVENT2) );
                if((memcmp((void *)&pBuffer[3], (void *)TempBTBuffer, sizeof(TCU_SPP_CONNECT_EVENT2))==0)&&
                   (memcmp((void *)&pBuffer[8], (void *)REMOTE_BDADDRESS, sizeof(REMOTE_BDADDRESS))==0))    
                {   
                   SysBTSetState(DEF_TCU_MNG_SSP_INFO_EVENT);
                   BlueToothStatemachine();
                   Result = 1;
                }
            }
            break;

      case REMOTE_DEVICE_NOTIFY:
            memcpypgm2ram(TempBTBuffer,TCU_MNG_REMOTE_DEVICE_NAME_AUTO_NOTIFY_EVENT,20);
            for(i=0; i<6; i++)
            {
               	TempBTBuffer[7+i] = REMOTE_BDADDRESS[i];
            }
            if((memcmp((void *)(pBuffer + 3), (void *)(TempBTBuffer + 3),2)==0)&&
                (memcmp((void *)(pBuffer + 7), (void *)(TempBTBuffer + 7),6)==0))
            {
               	SysBTSetState(HCI_IO_CAPABILITY_REQUEST_EVENT);
               	BlueToothStatemachine();
               	Result = 1;
            }
            break;

      case HCI_IO_CAPABILITY_REQUEST_EVENT:
          memcpypgm2ram(TempBTBuffer,HCI_IO_Capability_Request_Event,15);
          for(i=0; i<6; i++)
          {
              TempBTBuffer[9+i] = REMOTE_BDADDRESS[i];
          }
          if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(HCI_IO_Capability_Request_Event))==0)
          {
              SysBTSetState(ConnectionRequested2);
              BlueToothStatemachine();
              Result = 1;
          }
          break;
      
      case ConnectionRequested2:
         	memcpypgm2ram(TempBTBuffer,TCU_MNG_SSP_SET_RESP_HCI_IO_Capability_Request_Reply, 21 );
            for(i=0; i<6; i++) 
            {
               TempBTBuffer[15+i] = REMOTE_BDADDRESS[i];
            }
            commandBuffer = TempBTBuffer;
            if(memcmp((void *)pBuffer, (void *)commandBuffer,sizeof(TCU_MNG_SSP_SET_RESP_HCI_IO_Capability_Request_Reply))==0)
            {
               SysBTSetState(BTReady4);
               BlueToothStatemachine();
               Result = 1;
            }
            break;
            
      case BTReady4:
         	memcpypgm2ram(TempBTBuffer,HCI_IO_User_Confirmation_Request_Event,15);
         	for(i=0; i<6; i++)
         	{
            		TempBTBuffer[9+i] = REMOTE_BDADDRESS[i];
         	}
         	commandBuffer = TempBTBuffer;
         
         	if(memcmp((void *)pBuffer, (void *)commandBuffer,sizeof(HCI_IO_User_Confirmation_Request_Event))==0)
         	{
        		SysBTSetState(ControlSSP2);
        		BlueToothStatemachine();
        		Result = 1;
         	}    
            break;
            
      case ControlSSP2:
         	memcpypgm2ram(TempBTBuffer,TCU_MNG_SSP_SET_RESP_HCI_User_Confirmation_Request_Reply,21);
         	for(i=0; i<6; i++)
         	{
        		TempBTBuffer[15+i] = REMOTE_BDADDRESS[i];
         	}
         	commandBuffer = TempBTBuffer;
         	if(memcmp((void *)pBuffer, (void *)commandBuffer,sizeof(TCU_MNG_SSP_SET_RESP_HCI_User_Confirmation_Request_Reply))==0)
         	{
        		SysBTSetState(PairingComplete);
        		BlueToothStatemachine();
        		Result = 1;
         	}
            break;
            
      case PairingComplete:
            memcpypgm2ram(TempBTBuffer,HCI_Simple_Pairing_Complete_Event,16);
            for(i=0; i<6; i++)
            {
                TempBTBuffer[10+i] = REMOTE_BDADDRESS[i];
            }
            commandBuffer = TempBTBuffer;
            if(memcmp((void *)pBuffer, (void *)commandBuffer,sizeof(HCI_Simple_Pairing_Complete_Event))==0)
            {
                SysBTSetState(ControlSSP3);
                BlueToothStatemachine();
                Result = 1;
            }
            else
            {   // select Cancel on the Mobile or PC
                memcpypgm2ram(TempBTBuffer,HCI_Simple_Pairing_Complete_Cancel_Event,16);
                for(i=0; i<6; i++)
                {
                    TempBTBuffer[10+i] = REMOTE_BDADDRESS[i];
                }
                commandBuffer = TempBTBuffer;
                if(memcmp((void *)pBuffer, (void *)commandBuffer,sizeof(HCI_Simple_Pairing_Complete_Cancel_Event))==0)
                {
                    SysBTSetState(ControlSSP3);
                    BlueToothStatemachine();
                    Result = 1;
                }

            }
            break;
            
      case ControlSSP3:
           if(pBuffer[0] == 0x20)   // User select Allow on the Mobile Phone or PC
           {
             	memcpypgm2ram(TempBTBuffer,TCU_MNG_CONNECTION_STATUS_EVENT3,15);
             	for(i=0; i<6; i++)
             	{
            		TempBTBuffer[8+i] = REMOTE_BDADDRESS[i];
             	}
             	if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_MNG_CONNECTION_STATUS_EVENT3))==0)
             	{
        			for(i=0; i<16; i++)
        			{
                    	REMOTE_LINK_KEY[i] = pBuffer[15+i];
                    }   
        			//store Remote_Link_Key  DrvEepromWrite()
                    memcpy((void *)&BTRemoteData.RemoteLinkKey, (void *)REMOTE_LINK_KEY, sizeof(REMOTE_LINK_KEY));
                    memcpy((void *)&BTRemoteData.RemoteBDAdress, (void *)REMOTE_BDADDRESS, sizeof(REMOTE_BDADDRESS));
        			if(BTRemoteData.PairFlg == FALSE)
        			{
            			BTRemoteData.PairFlg = TRUE;
                        for(i = 0; i < BT_DEVICE_RECORDED_NUM_MAX; i++)
                        {
                            DrvEepromRead(EEBTRemoteDataAddress + (sizeof(_BTRemoteData) * i), (UINT8*)&BTRemoteDataTemp, sizeof(_BTRemoteData));
                            if(BTRemoteDataTemp.PairFlg != 0x01)
                            {
                                // record the BT information in the EEPROM
                                DrvEepromWrite(EEBTRemoteDataAddress + (sizeof(_BTRemoteData) * i), (UINT8*)&BTRemoteData, sizeof(_BTRemoteData));
                                break;
                            }
                        }
                        if(i == BT_DEVICE_RECORDED_NUM_MAX)
                        {
                            // all EEPROM space are stored, recover the first blank
                            DrvEepromWrite(EEBTRemoteDataAddress, (UINT8*)&BTRemoteData, sizeof(_BTRemoteData));
                        }
        			}
                    else 
                    {
                        // we need to update the link key data
                        DrvEepromWrite(EEBTRemoteDataAddress + (sizeof(_BTRemoteData) * BTDeviceRecordedNum), (UINT8*)&BTRemoteData, sizeof(_BTRemoteData));
                    }
                    SysBTSetState(BT_PAIR_DONE);
                    BlueToothStatemachine();
                    Result = 1;
             	}
           }
           else if(pBuffer[0] == 0x0F)  // User select Cancel on the PC
           {
               memcpypgm2ram(TempBTBuffer,TCU_MNG_CONNECTION_STATUS_EVENT2,15);
               for(i=0; i<6; i++)
               {
                   TempBTBuffer[8+i] = REMOTE_BDADDRESS[i];
               }
               if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_MNG_CONNECTION_STATUS_EVENT2))==0)
               {
                   SysBTSetState(BTReady);      // waiting for re-pair require
                   BlueToothStatemachine();
                   Result = 1;
               }
           }
   	       break;

       case BT_PAIR_DONE:   // judge if only pair done or SPP connected
         	memcpypgm2ram(TempBTBuffer,TCU_MNG_CONNECTION_STATUS_EVENT2,15);
         	for(i=0; i<6; i++)
         	{
        		TempBTBuffer[8+i] = REMOTE_BDADDRESS[i];
         	}
         	if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_MNG_CONNECTION_STATUS_EVENT2))==0)
         	{			
                BLOperatingState = BL_BLUETOOTH_PAIR_DONE;
                SysBTSetState(BTReady);
                BlueToothStatemachine();
                Result = 1;
         	}
           break;	
           
        case BTSPPReady3:
              memcpypgm2ram(TempBTBuffer,TCU_SPP_CONNECT_EVENT2, sizeof(TCU_SPP_CONNECT_EVENT2) );
              if((memcmp((void *)&pBuffer[3], (void *)TempBTBuffer, sizeof(TCU_SPP_CONNECT_EVENT2))==0)&&
                 (memcmp((void *)&pBuffer[8], (void *)REMOTE_BDADDRESS, sizeof(REMOTE_BDADDRESS))==0))    
              {   
                 SysBTSetState(DEF_TCU_MNG_SSP_INFO_EVENT);
                 BlueToothStatemachine();
                 Result = 1;
              }
              break;

        case DEF_TCU_MNG_SSP_INFO_EVENT:
            memcpypgm2ram( TempBTBuffer, HCI_Encryption_Key_Refresh_Complete_Event, sizeof(HCI_Encryption_Key_Refresh_Complete_Event));
            if(memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(HCI_Encryption_Key_Refresh_Complete_Event))==0)
            {
                BLOperatingState = BL_BLUETOOTH_CONNECTED;
                SysBTSetState(WaitingState);
                BlueToothStatemachine();
                Result = 1;            
            } 
            break;
            
   case WaitingState:
/****READY TO EXCEPT MESSAGES AND PAIRED ***********/
  
//////////////////////Receive Data and Display ///////////////////////
        if(BLDataStatus == BLUETOOTH_IDLE)
        {
            memcpypgm2ram(TempBTBuffer,INCOMING_DATA, sizeof(INCOMING_DATA));
            if(0 == memcmp((void *)&pBuffer[0x03], (void *)TempBTBuffer,sizeof(INCOMING_DATA))) //New BlueSPP old Verson5.4.3
            {
                Result = 1;
                BTData.BTDataLength = *(pBuffer + 7);
                for(i = 0; i < BTData.BTDataLength; i++)
                    BTData.BTDataBuffer[i] = pBuffer[9 + i];
                //memcpy((char *)BTData.BTDataBuffer,(const char *)(pBuffer + 9), BTData.BTDataLength);
                BLDataStatus = BLUETOOTH_DATA_RECEIVED;
                DrvUsartReset(USART_PORT_2);
                break;
            }
        }
//////////////////////  Send data response /////////////////////////////  
        if(BLDataStatus == BLUETOOTH_DATA_SENDING_1)
        {
            memcpypgm2ram(TempBTBuffer,TCU_ACCEPT_SEND_EVENT,sizeof(TCU_ACCEPT_SEND_EVENT));
            if(0 == memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_ACCEPT_SEND_EVENT)))
            {
                Result = 1;
                BLDataStatus = BLUETOOTH_DATA_SENDING_2;
                break;
            }
        }
        else if(BLDataStatus == BLUETOOTH_DATA_SENDING_2)
        {
            memcpypgm2ram(TempBTBuffer,TCU_SPP_DATA_SEND_EVENT,sizeof(TCU_SPP_DATA_SEND_EVENT));
            if(0 == memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_SPP_DATA_SEND_EVENT)))
            {
                Result = 1;
                BLDataStatus = BLUETOOTH_IDLE;
                break;
            }
        }

//////////////////////Disconnect Process///////////////////////
        memcpypgm2ram(TempBTBuffer,TCU_SPP_DISCONNECT_EVENT2,sizeof(TCU_SPP_DISCONNECT_EVENT2));
        for(i=0; i<6; i++) 
        {
          TempBTBuffer[8+i] = REMOTE_BDADDRESS[i];
        }
        
        if(0 == memcmp((void *)pBuffer, (void *)TempBTBuffer,sizeof(TCU_SPP_DISCONNECT_EVENT2)))
        {
            Result = 1;
            SysBTSetState(BTReady);  
            BlueToothStatemachine();
            BLOperatingState = BL_BLUETOOTH_INIT_DONE;
        }
        break;

	case BTM2WriteEEProm:
        if(memcmppgm2ram((void *)pBuffer, (rom void *)TCU_HCI_M2_GENERAL_WRITE_EEPROM_RESP, 13) == 0)	 	
        {
            SysBTSetState(WriteBDAddress); 
            BlueToothStatemachine();  
            Result = 1;
        }
	    break;
		 
   }     
   return(Result);
}

//
//
//

void SysBTSetState(UINT8 newState) 
{
   	// Set new state
	BTState = newState;
}

//
//
//

UINT8 SysBTGetState( void ) 
{
	return(BTState );
}
//
//
//

void SysBTReset(void)
{
	SysBTSetState(BTReset);
	BlueToothStatemachine();
}
//
//
//
//

void SysBTWrapData(UINT8* Message, UINT16 Length)
{
	UINT16 MessageLength = Length;
	UINT32 MessageTotal = MessageLength + 9;
	UINT8 BlankMessage[9] = {0x00, 0x00, 0x00, 0xe5, 0x08, 0x00, 0x00, 0x00, 0x00};
	//MessageTotal + IncomingData + MessageLength + Message
	BlankMessage[7] = (MessageLength & 0xFF);
	BlankMessage[8] = ((MessageLength & 0xFF00) >> 8);
	BlankMessage[5] = ((MessageLength+2) & 0xFF);
	BlankMessage[6] = (((MessageLength+2) & 0xFF00) >> 8); 
	BlankMessage[0] = (MessageTotal & 0xFF);
	BlankMessage[1] = (MessageTotal & 0xFF00);
	BlankMessage[2] = (MessageTotal & 0xFF0000);
   	memcpy((void*)TempBTBuffer, (void*)BlankMessage,9);
   	memcpy((void*)&TempBTBuffer[9],(void*)Message,Length);
}

//
//
//

void SysBTSendData(UINT8* Message, UINT16 Length)
{
	SysBTWrapData(Message,Length);
	DrvUsartSendData(USART_PORT_2,TempBTBuffer,(Length+9));
}

//
//
//
UINT8 WriteFrameHeader(UINT16 DataLength, UINT16 PacketId)
{
   UINT8    CkSum = 0;

                                       //set DLE character
   //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
   WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
                                       //send packet ID character and add to checksum tab
   //DrvUsartSendByte( Port, PacketId / 256 );
   WrapperBuffer[WrapperBufferSize++] = PacketId / 256;
   CkSum += (PacketId / 256);
   if((PacketId / 256) == DATA_LINK_ESCAPE)
   {
      //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }
   //DrvUsartSendByte( Port, PacketId % 256);
   WrapperBuffer[WrapperBufferSize++] = PacketId % 256;
   CkSum += (PacketId % 256);
   if((PacketId % 256) == DATA_LINK_ESCAPE)
   {
      //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }
                                       //send message length
   //DrvUsartSendByte( Port, DataLength / 256 );
   WrapperBuffer[WrapperBufferSize++] = DataLength / 256;
   CkSum += (DataLength / 256);
   if((DataLength / 256) == DATA_LINK_ESCAPE)
   {
      //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }
   //DrvUsartSendByte( Port, DataLength % 256 );
   WrapperBuffer[WrapperBufferSize++] = DataLength % 256;
   CkSum += (DataLength % 256);
   if((DataLength % 256) == DATA_LINK_ESCAPE)
   {
      //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }
      
   return(CkSum);
}

//
// Function:      
// 
// Parameters:    pointer to data
//                data buffer length
//                current checksum
//                serial port id
// Return Value:  Sum of bytes 1 - (n-4) excluding DLE characters
// 
// Description:   adds data to buffer and computes sum of bytes
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
//

UINT8 WritePayload(UINT8* pData, UINT16 Length, UINT8 CkSum)
{
   UINT16   i;

   for(i = 0; i < Length; i++, pData++)
   {
      //DrvUsartSendByte( Port, *pData );
      WrapperBuffer[WrapperBufferSize++] = *pData;
      CkSum += *pData;                 //compute checksum
      if (*pData == DATA_LINK_ESCAPE)
      {
         //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
         WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
      }
   }
   return(CkSum);                      //return checksum
}

//
// Function:      
// 
// Parameters:    pointer to data buffer
//                data buffer length
//                packet id
//                serial port id
// Return Value:  None
// 
// Description:   Wraps passed data buffer per Serial protocol specification and send out the serial port
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
//
void SysWrapperWrapMessage(UINT8* pData, UINT16 DataLength, UINT16 PacketId)
{
   UINT8    CkSum;
   
   //clear wrapper buffer
   memset(WrapperBuffer, 0x00, 128);
   WrapperBufferSize = 0;

   CkSum = WriteFrameHeader(DataLength, PacketId);
   CkSum = WritePayload(pData, DataLength, CkSum);

   CkSum = 0xFF - CkSum;
   WrapperBuffer[WrapperBufferSize++] = CkSum;
   if (CkSum == DATA_LINK_ESCAPE)
   {
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }

   //send DLE and ETX characters to signify end of transmission
   //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
   WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   //DrvUsartSendByte( Port, END_OF_TEXT );
   WrapperBuffer[WrapperBufferSize++] = END_OF_TEXT;

   //put code here to send buffer over bluetooth
   SysBTSendData(WrapperBuffer, WrapperBufferSize);
   
}


