////////////////////////////////////////////////////////////////////////////////
//
// DrvUsart_18F87J10.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_USART_18F67J10_H_
#define _DRV_USART_18F67J10_H_

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

typedef enum
{
   USART_PORT_1   = 0,
   USART_PORT_2   = 1
} _UsartPort, *_UsartPortPtr;

////////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
////////////////////////////////////////////////////////////////////////////////

//
// I/O line definitions.
//

// I/O lines.
#define USART1_TX_IO       MDX_TX1_IO
#define USART1_RX_IO       MDX_RX1_IO
#define USART2_TX_IO       MDX_BT_TXD_IO
#define USART2_RX_IO       MDX_BT_RXD_IO

// I/O line direction bits.
#define USART1_TX_TRIS     MDX_TX1_RELAY0_TRIS
#define USART1_RX_TRIS     MDX_RX1_RELAY1_TRIS
#define USART2_TX_TRIS     MDX_BT_TXD_TRIS
#define USART2_RX_TRIS     MDX_BT_RXD_TRIS

//
// Control registers status values.
// 

// TXSTAx: Transmit status and control register.
// CSRC: Clock Source Select bit.
#define USART_SLAVE_MODE               0  // Slave mode (clock from external source).
#define USART_MASTER_MODE              1  // Master mode (clock generated internally from BRG).
// TX9: 9-bit Transmit Enable bit.
#define USART_8_BIT_TRANSMISSION       0  // Selects 8-bit transmission
#define USART_9_BIT_TRANSMISSION       1  // Selects 9-bit transmission
// TXEN: Transmit Enable bit
#define USART_TRANSMIT_DISABLE         0  // Transmit disabled.
#define USART_TRANSMIT_ENABLE          1  // Transmit enabled.
// SYNC: EUSART Mode Select bit.
#define USART_ASYNCHRONOUS_MODE        0  // Asynchronous mode.
#define USART_SYNCHRONOUS_MODE         1  // Synchronous mode.
// SENDB: Send Break Character bit.
#define USART_BREAK_COMPLETE           0  // Sync Break transmission completed.
#define USART_SEND_BREAK               1  // Send Sync Break on next transmission (cleared by hardware upon completion).
// BRGH: High Baud Rate Select bit.
#define USART_LOW_SPEED                0  // Low speed.
#define USART_HIGH_SPEED               1  // High speed.
// TRMT: Transmit Shift Register Status bit.
#define USART_TSR_FULL                 0  // TSR full.
#define USART_TSR_EMPTY                1  // TSR empty.

// RCSTAx: Receive status and control register.
// SPEN: Serial Port Enable bit.
#define USART_PORT_DISABLE             0  // Serial port disabled (held in Reset).
#define USART_PORT_ENABLE              1  // Serial port enabled (configures RXx/DTx and TXx/CKx pins as serial port pins).
// RX9: 9-bit Receive Enable bit.
#define USART_8_BIT_RECEPTION          0  // Selects 8-bit reception.
#define USART_9_BIT_RECEPTION          1  // Selects 9-bit reception.
// SREN: Single Receive Enable bit.
#define USART_DISABLE_SINGLE_RECEIVE   0  // Disables single receive.
#define USART_ENABLE_SINGLE_RECEIVE    1  // Enables single receive.
// CREN: Continuous Receive Enable bit.
#define USART_DISABLE_RECEIVER         0  // Disables receiver.
#define USART_ENABLE_RECEIVER          1  // Enables receiver.
// ADDEN: Address Detect Enable bit.
#define USART_ADDRESS_DETECT_DISABLE   0  // Disables address detection.
#define USART_ADDRESS_DETECT_ENABLE    1  // Enables address detection.
// FERR: Framing Error bit.
#define USART_NO_FRAMING_ERROR         0  // No framing error.
#define USART_FRAMING_ERROR            1  // Framing error.
// OERR: Overrun Error bit.
#define USART_NO_OVERRUN_ERROR         0 // No overrun error.
#define USART_OVERRUN_ERROR            1 // Overrun error (can be cleared by clearing bit CREN).

// BAUDCONx: Baud rate control register.
// ABDOVF: Auto-Baud Acquisition Rollover Status bit.
#define USART_BRG_ROLLOVER             1  // A BRG rollover has occurred during Auto-Baud Rate Detect mode.
#define USART_NO_BRG_ROLOVER           0  // No BRG rollover has occurred.
// RCIDL: Receive Operation Idle Status bit.
#define USART_RECEIVE_IDLE             1  // Receive operation is idle.
#define USART_RECEIVE_ACTIVE           0  // Receive operation is active.
// SCKP: Synchronous Clock Polarity Select bit.
#define USART_IDLE_STATE_AT_HIGH_LEVEL 1  // Idle state for clock (CKx) is a high level.
#define USART_IDLE_STATE_AT_LOW_LEVEL  0  // Idle state for clock (CKx) is a low level.
// BRG16: 16-bit Baud Rate Register Enable bit.
#define USART_16_BIT_BRG               1  // 16-bit Baud Rate Generator – SPBRGHx and SPBRGx.
#define USART_8_BIT_BRG                0  // 8-bit Baud Rate Generator – SPBRGx only (Compatible mode), SPBRGHx value ignored.
// WUE: Wake-up Enable bit.
#define USART_RX_MONITOR_ENABLE        1  // EUSART will continue to sample the RXx pin.
#define USART_RX_MONITOR_DISABLE       0  // RXx pin not monitored or rising edge detected.
// ABDEN: Auto-Baud Detect Enable bit.
#define USART_BR_MEASUREMENT_ENABLE    1  // Enable baud rate measurement on the next character.
#define USART_BR_MEASUREMENT_DISABLE   0  // Baud rate measurement disabled or completed.

//
// Baud rate register value definitions.
//

// The formula to be used is:
//    b = Fosc / (4 * (n + 1)) thus
//    n = (Fosc / (4 * b)) - 1
//
//       b         n         n       b      %
//    required calculated selected actual error 
//        300   26665.67    26666     299  0.33
//       1200    6665.67     6666    1199  0.08
//       2400    3332.33     3332    2400  0.00
//       4800    1665.67     1666    4799  0.02
//       9600     832.33      832    9603  0.03
//      19200     415.67      416   19184  0.08
//      38400     207.33      207   38461  0.16
//      57600     137.89      138   57553  0.08
//     115200      68.44       68  115942  0.64

#define USART_BAUD_RATE_300      26666
#define USART_BAUD_RATE_1200      6666
#define USART_BAUD_RATE_2400      3332
#define USART_BAUD_RATE_4800      1666
#define USART_BAUD_RATE_9600       832
#define USART_BAUD_RATE_19200      416
#define USART_BAUD_RATE_38400      207
#define USART_BAUD_RATE_57600      138
#define USART_BAUD_RATE_115200      68

//
// General definitions.
//

// Receive error flags.
#define USART_STATUS_NO_ERROR              	0b00000000
#define USART_STATUS_FRAME_ERROR        	0b00000001
#define USART_STATUS_OVERRUN_ERROR    	0b00000010
#define USART_STATUS_BUFFER_ERROR       	0b00000100
#define USART_STATUS_TIMEOUT                 	0b00001000

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

void  DrvUsartInit( _UsartPort Port, UINT16 BaudRate, UINT8 *Buffer, UINT8 BufferSize  );
void  DrvUsartReset( _UsartPort Port );
void	DrvUsartSendByte( _UsartPort Port, UINT8 Data );
void	DrvUsartSendData( _UsartPort Port, UINT8 *Data, UINT8 Count );
_Bool DrvUsartByteReady( _UsartPort Port );
_Bool DrvUsartReadByte( _UsartPort Port, UINT8 *Byte );
UINT8  DrvUsartLastError( _UsartPort Port );
void  DrvUsartDisable( _UsartPort Port );

void  DrvUsart1Isr( void );
void  DrvUsart2Isr( void );
extern volatile UINT8 DrvUsart2GetStatus(void);
extern volatile UINT16 DrvUsart2Read( void* pBuffer, UINT8 MaxCounts);
extern volatile UINT16 DrvUsart2GetNumberOfBytesAvailable(void);
extern volatile UINT16 DrvUsart2GetMessageLength(void);
//
// End of include file.
//

#endif
