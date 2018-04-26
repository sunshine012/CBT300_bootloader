#include <stdlib.h>
#include <string.h>
#include "DrvPic18f67J10.h"

#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "DrvUsart_18F67J10.h"
#include "bootload.h"

typedef void (*far pFVoidVoid)(void);      
typedef UINT8 (*far pFByteByte)(UINT8 data);

/***
 ** Check sum Code
 **/

// Boot loader gets 0-7FFFh, The application program gets 8000-1FBFD, 97277 bytes. 
// By using the PICC-18 Linker 'Specify Offset In ROM' command the entire
// application image is shifted.  If this value is specified as 8000
// the application will load at 8000h.  The first instruction is always
// a GOTO XXXX, which is a 2 word instruction.  Then there is (unless modified)
// nothing until 8008. At 8008 is the 'High Priority' interrupt vector.
// So - we will use the area between 8004 and 8008.
// At 8006 we will look for the last address to checksum.  If this value
// is 0xFFFF, the summer will go to 0x1FBFD (which will take longer).
// 8002-8006 can be used by the program to insert the check-sum, but the
// operation of this program does not change.
UINT8 ChkSumCode(void)
{
   UINT16      ChkSum;
   UINT16      RdChkSum;
                                       //Address
   TBLPTRU = (UINT8)(P18F87_FLASH_START_ADDRESS >> 16);                        
   TBLPTRH = (UINT8)(P18F87_FLASH_START_ADDRESS >> 8);		               
   TBLPTRL = (UINT8)(P18F87_FLASH_START_ADDRESS);
                        
   do                                  //Check if GOTO or BRA opcode in Resetvector
   {
      _asm 
         TBLRDPOSTINC                
         TBLRDPOSTINC                
      _endasm   
      if((TABLAT == 0xEF) || ((TABLAT & 0xF8) == 0xD0))
      {
         TBLPTRL = 0;
      }
   }while((TBLPTRL != 0) && (TBLPTRL < 8));

   if(TBLPTRL != 0) 
   {
      //DrvUsartSendByte(USART_PORT_1, 0xAA);
      return(0);                       //not programmed at all return error
   }
	   
   ChkSum = 0;                         //Start back at the beginning
   do
   {
      _asm                             //Read the program address into TABLAT (auto increment)
         TBLRDPOSTINC
      _endasm
	   ChkSum += TABLAT;		            //Put current address into checksum.
   }while((TBLPTRU < (UINT8)(P18F87_FLASH_CHECKSUM_ADDRESS >> 16) || 
           TBLPTRH < (UINT8)(P18F87_FLASH_CHECKSUM_ADDRESS >> 8)) || 
          (TBLPTRL < (UINT8)P18F87_FLASH_CHECKSUM_ADDRESS));

   _asm
      TBLRDPOSTINC
   _endasm

   RdChkSum = TABLAT;
   RdChkSum <<= 8;
   
   _asm
      TBLRD
   _endasm

   RdChkSum |= TABLAT;
   
   //DrvUsartSendByte(USART_PORT_1, (ChkSum & 0xFF));
   //DrvUsartSendByte(USART_PORT_1, (ChkSum >> 8) & 0xFF);

   //DrvUsartSendByte(USART_PORT_1, (RdChkSum & 0xFF));
   //DrvUsartSendByte(USART_PORT_1, (RdChkSum >> 8) & 0xFF);

   if(ChkSum != RdChkSum)
      return(1);                       //return check sum error
   else
      return(2);                       //return check sum valid
}
