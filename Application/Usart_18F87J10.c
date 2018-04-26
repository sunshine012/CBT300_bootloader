////////////////////////////////////////////////////////////////////////////////
//
// Usart.c
//
////////////////////////////////////////////////////////////////////////////////

//
// Required include files.
//

#include "p18f87J10.h"

#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "Usart_18F87J10.h"



////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

BYTE     *Usart1Buffer;
UINT8    Usart1BufferSize;
UINT16   Usart1WriteIndex;
UINT16   Usart1ReadIndex;

BYTE     *Usart2Buffer;
UINT8    Usart2BufferSize;
UINT16   Usart2WriteIndex;
UINT16   Usart2ReadIndex;

////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Usart1Isr.
//

void Usart1Isr( void )
{
   Usart1Buffer[ Usart1WriteIndex ] = RCREG1;
   
   Usart1WriteIndex++;
   if( Usart1WriteIndex = Usart1BufferSize )
   {
      Usart1WriteIndex = 0;
   }    
}


////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// UsartInit1.
//

_Bool	DrvUsart1Init( UINT8 Channel, BYTE *Buffer  )
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
   RCSTA1bits.SPEN      = USART_PORT_ENEBLE;

   // BAUDCON1: Baud rate control register
   BAUDCON1bits.WUE     = USART_RX_MONITOR_DISABLE;
   BAUDCON1bits.BRG16   = USART_8_BIT_BRG;

	
	// SPBRG1: Baud Rate Generator
   // The formula to be used is:
   //    b = Fosc / (16 * (n + 1)) thus
   //    n = (Fosc / (16 * b)) - 1
   // Required baud rate is 57600, this gives the following n:
   //    n = (32000000 / (16 * 57600)) - 1 = 33.7
   // Define n as 34 gives the following baud rate:
   //    b = 32000000 / (16 * (34 + 1)) = 57142
   // The baud rate error is:
   //    e = (57600 - 57142) / 57600 = 0.80% 
   SPBRG1               = 34;

   // Initialize buffer.
   Usart1Buffer         = Buffer;
   Usart1WriteIndex     = 0;
   Usart1ReadIndex      = 0;
}

//
// UsartInit2.
//

_Bool DrvUsart2Init( UINT8 Channel, BYTE *Buffer  )
{
   // I/O pin directions.
   USART2_TX_TRIS       = TRIS_BIT_OUTPUT;
   USART2_RX_TRIS       = TRIS_BIT_INPUT;

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
   RCSTA2bits.SPEN      = USART_PORT_ENEBLE;

   // BAUDCON2: Baud rate control register
   BAUDCON2bits.WUE     = USART_RX_MONITOR_DISABLE;
   BAUDCON2bits.BRG16   = USART_8_BIT_BRG;
	
	// SPBRG2: Baud Rate Generator
   // The formula to be used is:
   //    b = Fosc / (16 * (n + 1)) thus
   //    n = (Fosc / (16 * b)) - 1
   // Required baud rate is 9600, this gives the following n:
   //    n = (32000000 / (16 * 9600)) - 1 = 207.3
   // Define n as 207 gives the following baud rate:
   //    b = 32000000 / (16 * (207 + 1)) = 9615
   // The baud rate error is:
   //    e = (9600 - 9615) / 9600 = 0.16% 
   //SPBRG2 = 207;
	
   // SPBRG2: Baud Rate Generator
   // The formula to be used is:
   //    b = Fosc / (16 * (n + 1)) thus
   //    n = (Fosc / (16 * b)) - 1
   // Required baud rate is 19200, this gives the following n:
   //    n = (32000000 / (16 * 19200)) - 1 = 103.2
   // Define n as 104 gives the following baud rate:
   //    b = 32000000 / (16 * (103 + 1)) = 19230
   // The baud rate error is:
   //    e = (19230 - 19200) / 19200 = 0.16% 
   SPBRG2 = 103;

   // Initialize buffer.
   Usart2Buffer      = Buffer;
   Usart2WriteIndex  = 0;
   Usart2ReadIndex   = 0;
}

//
//
//

void	DrvUsart1TransmitChar( UINT8 Channel, BYTE Data );

//
// Usart1ByteReady.
//

_Bool  DrvUsart1ByteReady( UINT8 Channel )
{
   if( Usart1ReadIndex != Usart1WriteIndex )
   {
      return( BOOL_TRUE );
   }
   else
   {
      return( BOOL_FALSE );
   }
}

//
// Usart1ReadByte.
//

BYTE  DrvUsart1ReadByte( UINT8 Channel )
{
   BYTE  Data;

   Data = Usart1Buffer[ Usart1ReadIndex ];

   Usart1ReadIndex++;
   if( Usart1ReadIndex = Usart1BufferSize )
   {
      Usart1ReadIndex = 0;
   }

   return( Data );
}

