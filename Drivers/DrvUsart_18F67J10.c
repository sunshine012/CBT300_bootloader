////////////////////////////////////////////////////////////////////////////////
//
// Usart.c
//
////////////////////////////////////////////////////////////////////////////////

//
// Required include files.
//
#include <stdlib.h>         
#include <string.h>
#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
//#include "DrvPan1026.h"
//#include "AppData.h"
#include "DrvTimer_18F67J10.h"
#include "DrvInt_18F67J10.h"
#include "DrvUsart_18F67J10.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

UINT8    *Usart1Buffer;
UINT8    Usart1BufferSize;
UINT16   Usart1WriteIndex;
UINT16   Usart1ReadIndex;
UINT8    Usart1Status;

UINT8    *Usart2Buffer;
UINT8    Usart2BufferSize;
UINT16   Usart2WriteIndex;
UINT16   Usart2ReadIndex;
UINT8    Usart2Status;

////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// UsartInit1.
//

void Usart1Init( UINT16 BaudRate, UINT8 *Buffer, UINT8 BufferSize )
{
   // I/O pin directions.
   USART1_TX_TRIS       = TRIS_BIT_OUTPUT;
   USART1_RX_TRIS       = TRIS_BIT_INPUT;
   
   // TXSTA1: Transmit status and control register.
   TXSTA1bits.BRGH      = USART_HIGH_SPEED;
   TXSTA1bits.SENDB     = USART_BREAK_COMPLETE;
   TXSTA1bits.SYNC      = USART_ASYNCHRONOUS_MODE;
   TXSTA1bits.TXEN      = USART_TRANSMIT_ENABLE;
   TXSTA1bits.TX9       = USART_8_BIT_TRANSMISSION;
   TXSTA1bits.CSRC      = USART_ASYNCHRONOUS_MODE;

   // RCSTA1: Receive status and control register.
   RCSTA1bits.CREN      = USART_ENABLE_RECEIVER;
   RCSTA1bits.RX9       = USART_8_BIT_RECEPTION;
   RCSTA1bits.SPEN      = USART_PORT_ENABLE;

   // BAUDCON1: Baud rate control register
   BAUDCON1bits.WUE     = USART_RX_MONITOR_DISABLE;
   BAUDCON1bits.BRG16   = USART_16_BIT_BRG;

	// SPBRG1, SPBRGH1: Baud Rate Generator
   SPBRGH1              = (BaudRate >> 8) & 0x00FF;
   SPBRG1               = BaudRate & 0xFF;

   // Initialize buffer.
   Usart1Buffer         = Buffer;
   Usart1BufferSize     = BufferSize;

   // Reset buffer and status.
   DrvUsartReset( USART_PORT_1 );   

   // Enable the receive interrupt if a valid buffer has been specified.
   DrvIntEnable( INT_ID_USART_1_RX, (Buffer != 0) && (BufferSize > 0) );
}

//
// UsartInit2.
//

void Usart2Init( UINT16 BaudRate, UINT8 *Buffer, UINT8 BufferSize  )
{
   // I/O pin directions.
   USART2_TX_TRIS       = TRIS_BIT_OUTPUT;
   USART2_RX_TRIS       = TRIS_BIT_INPUT;
   USART2_TX_IO    	= 0;

   // TXSTA2: Transmit status and control register.
   TXSTA2bits.BRGH      = USART_HIGH_SPEED;
   TXSTA2bits.SENDB     = USART_BREAK_COMPLETE;
   TXSTA2bits.SYNC      = USART_ASYNCHRONOUS_MODE;
   TXSTA2bits.TXEN      = USART_TRANSMIT_ENABLE;
   TXSTA2bits.TX9       = USART_8_BIT_TRANSMISSION;
   TXSTA2bits.CSRC      = USART_ASYNCHRONOUS_MODE;

   // RCSTA2: Receive status and control register.
   RCSTA2bits.CREN      = USART_ENABLE_RECEIVER;
   RCSTA2bits.RX9       = USART_8_BIT_RECEPTION;
   RCSTA2bits.SPEN      = USART_PORT_ENABLE;

   // BAUDCON2: Baud rate control register
   BAUDCON2bits.WUE     = USART_RX_MONITOR_DISABLE;
   BAUDCON2bits.BRG16   = USART_16_BIT_BRG;
	
	// SPBRG2, SPBRGH2: Baud Rate Generator
   SPBRGH2              = (BaudRate >> 8) & 0x00FF;
   SPBRG2               = BaudRate & 0xFF;

   // Initialize buffer.
   Usart2Buffer         = Buffer;
   Usart2BufferSize     = BufferSize;
   
   // Reset buffer and status.
   DrvUsartReset( USART_PORT_2 );   

   // Enable the receive interrupt if a valid buffer has been specified.
   DrvIntEnable( INT_ID_USART_2_RX, (Buffer != 0) && (BufferSize > 0) );
   //DrvIntEnable( INT_ID_USART_2_RX, INT_ENABLE );
}

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

void DrvUsartInit( _UsartPort Port, UINT16 BaudRate, UINT8 *Buffer, UINT8 BufferSize  )
{
   if( Port == USART_PORT_1 )
   {
      Usart1Init( BaudRate, Buffer, BufferSize  );
   }
   else if( Port == USART_PORT_2 )
   {
      Usart2Init( BaudRate, Buffer, BufferSize  );
   }
}

void DrvUsartDisable( _UsartPort Port )
{
   switch( Port )
   {
      case USART_PORT_1:
         DrvIntEnable( INT_ID_USART_1_RX, FALSE );
         RCSTA1bits.SPEN = USART_PORT_DISABLE;
         USART1_TX_IO    = 0;
         break;
      case USART_PORT_2:
         DrvIntEnable( INT_ID_USART_2_RX, FALSE );
         RCSTA2bits.SPEN = USART_PORT_DISABLE;
         USART2_TX_IO    = 0;
         break;
      default:
         break;
   }
}
//
//
//

void DrvUsartReset( _UsartPort Port )
{
   if( Port == USART_PORT_1 )
   {
      Usart1WriteIndex     = 0;
      Usart1ReadIndex      = 0;
      Usart1Status         = USART_STATUS_NO_ERROR;
   }
   else if( Port == USART_PORT_2 )
   {
      Usart2WriteIndex     = 0;
      Usart2ReadIndex      = 0;
      Usart2Status         = USART_STATUS_NO_ERROR;
   }
}

//
//
//

void	DrvUsartSendByte( _UsartPort Port, UINT8 Data )
{
   if( Port == USART_PORT_1 )
   {
      // Wait for the TX register to be empty.
	   while( TXSTA1bits.TRMT == USART_TSR_FULL );

      // Load the TX data register.
	   TXREG1 = Data;
   
      // Wait until the byte has been shifted out.
	   while( TXSTA1bits.TRMT == USART_TSR_FULL );
   }
   else if( Port == USART_PORT_2 )
   {
      // Wait for the TX register to be empty.
	   while( TXSTA2bits.TRMT == USART_TSR_FULL );

      // Load the TX data register.
	   TXREG2 = Data;
   
      // Wait until the byte has been shifted out.
	   while( TXSTA2bits.TRMT == USART_TSR_FULL );
   }
}

//
//
//

void	DrvUsartSendData( _UsartPort Port, UINT8 *Data, UINT8 Count )
{
   while( Count-- )
   {
      DrvUsartSendByte( Port, *Data++ );
	  CLRWDT();  	  
   }
}

//
//
//
volatile UINT8 DrvUsart2GetStatus(void)
{
   UINT8 Status;

   Status = Usart2Status;
   Usart2Status = USART_STATUS_NO_ERROR;
   if(DrvTimer0CounterDone(TIMER0_MS_COUNTER_BT ))
   {
   		Status |= USART_STATUS_TIMEOUT;
   }
   else
   {
		Status &= ~USART_STATUS_TIMEOUT;
   }

   return(Status);
}
//
//
//
volatile UINT16 DrvUsart2Read( void* pBuffer, UINT8 MaxCounts)
{
   UINT8    Count = 0;
   UINT8    Char;

   while(Count < MaxCounts)      
   {                                   
      DrvUsartReadByte(USART_PORT_2, &Char); //read byte(s)
                                       //save byte in buffer
      *((UINT8*)pBuffer + Count++) = Char;     
   }
   return(Count);
}
//
//
//
volatile UINT16 DrvUsart2GetNumberOfBytesAvailable(void)
{
   UINT16   NumOfBytes;
   UINT16   WIndex;

   WIndex = Usart2WriteIndex;    //save because write gets incremented in interrupt routine
   if(WIndex > Usart2ReadIndex)
   {
      NumOfBytes = WIndex - Usart2ReadIndex;
   }
   else
   {
      NumOfBytes = Usart2BufferSize - Usart2ReadIndex;
      NumOfBytes += WIndex;
   }
   return((UINT16)NumOfBytes);
}
//
//
//
volatile UINT16 DrvUsart2GetMessageLength(void)
{
    return(Usart2Buffer[Usart2ReadIndex]);
}


//
//
//

_Bool DrvUsartByteReady( _UsartPort Port )
{
   _Bool Result;

   Result = FALSE;

   if( Port == USART_PORT_1 )
   {
      Result = (Usart1ReadIndex != Usart1WriteIndex);
   }
   else if( Port == USART_PORT_2 )
   {
      Result = (Usart2ReadIndex != Usart2WriteIndex);
   }

   return( Result );
}

//
//
//

_Bool DrvUsartReadByte( _UsartPort Port, UINT8 *Byte )
{
   _Bool Result;

   Result = FALSE;

   if( (Port == USART_PORT_1) && (Usart1ReadIndex != Usart1WriteIndex) )
   {
      *Byte = Usart1Buffer[ Usart1ReadIndex ];

      Usart1ReadIndex++;
      if( Usart1ReadIndex == Usart1BufferSize )
      {
         Usart1ReadIndex = 0;
      }

      Result = TRUE;
   }
  // Disable Usart2 for Receive Byte
   else if( (Port == USART_PORT_2) && (Usart2ReadIndex != Usart2WriteIndex) )
   {
      *Byte = Usart2Buffer[ Usart2ReadIndex ];

      Usart2ReadIndex++;
      if( Usart2ReadIndex == Usart2BufferSize )
      {
         Usart2ReadIndex = 0;
      }

      Result = TRUE;
   }
   return( Result );
}

//
//
//

UINT8  DrvUsartLastError( _UsartPort Port )
{
   if( Port == USART_PORT_1 )
   {
      return( Usart1Status );
   }
   else if( Port == USART_PORT_2 )
   {
      return( Usart2Status );
   }
}

//
// DrvUsart1Isr.
//

void DrvUsart1Isr( void )
{
	UINT8 temp;
   if( RCSTA1bits.FERR )
   {
      Usart1Status |= USART_STATUS_FRAME_ERROR;
   }
   if( RCSTA1bits.OERR )
   {
      Usart1Status     |= USART_STATUS_OVERRUN_ERROR;
      RCSTA1bits.CREN   = USART_DISABLE_RECEIVER;
      RCSTA1bits.CREN   = USART_ENABLE_RECEIVER;
   }

   Usart1Buffer[ Usart1WriteIndex ] = RCREG1;
   Usart1WriteIndex++;

   if( Usart1WriteIndex == Usart1BufferSize )
   {
      Usart1WriteIndex = 0;
   }    

   if( Usart1WriteIndex == Usart1ReadIndex )
   {
      Usart1Status |= USART_STATUS_BUFFER_ERROR;
   }
}

//
// DrvUsart2Isr.
//

void DrvUsart2Isr( void )
{
   if( RCSTA2bits.FERR )
   {
      Usart2Status |= USART_STATUS_FRAME_ERROR;
   }
   if( RCSTA2bits.OERR )
   {
      Usart2Status     |= USART_STATUS_OVERRUN_ERROR;
      RCSTA2bits.CREN   = USART_DISABLE_RECEIVER;
      RCSTA2bits.CREN   = USART_ENABLE_RECEIVER;
   }
	//Bluetooth for handle Event 
    Usart2Buffer[ Usart2WriteIndex ] = RCREG2;
    DrvTimer0Reset();
    DrvTimer0SetCounter( TIMER0_MS_COUNTER_BT, 6);  //10ms
    Usart2WriteIndex++;
   
   if( Usart2WriteIndex == Usart2BufferSize )
   {
      		Usart2WriteIndex = 0;
   }    

   if( Usart2WriteIndex == Usart2ReadIndex )
   {
       Usart2Status |= USART_STATUS_BUFFER_ERROR;	  
   }
   

}

