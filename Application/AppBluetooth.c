/****************************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     This module defines the error handling routine(s)
;
****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "AppData.h"
#include "AppBluetooth.h"
#include "BootLoad.h"
#include "SysBluetooth.h"
#include "SysDisplay.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvTimer_18F67J10.h"
#include "DrvEeprom_25AA320.h"
#include "DrvUsart_18F67J10.h"
#include "DrvInt_18F67J10.h"

CHAR  SerialRxBuffer2[160];

const rom char BTInitializeChar[]="BT INITIALIZE";
const rom char BTReadyChar[]="BT READY";
const rom char BTPleaseWait[]="PLEASE WAIT";
const rom char BTPleaseConnect[]="PLEASE CONNECT";
const rom char BTPairChar[]="BT PAIR DONE";
const rom char BTReadyForUpdating[]="READY FOR UPDATING";
const rom char BTConnectComplete[]="BT CONNECTED";
const rom char BTWaitingForUpdating[]="WAITING FOR UPDATING";
const rom char Command_VS[4] = {0x7B, 0x56, 0x53, 0x7D}; // {VS}
const rom char Command_Boot[6] = {0x7B, 0x42, 0x4F, 0x4F, 0x54, 0x7D};  // BOOT
const rom char LoadingDataText2[] = {"LOADING DATA2"};


void BluetoothSendData(UINT8 *buffer, UINT16 datalength);

void ProcessSerialBuffer1(CHAR* pBuffer)
{
   if((strcmppgm2ram((char*)pBuffer, "{BOOT}") == 0)||
      (strcmppgm2ram((char*)pBuffer, "{VS}") == 0))
   {
        DrvIntEnable( INT_ID_USART_1_RX, INT_DISABLE);
        BootLoad();
   }
   DrvUsartReset(USART_PORT_1);       
}

volatile UINT8 AppCheckSerialPort( CHAR* pBuffer, UINT8 mode)
{                                      //get the status
   UINT8         NumOfBytes;
   UINT8         BytesAvailable, BytesRead;
   volatile UINT8 Status;

   Status = DrvUsart2GetStatus();
   BytesAvailable = DrvUsart2GetNumberOfBytesAvailable();

   if(Status & (USART_STATUS_FRAME_ERROR|USART_STATUS_OVERRUN_ERROR))
   {                                   //error
      DrvUsartReset(USART_PORT_2);             //reset the port
   }
   else if(Status & (USART_STATUS_BUFFER_ERROR | USART_STATUS_TIMEOUT))
   {                                   //read the bytes from the serial port driver
        if(mode == BLUETOOTH_DATA_NORMAL)
        {
      		NumOfBytes = DrvUsart2Read(pBuffer, BytesAvailable);
      		*(pBuffer + NumOfBytes) = '\0';  //add the NULL character
        }
        else if(mode == BLUETOOTH_DATA_SPECIAL)
        {
            BytesRead = DrvUsart2GetMessageLength();
            if(BytesRead <= BytesAvailable)
            {
                NumOfBytes = DrvUsart2Read(pBuffer, BytesRead);
                *(pBuffer + NumOfBytes) = '\0';  //add the NULL character
                //DrvUsartSendData(USART_PORT_1, pBuffer, BytesRead);
            }
        }
   }
      
   return(Status);
}



void BlueToothState(void)
{
    CHAR        Char;
	CHAR*       pBuffer1;
    UINT32      Temp;
    UINT32      LoadAddr;
    UINT32      Address;
    UINT8       Command;
    UINT8       HostCheckSum;
    UINT8       ToolCheckSum;
    UINT8       i;
    UINT8       AddressCounter;
    UINT8       BootloaderModeFlag;
    
    while(1)
    {
        if((DrvUsartByteReady(USART_PORT_2)) &&
           (AppCheckSerialPort(SerialRxBuffer2, ((BTState >= BTReady)?BLUETOOTH_DATA_SPECIAL : BLUETOOTH_DATA_NORMAL))
                &(USART_STATUS_BUFFER_ERROR | USART_STATUS_TIMEOUT)))
        {
              if(SysProcessBluetoothCommand(SerialRxBuffer2) == 1)
              {
                //DrvUsartSendByte(USART_PORT_1, BTState);
                memset(SerialRxBuffer2, 0x00, sizeof(SerialRxBuffer2));
              }
                         
        }
        switch(BLOperatingState)
        {
            case BL_BLUETOOTH_INIT:
                DrvTimer0SetCounter(TIMER0_MS_COUNTER_1, 1000);
                DisplayRomString(1, BootLoaderText);
                SysClear_Line_S(3);
                DisplayRomString(3, BTInitializeChar);
                SysClear_Line_S(4);
                DisplayRomString(4, BTPleaseWait);
                SysInitBlueToothRadio();
                BLOperatingState++;
                break;
                
            case BL_BLUETOOTH_INIT_WAIT:
                if(DrvTimer0CounterDone(TIMER0_MS_COUNTER_1))
                {
                    BLOperatingState = BL_BLUETOOTH_INIT;
                }
                break;

            case BL_BLUETOOTH_INIT_DONE:
                DisplayRomString(1, BootLoaderText);
                SysClear_Line_S(3);
                DisplayRomString(3, BTReadyChar);
                SysClear_Line_S(4);
                DisplayRomString(4, BTPleaseConnect);
                BLOperatingState++;
                break;

            case BL_UPDATE_WAIT:    // Update from MXT or Bluetooth    
                if(DrvUsartByteReady(USART_PORT_1))  //serial port 1 monitor
                {
                    if(DrvUsartReadByte(USART_PORT_1, &Char))
                    {
                        *pBuffer1++ = Char;
                        if(Char == '}')         //check for stop character
                        {
                            *pBuffer1 = '\0';     //add string terminator
                            ProcessSerialBuffer1(SerialRxBuffer1);
                            pBuffer1 = SerialRxBuffer1;
                        }
                        if(pBuffer1 > (SerialRxBuffer1 + sizeof(SerialRxBuffer1)))
                            pBuffer1 = SerialRxBuffer1;
                    }  
                } 
                break;

            case BL_BLUETOOTH_PAIR_DONE:
                Clear_Screen();
                DisplayRomString(1, BootLoaderText);
                SysClear_Line_S(3);
                DisplayRomString(3, BTPairChar);
                SysClear_Line_S(4);
                DisplayRomString(4, BTReadyForUpdating);
                BLOperatingState++;
                break;

            case BL_BLUETOOTH_PAIR_DONE_WAIT:
                break;

            case BL_BLUETOOTH_CONNECTED:
                Clear_Screen();
                DisplayRomString(1, BootLoaderText);
                SysClear_Line_S(3);
                DisplayRomString(3, BTConnectComplete);
                SysClear_Line_S(4);
                DisplayRomString(4, BTWaitingForUpdating);
                BLDataStatus = BLUETOOTH_IDLE;
                BLOperatingState++;
                break;

            case BL_BLUETOOTH_CONNECTED_WAIT:
                if(BLDataStatus == BLUETOOTH_DATA_RECEIVED)
                {
                    BLDataStatus = BLUETOOTH_DATA_PROCESSING;
                    DrvUsartSendData(USART_PORT_1, BTData.BTDataBuffer, BTData.BTDataLength);
                    memcpypgm2ram( TempBTBuffer, Command_VS, sizeof(Command_VS));
                    if(strncmp((const char *)TempBTBuffer, (const char *)BTData.BTDataBuffer, sizeof(Command_VS)) == 0)
                    {
                        BluetoothSendData(TempBTBuffer, sizeof(Command_VS));
                    }
                    else
                    {
                        memcpypgm2ram( TempBTBuffer, Command_Boot, sizeof(Command_Boot));
                        if(strncmp((const char *)TempBTBuffer, (const char *)BTData.BTDataBuffer, sizeof(Command_Boot)) == 0)
                        {
                            BluetoothSendData(TempBTBuffer, sizeof(Command_Boot));
                            BLOperatingState++;
                            BootloaderModeFlag = BL_NONE;
                        }
                    }
                }
                break;

            case BL_UPDATE_FROM_BLUETOOTH:
                if(BLDataStatus == BLUETOOTH_DATA_RECEIVED)
                {
                    BLDataStatus = BLUETOOTH_DATA_PROCESSING;
                    DrvUsartSendData(USART_PORT_1, BTData.BTDataBuffer, BTData.BTDataLength);
                    if(BootloaderModeFlag == BL_NONE)
                    {
                        BluetoothSendData(BTData.BTDataBuffer, 1);
                        switch(BTData.BTDataBuffer[0])
                        {
                            case 1:
                                break;

                            case 2:
                                BootloaderModeFlag = BL_FLASH;
                                break;

                            case 3:
                                Address = 0;
                                AddressCounter = 3;
                                BootloaderModeFlag = BL_ADDRESS;
                                DisplayRomString(3, LoadingDataText);
                                break;

                            case 4:
                                _asm RESET _endasm      // reboot
                                break;

                            case 5:
                                memcpypgm2ram( TempBTBuffer, VersionNumberText, 12);
                                BluetoothSendData(TempBTBuffer, 12);
                                break;
                        }
                        
                    }
                    else
                    {
                        if(BootloaderModeFlag == BL_ADDRESS)
                        {
                            AddressCounter--;
                            Temp = ((UINT32)BTData.BTDataBuffer[0]) & 0x00FF;
                            Address += Temp << (AddressCounter * 8);
                            if(AddressCounter == 0)
                            {
                                //erase address sector
                                EraseFlash(Address & (UINT32)P18F87_FLASH_LAST_ROW);
                                BootloaderModeFlag = BL_NONE;
                                LoadAddr = Address;
                                
                                BluetoothSendData(BTData.BTDataBuffer, 1);
                            }
                            else
                            {
                                BluetoothSendData(BTData.BTDataBuffer, 1);
                            }
                        }
                        else if(BootloaderModeFlag == BL_FLASH)
                        {
                            ToolCheckSum = 0;
                            for(i = 0; i < P18F87_FLASH_ROW_SIZE; i++)
                            {
                                CodeBuf[i] = BTData.BTDataBuffer[i];
                                ToolCheckSum += BTData.BTDataBuffer[i];
                            }
                            
                            HostCheckSum = BTData.BTDataBuffer[64];
                            BluetoothSendData(&HostCheckSum, 1);
                            
                            if((UINT32)LoadAddr < P18F87_FLASH_START_ADDRESS ||
                               (UINT32)LoadAddr > (P18F87_FLASH_END_ADDRESS - (P18F87_FLASH_ROW_SIZE - 1)))
                            {                    //force bad ACK to host
                               ToolCheckSum++;   //= ~HostCheckSum;
                                                 //cannot erase or program (out of range)
                               BluetoothSendData(&ToolCheckSum, 1);
                               break;
                            }

                            while((TXSTA1bits.TRMT == 0) || (TXSTA2bits.TRMT == 0))
                            {
                                CLRWDT();
                            }
                            
                            if(ToolCheckSum == HostCheckSum)
                            {                    
                                                 //program the row and config bits if necessary
                               if(WriteFlash((UINT32)LoadAddr, CodeBuf, PROGRAM_ALL) == FAIL)
                               {                 //force bad ACK to host
                                  ToolCheckSum = ~HostCheckSum; 
                               }
                               else
                               {                 //get ready for next block
                                  LoadAddr += P18F87_FLASH_ROW_SIZE;
                               }
                            }
                            else
                            {
                                ToolCheckSum = ~HostCheckSum;
                            }
                            BluetoothSendData(&ToolCheckSum, 1);
                            BootloaderModeFlag = BL_NONE;
                        }
                    }
                }
                break;
        }
    }
}

void BluetoothSendData(UINT8 *buffer, UINT16 datalength)
{
    SerialRxBuffer2[0] = ((UINT32)(datalength + 9)) & 0x0000FF;
    SerialRxBuffer2[1] = (((UINT32)(datalength + 9)) >> 8) & 0x0000FF;
    SerialRxBuffer2[2] = (((UINT32)(datalength + 9)) >> 16)& 0x0000FF;
    SerialRxBuffer2[3] = 0xE5;
    SerialRxBuffer2[4] = 0x08;
    SerialRxBuffer2[5] = (datalength + 2) & 0x00FF;
    SerialRxBuffer2[6] = ((datalength + 2) >> 8) & 0x00FF;
    SerialRxBuffer2[7] = datalength & 0x0000FF;
    SerialRxBuffer2[8] = (datalength >> 8) & 0x00FF;
    strncpy((char *)(SerialRxBuffer2 + 9), (const char *)buffer, datalength);
    DrvUsartSendData( USART_PORT_2, SerialRxBuffer2, datalength + 9);
    DrvUsartSendData( USART_PORT_1, SerialRxBuffer2, datalength + 9);
    BLDataStatus = BLUETOOTH_DATA_SENDING_1;
    while(TXSTA2bits.TRMT == 0)
    {
        CLRWDT();
    }
}

