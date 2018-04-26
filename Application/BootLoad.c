/****************************************************************************
;
;  Copyright (c) Midtronics 2006
;
;     This module defines the calibrate routine(s).
;
****************************************************************************/
#include "DrvPic18f67J10.h"
#include <stdio.h>
#include <string.h>

#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "BootLoad.h"

//#include "DrvSpi.h"
//#include "DrvSound.h"
//#include "DrvRtc_M41T94.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvSsp_18F67J10.h"
#include "DrvUsart_18F67J10.h"
#include "DrvInt_18F67J10.h"
#include "DrvEeprom_25AA320.h"
#include "Font6x8.h"
#include "DrvLoad.h"
//#include "DrvGain.h"
#include "DrvKey.h"
#include "DrvTimer_18F67J10.h"

#include "AppData.h"
#include "SysDisplay.h"

//extern int _user_putc( char c );

const rom char BootLoaderText[] = {"BOOT LOADER"};
const rom char VersionText[] = {"VERSION"};
const rom char VersionNumberText[] = {"192-160002-E"};
const rom char LoadingDataText[] = {"LOADING DATA"};
//const rom char UpdatingSoftwareText[] = {"UPDATING SOFTWARE"};
//const rom char PleaseWaitText[] = {"PLEASE WAIT..."};
/*const rom char LoadingDataTypeText[3][17] = {
                                             "LOADING FIRMWARE",
                                             " LOADING  FLASH ",
                                             "LOADING  EE PROM"
                                            };
const rom char DataCardErrorText[5][19] = {
                                           "DATA CARD ERROR",     //header
                                           " INCORRECT FORMAT ",  //error 1
                                           "  DATA CARD FULL  ",  //error 2
                                           "S RECORD INCORRECT",  //error 3
                                           " FILE READ ERROR  "   //error 4
                                          };*/
   
UINT8    CodeBuf[P18F87_FLASH_ROW_SIZE + 2];
UINT8    MXTUpdateTestState = 0;
UINT8    DisplayBuffer[21];

void DisplayRomString(UINT8 row, const rom char* string)
{
   strcpypgm2ram((char *)DisplayBuffer, string);
   DisplayString_S(DisplayBuffer, row, DISPLAY_C);
}


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
void BootLoad(void)
{
   UINT32      StartAddr;
   UINT32      LoadAddr;
   UINT32      Address;
   UINT8       Command;
   UINT8       HostCheckSum;
   UINT8       ToolCheckSum;
   UINT8       i;

   MXTUpdateTestState = 0;
   while(1)                            //calibration task
   {
      CLRWDT();
      switch(MXTUpdateTestState)
      {
         case BOOT_LOAD_INITIALIZE:
            Clear_Screen();
            DisplayRomString(1, BootLoaderText);
            DisplayRomString(2, VersionText);
            DisplayRomString(3, VersionNumberText);

            Command = RCREG;           //clear receive data
            Command = RCSTA;           //clear receive flags
            PIR1bits.RCIF = 0;
            MXTUpdateTestState++;
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
                                       //The write routine takes care of erasing the flash
                  break;               //sector

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
                                       //echo tool checksum
                  TransmitCharacter(ToolCheckSum);    
                  break;

               case 3:                 //Get the 'load' address
                  Address = 0;
                  for(i = 0; i < 3; i++)
                  {
                     Address <<= 8;
                     Address |= (UINT32)ReadCharacter();
                                       //echo address
                     TransmitCharacter((UINT8)Address);
                  }
                  DisplayRomString(3, LoadingDataText);
                  LoadAddr = Address;
                                       //erase address sector
                  EraseFlash(Address & (UINT32)P18F87_FLASH_LAST_ROW);
                  break;

               case 4:                 
                  _asm RESET _endasm   //reboot
                  break;

               case 5:                 //Note:This command is not part of the CAL protocol
                  i = 0;
                  do{
                     TransmitCharacter(VersionNumberText[i]);
                  }while(VersionNumberText[i++] != 0);
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

//char  DataBuffer[64];
/*void UploadFile(FFS_FILE* pFile, UINT8 Memory)
{
   UINT8       count, i, offset;
   UINT8       Sector;
   char*       pStart;
   char*       pEnd;
   const rom void* pData;
   UINT32      Address;
   UINT32      BaseAddress;
   UINT32      SectorErasedReg = 0;
   char        FileBuffer[64];

   DisplayRomString(1, 13, UpdatingSoftwareText);
   DisplayRomString(2, 22, PleaseWaitText);
   DisplayRomString(5, 16, LoadingDataTypeText[Memory]);
   while(pFile->current_byte_within_file < pFile->file_size)
   {
      if(MMC_IS_NOT_INSERTED())
         VerifyError(FILE_READ_ERROR);
         
      memset(FileBuffer, 0x00, sizeof(FileBuffer));
                                       //read line
      ffs_fgets(FileBuffer, sizeof(FileBuffer), pFile);                                          
                                       //find line start and line end
      pStart = strstrrampgm(FileBuffer, "S");  
      pEnd = strstrrampgm(FileBuffer, "\r\n") - 2;
      if(pStart && pEnd)
      {
         switch(*(pStart + 1))
         {
            case '0':                  //S0, header record
            case '8':                  //S8, terminator for S2 records
               break;
               
            case '2':                  //S2 records
               pStart += 4;            //get base address
               Address = AsciiToBinary(pStart, 6);
               pStart += 6;            //move to data start            
               count = (pEnd - pStart) >> 1;
               switch(Memory)
               {
                  case INTERNAL_FLASH:
                                       //set the base address of sector
                     BaseAddress = Address & (UINT32)P18F87_FLASH_LAST_ROW;
                                       //read current data back into buffer
                     pData = (const rom void*)BaseAddress;
                     memcpypgm2ram((void*)DataBuffer, pData, P18F87_FLASH_ROW_SIZE);
                                       //check if all data fits in sector
                     if((Address + count) > (BaseAddress + P18F87_FLASH_ROW_SIZE))
                     {                 //no limit write size to what fits in sector
                        count = P18F87_FLASH_ROW_SIZE - (Address - BaseAddress);
                     }
                     offset = (Address & (P18F87_FLASH_ROW_SIZE - 1));
                     for(i = 0; i < count; i++)
                     {                 //copy data which fits into current sector into 
                                       //buffer
                        DataBuffer[offset + i] = AsciiToBinary(pStart, 2);
                        pStart += 2;
                     }
                     break;
                     
                  case EXTERNAL_EEPROM:
                     for(i = 0; i < count; i++)
                     {                 //copy data into buffer
                        DataBuffer[i] = AsciiToBinary(pStart, 2);
                        pStart += 2;
                     }
                     break;

                  case EXTERNAL_FLASH:
                                       //set the base address of sector
                     /*BaseAddress = Address & 0x00FF0000; 
                                       //check if all data fits in sector
                     if((Address + count) > (BaseAddress + FLASH_SECTOR_SIZE))
                     {                 //no limit write size to what fits in sector
                        count = FLASH_SECTOR_SIZE - (Address - BaseAddress);
                     }
                     for(i = 0; i < count; i++)
                     {                 //copy data which fits into current sector into 
                                       //buffer
                        DataBuffer[i] = AsciiToBinary(pStart, 2);
                        pStart += 2;
                     }
                     break;
                     
                  default:
                     ;
               }
               SysGraphicBar( 6, 14, 100, 
                             (pFile->current_byte_within_file * 100) / pFile->file_size );
               switch(Memory)
               {
                  case INTERNAL_FLASH:
                                       //write and verify data to current sector
                     if(WriteFlash(BaseAddress, (UINT8*)DataBuffer, PROGRAM_ALL) == FAIL)
                     {
                        VerifyError(FILE_READ_ERROR);
                     }   
                     if(pStart != pEnd)//check if all data written
                     {                 //no, data crosses sectors,
                                       //set new base address of next sector
                        BaseAddress += P18F87_FLASH_ROW_SIZE;
                                       //read current data back into buffer
                        pData = (const rom void*)BaseAddress;
                        memcpypgm2ram((void*)DataBuffer, pData, P18F87_FLASH_ROW_SIZE);
                                       //set count of remaining data for next sector
                        count = (pEnd - pStart) >> 1;
                        for(i = 0; i < count; i++)
                        {              //copy data which fits into current sector into 
                                       //buffer
                           DataBuffer[i] = AsciiToBinary(pStart, 2);
                           pStart += 2;
                        }
                                       //write and verify data to current sector
                        if(WriteFlash(BaseAddress, (UINT8*)DataBuffer, PROGRAM_ALL) == FAIL)
                        {
                           VerifyError(FILE_READ_ERROR);
                        }   
                     }   
                     break;

                  case EXTERNAL_EEPROM:
                                       //write and verify
                     if(DrvEepromWriteAndVerify((UINT16)Address, (UINT8*)DataBuffer, count ) == FAIL)
                     {
                        VerifyError(FILE_READ_ERROR);
                     }  
                     break;
                     
                  case EXTERNAL_FLASH:
                                       //get sector
                     /*Sector = FLASH_ADDRESS_TO_SECTOR( Address );
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
                        VerifyError(FILE_READ_ERROR);
                     }   
                     if(pStart != pEnd)//check if all data written
                     {                 //data crosses sectors
                        Sector++;      //no, set new base address of next sector
                                       //check if erased already
                        if((SectorErasedReg & ((UINT32)0x00000001 << Sector)) == 0)
                        {              //not erased yet so erase
                           DrvFlashSectorErase( Sector );
                                       //mark as erased
                           SectorErasedReg |= ((UINT32)0x00000001 << Sector);
                        }
                                       //set count of remaining data for next sector
                        count = (pEnd - pStart) >> 1;
                        for(i = 0; i < count; i++)
                        {              //copy data which fits into current sector into 
                                       //buffer
                           DataBuffer[i] = AsciiToBinary(pStart, 2);
                           pStart += 2;
                        }
                                       //write and verify
                        if(DrvFlashPageWrite((UINT24)Address, (UINT8*)DataBuffer, count ) == FAIL)
                        {
                           VerifyError(FILE_READ_ERROR);
                        }   
                     }
                     break;
                     
                  default:
                     ;
               }
               break;
              
            default:                   //S1, S3, S5, S7 and S9 records             
               VerifyError(SRECORD_TYPE_ERROR);
         }
      }
      else
         break;
   }
   ffs_fclose(pFile);                //close file
}*/

      
