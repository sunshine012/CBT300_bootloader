////////////////////////////////////////////////////////////////////////////////
//
// Usart_18F87J10.h
//
////////////////////////////////////////////////////////////////////////////////

#ifndef USART_18F87J10_H_
#define USART_18F87J10_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "p18f87J10.h"

#include "DrvMcc18.h"
#include "DrvMdxP600.h"

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
#define USART2_TX_IO       MDX_TXDPRN1_IO
#define USART2_RX_IO       MDX_RXDPRN_IO

// I/O line direction bits.
#define USART1_TX_TRIS     MDX_TX1_TRIS
#define USART1_RX_TRIS     MDX_RX1_TRIS
#define USART2_TX_TRIS     MDX_TXDPRN1_TRIS
#define USART2_RX_TRIS     MDX_RXDPRN_TRIS

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
#define USART_PORT_ENEBLE              1  // Serial port enabled (configures RXx/DTx and TXx/CKx pins as serial port pins).
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

_Bool	DrvUsart1Init( UINT8 Channel, BYTE *Buffer  );
void	DrvUsart1TransmitChar( UINT8 Channel, BYTE Data );
_Bool DrvUsart1ByteReady( UINT8 Channel );
BYTE  DrvUsart1ReadByte( UINT8 Channel );

_Bool	DrvUsart2Init( UINT8 Channel, BYTE *Buffer  );
void	DrvUsart2TransmitChar( UINT8 Channel, BYTE Data );
_Bool DrvUsart2ByteReady( UINT8 Channel );
BYTE  DrvUsart2ReadByte( UINT8 Channel );

//
// End of include file.
//

#endif
