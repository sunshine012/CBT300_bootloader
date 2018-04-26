/****************************************************************************
;
;  Copyright (c) Midtronics 2006
;
;     This module defines the calibrate routine(s).
;
****************************************************************************/
#include "pic18f87J10.h"
#include <stdio.h>
#include <string.h>

#include "MpLabC18.h"
#include "MdxP600.h"
#include "BootLoad.h"

#include "DrvSpi.h"
#include "DrvSound.h"
#include "DrvFlash_M25P16.h"
#include "DrvEeprom_25AA320.h"
#include "DrvRtc_M41T94.h"
#include "DrvLcd_MID184_310.h"
#include "DrvSsp_18F87J10.h"
#include "DrvUsart_18F87J10.h"
#include "DrvInt_18F87J10.h"
#include "Font6x8.h"
#include "DrvLoad.h"
#include "DrvGain.h"
#include "DrvKey.h"
#include "DrvTimer_18F87J10.h"
#include "Adc_18F87J10.h"
#include "DrvCca.h"
#include "Pri_BD2_2880.h"
#include "DrvMMC.h"
#include "MMCdriver.h"
#include "MMCffs.h"
#include "MMCmem.h"

#include "SysGraphic.h"


extern int _user_putc( char c );

// The last 4 bytes of flash should always be programmed IMMEDIATELY after
// erasure of the last 1K block of flash.  Use the configuration below
const UINT8 DefaultConfigBits[P18F87_FLASH_CONFIG_SIZE] = {  0x80,  //Debug Off, Stack Overflow On, WDT On
                                                             0xF4,  //No code protect
                                                             0x05,  //Clock select by FOSC1:FOSC0, HS Clock
                                                             0xFF,  //WDT = 1:128
                                                             0xB0,  //Unused
                                                             0xF3,  //CCP2 is multiplexed with RB3
                                                             0x60,  //Device ID
                                                             0x17}; //Device ID (Device ID 00010111)

const char BootLoaderText[] = {"BOOT LOADER"};
const char VersionText[] = {"VERSION 1.01"};
const char LoadingDataText[] = {"LOADING DATA"};
const char DataCardLoadingText[] = {"DATA CARD LOADING"};
   
void DisplayString(UINT8 row, UINT8 column, const char* string)
{
   DrvLcdSetCursorAt( row, column );
   while(*string != '\0')
      _user_putc(*string++);
}

UINT8    CodeBuf[P18F87_FLASH_ROW_SIZE + 2];
UINT8    ConfigBuf[P18F87_FLASH_ROW_SIZE + 2];
UINT8	   TestState = 0;
/****************************************************************************

   This function performs the bootloader portion of the calibration which is
   application programming.

   THIS BOOTLOADER WILL ACCEPT BINARY FILES ONLY!

   Command Format:
     Sent to this program:  [COMMAND]
     Standard response is to echo the send data stream and append a
     0 for success or a 1 for failure.

   COMMAND  FUNCTION          DATA FROM HOST          DATA FROM TOOL
      1    Erase Flash   Start Address:[high][low]          0
      2    Program and   Data:64bytes*,CS:1byte CS:1byte    **
             Verify Flash
      3    Load Flash       Address:[high][low]             None
             Addresses
      4     Reset uP                None                    None

   Address is auto incremented.
   All values are echoed except 64 bytes of data.

   * Data is not echoed.
   ** After echoing the received checksum, the calculated checksum is transmitted.


   Write Example:
   From host: [0x03][address high][address low][0x02][64 bytes of data][cs]
   From tool: [0x03][address high][address low][0x02][cs][cs]
   or
   From host: [0x02][64 bytes of data][cs]
   From tool: [0x02][cs][cs]

   Erase Example:
   From host: [0x03][end address high][end address low][0x01][start  address high][start address low]
   From tool: [0x03][end address high][end address low][0x01][start  address high][start address low][0=success, 1=failure]

   To stream-line everything there are no interrupts, with one exception.  The
   low priority interrupt will be traped and used to cause this program to run.
   It is used by the loaded application to 'call' the bootloader.


   Parameters Passed:   None
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   02-22-06    JD          Developed
   08-28-06    DY          Modified for FBT50

****************************************************************************/
void BootLoad(UINT8 bCSum)
{
   UINT32      StartAddr;
   UINT32      LoadAddr;
   UINT32      Address;
   UINT8       Command;
   UINT8       HostCheckSum;
   UINT8       ToolCheckSum;
   UINT8       i;

   TestState = bCSum;
   while(1)                            //calibration task
   {
      CLRWDT();
      switch(TestState)
      {
         case BOOT_LOAD_INITIALIZE:
									            //recieve interupt disabled		
            DisplayString(3, 31, BootLoaderText);
            DisplayString(4, 28, VersionText);

            Command = RCREG;           //clear receive data
            Command = RCSTA;           //clear receive flags
            PIR1bits.RCIF = 0;
            TestState++;
            break;

         default:
            if(!PIR1bits.RCIF)         //set when register is not empty
            {
               break;                  //continue loop
            }
            Command = ReadCharacter(); //check if start command
            TransmitCharacter(Command);//echo command
            switch(Command)            //check command received
            {
               
               case 1:                 //Erase Flash Command
               /*
                  CLRWDT();
                  Address = 0;
                  for(i = 0; i < 2; i++)
                  {
                     Address <<= 8;
                     Address |= (UINT16)ReadCharacter();
                                       //echo address
                     TransmitCharacter((UINT8)Address);
                  }
                  StartAddr = (Address & P18F87_FLASH_LAST_SECTOR);
                  if(StartAddr >= LoadAddr)
                  {                    //Start must be on 64 byte boundary
                                       //End must be the end of a 64 byte boundary
                                       //End must be after start
                     CLRWDT();
                                       //send fail code
                     TransmitCharacter(FAIL);        
                  }
                  else
                  {                    //erase if address is above bootloader and 
                                       //on 1024 boundary
                     if((UINT32)StartAddr >= P18F87_FLASH_START_ADDRESS)
                     {
                        while(StartAddr < LoadAddr)
                        {
                           if(EraseFlash((UINT32)StartAddr) == FAIL)
                           {           //cannot erase
                              TransmitCharacter(FAIL);    
                              break;
                           }
                           if((UINT32)StartAddr == P18F87_FLASH_LAST_SECTOR)
                           {           //program config bits if last row
                              WriteFlash(P18F87_FLASH_LAST_ROW, ConfigBuf, PROGRAM_CONFIG_BITS);
                           }
                           StartAddr += P18F87_FLASH_SECTOR_SIZE;
                        }
                                       //send success code even if did nothing
                        TransmitCharacter(PASS);    
                     }
                     else
                     {                 //send fail code for bad start address
                        TransmitCharacter(FAIL);    
                     }
                     CLRWDT();
                  }
                  */
                  break;

               case 2:                 //Program and Verify       
                  ToolCheckSum = 0;
                  for(i = 0; i < P18F87_FLASH_ROW_SIZE; i++)      
                  {                    //Note 64 is a Mapple limitation
                     ToolCheckSum += CodeBuf[i] = ReadCharacter();
                  }
                                       //Now get CS
                  HostCheckSum = ReadCharacter();
                                       //echo host checksum
                  TransmitCharacter(HostCheckSum);    

                  if((UINT32)LoadAddr < P18F87_FLASH_START_ADDRESS ||
                     (UINT32)LoadAddr > (P18F87_FLASH_END_ADDRESS - (P18F87_FLASH_ROW_SIZE - 1)))
                  {                    //force bad ACK to host
                     ToolCheckSum++;   //= ~HostCheckSum;
                                       //cannot erase or program (out of range)
                     TransmitCharacter(ToolCheckSum);
                     break;
                  }
                                       //Make sure this goes out before flashing
                  while(TXSTA1bits.TRMT == 0)
                  {
                     CLRWDT();
                  }
                                       //Write data to flash if within range and checksum is correct
                  if(ToolCheckSum == HostCheckSum)
                  {                    //program the row and config bits if necessary
                     if(WriteFlash((UINT32)LoadAddr, CodeBuf, PROGRAM_ALL) == FAIL)
                     {                 //force bad ACK to host
                        ToolCheckSum = ~HostCheckSum; 
                     }
                     else
                     {                 //get ready for next block
                        LoadAddr += P18F87_FLASH_ROW_SIZE;
                     }
                  }
                                       //echo tool checksum
                  TransmitCharacter(ToolCheckSum);    
                  DrvLcdSetCursorAt( 6, 60 );
                  break;

               case 3:                 //Get the 'load' address
                  Address = 0;
                  for(i = 0; i < 2; i++)
                  {
                     Address <<= 8;
                     Address |= (UINT32)ReadCharacter();
                                       //echo address
                     TransmitCharacter((UINT8)Address);
                  }
                  DisplayString(5, 28, LoadingDataText);
                  LoadAddr = Address;
                  break;

               case 4:                 
                  _asm RESET _endasm   //reboot
                  break;

               case 0xEE:              //Note:This command is not part of the CAL protocol
                  break;

               case 0xF8:              //Note:This command is not part of the CAL protocol
                  break;
            }
      }
   }
}

/****************************************************************************

   This function erases the flash in a 1024 byte row.

   Parameters Passed:   RowAddress - Starting address (bits 9:0 are ignored)
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   08-28-06    DY          Developed

****************************************************************************/
UINT8 EraseFlash(UINT32 RowAddress)
{
   UINT8    retries;
   UINT8    Result;
   UINT16   i;

   if(RowAddress > P18F87_FLASH_END_ADDRESS)
   {
      return(FAIL);
   }

   retries = 3;
   Result = FAIL;
   while(retries > 0 && Result == FAIL)
   {
      retries--;
      Result = PASS;
      CLRWDT();
                                       //top 8 bits of address
      TBLPTRU = (UINT8)(RowAddress >> 16);
                                       //middle 8 bits of address
      TBLPTRH = (UINT8)(RowAddress >> 8); 
      TBLPTRL = 0x00;                  //not important
      EECON1bits.WREN = 1;             //Enable write operation
      EECON1bits.FREE = 1;             //Enable row erase
      EECON2 = 0x55;                   //required sequence
      EECON2 = 0xAA;                   //   "       "
      EECON1bits.WR = 1;               //start erase operation
      MDX_DELAY_125NS();
      CLRWDT();
      EECON1bits.WREN = 0;
                                       //VERIFY ERASE
                                       //Load start address of program area aligned to 1024 boundary
      TBLPTRU = (UINT8)(RowAddress >> 16);
	   TBLPTRH = (UINT8)((RowAddress >> 8) & 0xFC);
	   TBLPTRL = 0;
                                       //loop 1024 times
      for(i = 0; i < P18F87_FLASH_SECTOR_SIZE; i++)
      {                                //transfer data into TABLAT
   	   _asm
            TBLRDPOSTINC                
         _endasm
         if(TABLAT != 0xFF)            //erased?
         {
            Result = FAIL;             //report failure!
            break;
         }
      }
   }
   return(Result);
}

/****************************************************************************

   This function programs 64 bytes of flash data.

   Parameters Passed:   RowAddress - Starting address of 64 bytes
                        *dataptr - points to first of 64 bytes
                        Mode = PROGRAM_ALL
                                 Programs row and replaces last 8 bytes with
                                 config bits if last low.
                               PROGRAM_CONFIG_BITS
                                 Only programs if last row and fills buffer
                                 with 0xFF's and config bits.
   Parameters Returned: PASS is verified and FAIL if error

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   09-07-06    DY          Developed

****************************************************************************/
UINT8 WriteFlash(UINT32 RowAddress, UINT8* Buffer, UINT8 Mode)
{
	UINT8    i;

   if((RowAddress % P18F87_FLASH_SECTOR_SIZE) == 0)
      EraseFlash(RowAddress);          //erase
                                       //row with config bits?
   if(RowAddress == P18F87_FLASH_LAST_ROW)    
   {
      if(Mode == PROGRAM_CONFIG_BITS)  //fill with FF's?
      {
         for(i = 0; i < (P18F87_FLASH_ROW_SIZE - P18F87_FLASH_CONFIG_SIZE); i++)
         {
            *(Buffer + i) = 0xFF;      //fill all but last 8 with 0xFF
         }
      }
      for(i = 0; i < P18F87_FLASH_CONFIG_SIZE; i++)
      {                                //load config bits
         *(Buffer + i + (P18F87_FLASH_ROW_SIZE - P18F87_FLASH_CONFIG_SIZE)) = DefaultConfigBits[i];
      }
   }
   else
   {
      if(Mode == PROGRAM_CONFIG_BITS)
      {
         return(FAIL);                 //not last row so cannot do config bits
      }
   }

   RowAddress--;
   
   TBLPTRU = (UINT8)(RowAddress >> 16);//Load start address of program area
	TBLPTRH = (UINT8)(RowAddress >> 8);
	TBLPTRL = (UINT8)(RowAddress);
                                       //loop P18F87_FLASH_ROW_SIZE times
   for(i = 0; i < P18F87_FLASH_ROW_SIZE; i++) 
   {
      TABLAT = *(Buffer + i);          //load data
         
   	_asm
         TBLWTPREINC
      _endasm
   }

   EECON1bits.WREN = 1;                //Enable write operation
   EECON1bits.FREE = 0;                //Disable row erase
   EECON2 = 0x55;                      //required sequence
   EECON2 = 0xAA;                      //   "       "
   EECON1bits.WR = 1;                  //start erase operation
   MDX_DELAY_125NS();

   EECON1bits.WREN = 0;                //Disable write operation

   //VERIFY PROGRAMMING

   TBLPTRU = (UINT8)(RowAddress >> 16);// Load start address of program area
	TBLPTRH = (UINT8)(RowAddress >> 8);
	TBLPTRL = (UINT8)(RowAddress);
                                       //loop P18F87_FLASH_ROW_SIZE times
   for(i = 0; i < P18F87_FLASH_ROW_SIZE; i++) 
   {								            //transfer data into TABLAT
      _asm 
         TBLRDPREINC
	   _endasm                          

      if(TABLAT != *(Buffer + i))      //same data as programmed?
      {                                //cannot verify if config bits so quit with
                                       //PASS if last 8 bytes
         if(i == (P18F87_FLASH_ROW_SIZE - P18F87_FLASH_CONFIG_SIZE) && 
            RowAddress == P18F87_FLASH_LAST_ROW)
         {
            break;
         }
         return(FAIL);                 //report failure
      }
   }

   return(PASS);
}

/****************************************************************************

   This function reads a character from the serial port.

   Parameters Passed:   None
   Parameters Returned: serial data

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   02-22-06    JD          Developed

****************************************************************************/
UINT8 ReadCharacter(void)
{
   while(!PIR1bits.RCIF)               //set when register is not empty
   {
      CLRWDT();                        //reset the internal software watchdog
   }
   return RCREG1;
}

/****************************************************************************

   This function sends a character out the serial port.

   Parameters Passed:   data
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   02-22-06    JD          Developed

****************************************************************************/
void TransmitCharacter(UINT8 data)
{
   while(!TXSTA1bits.TRMT)             //TRMT1 is set when TSR is empty
   {
      CLRWDT();                        //reset the internal software watchdog
   }
   TXREG = data;                       //load the register
   CLRWDT();                           //reset the internal software watchdog
}


UINT32 AsciiToBinary(char *pData, UINT8 size)
{
   UINT32   Data = 0;
   UINT8    Byte, i;

   for(i = 0; i < size; i++)
   {
      Data <<= 4;
      Byte = (UINT8)*pData++ - '0';
      if(Byte > 9)
         Byte -= 7;
      Data |= (UINT32)Byte;
   }
   return(Data);
}

void VerifyError(void)
{                        
   DrvLcdCls();
   DisplayString(4, 19, DataCardErrorText);
   while(1)
      ;
}

char  DataBuffer[64];
void UploadFile(MMC_FILE* pFile, UINT8 Memory)
{
   UINT8       count = 0;
   UINT8       Sector;
   char*       pStart;
   char*       pEnd;
   const rom void* pData;
   UINT32      Address;
   UINT32      BaseAddress;
   UINT32      SectorErasedReg = 0;
   char        FileBuffer[64];

   DisplayString(3, 16, DataCardLoadingText);
   DisplayString(4, 28, VersionText);

   while(pFile->CurrentByteWithinFile < pFile->FileSize)
   {
      memset(FileBuffer, 0x00, sizeof(FileBuffer));
                                       //read line
      MMCFileGetString(FileBuffer, sizeof(FileBuffer), pFile);                                          
                                       //find line start and line end
      pStart = strstrrampgm(FileBuffer, "S");  
      pEnd = strstrrampgm(FileBuffer, "\r\n") - 2;
      if(pStart && pEnd)
      {
         switch(*(pStart + 1))
         {
            case '2':
               pStart += 4;                     //get base address
               Address = AsciiToBinary(pStart, 6);
               switch(Memory)
               {
                  case INTERNAL_FLASH:
                     BaseAddress = Address & 0x00FFFFC0;
                     pData = (const rom void*)BaseAddress;
                     memcpypgm2ram((void*)DataBuffer, pData, P18F87_FLASH_ROW_SIZE);
                     break;
                     
                  case EXTERNAL_EEPROM:
                  case EXTERNAL_FLASH:
                     BaseAddress = Address;
                     break;
                     
                     default:
                        ;
               }
               pStart += 6;            //move to data start            
               for(count = Address - BaseAddress; pStart < pEnd; count++)
               {
                  DataBuffer[count] =  AsciiToBinary(pStart, 2);
                  pStart += 2;
               }
               SysGraphicBar( 5, 14, 100, 
                             (pFile->CurrentByteWithinFile * 100) / pFile->FileSize );
               switch(Memory)
               {
                  case INTERNAL_FLASH:
                                       //write and verify
                     if(WriteFlash(BaseAddress, (UINT8*)DataBuffer, PROGRAM_ALL) == FAIL)
                     {
                        VerifyError();
                     }   
                     break;

                  case EXTERNAL_EEPROM:
                                       //write and verify
                     if(DrvEepromWriteAndVerify((UINT16)Address, (UINT8*)DataBuffer, count ) == FAIL)
                     {
                        VerifyError();
                     }   
                     break;
                     
                  case EXTERNAL_FLASH:
                                       //get sector
                     Sector = FLASH_ADDRESS_TO_SECTOR( Address );
                                       //check if sector erased
                     if((SectorErasedReg & ((UINT32)0x00000001 << Sector)) == 0)
                     {                 //not erased yet so erase
                        DrvFlashSectorErase( Sector );
                                       //mark as erased
                        SectorErasedReg |= ((UINT32)0x00000001 << Sector);
                     }
                                       //write and verify
                     if(DrvFlashPageWrite((UINT24)Address, (UINT8*)DataBuffer, count ) == FAIL)
                     {
                        VerifyError();
                     }   
                     break;
                     
                  default:
                     ;
               }
               break;
              
            default:
               ;
         }
      }
      else
         break;
   }
   MMCFileClose(pFile);
}

      