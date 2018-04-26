////////////////////////////////////////////////////////////////////////////////
//
// Ssp.c
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvSsp_18F67J10.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////



void DrvSsp1InitAsSpiMaster( void ) 
{
   // Disble the SSP module for initialization.
   SSP1CON1bits.SSPEN = SSP_DISABLE;

   // SSP1STAT
   // b7 - SMP: Sample bit                         1: Input sampled at end of output time.
	// b6 - CKE: SPI Clock Select bit               0: Transmission on idle to active clock.
	// b5 - D/A: Data/Address bit                   0: Not used.
	// b4 - P: Stop bit                             0: Not used.
	// b3 - S: Start bit                            0: Not used.
	// b2 - R/W: Read/Write Information bit         0: Not used.
	// b1 - UA: Update Address bit                  0: Not used.
	// b0 - BF: Buffer Full Status bit              0: Receive buffer empty
   SSP1STAT = 0b10000000;
   
   // SSP1CON
   // b7 - WCOL: Write collision detect            0: No collision detected. 
	// b6 - SSPOV: Receive Overflow Indicator bit   0: Not used.
	// b5 - SSPEN: MSSP Enable bit                  0: Disable serial port.
	// b4 - CKP: Clock Polarity bit                 1: Clock idle state at high level.
	// b3 - SSPM3: MSSP Mode Select bit 3           0: \
	// b2 - SSPM2: MSSP Mode Select bit 2           0: | SPI Master mode
	// b1 - SSPM1: MSSP Mode Select bit 1           0: | Clock = Fosc/16
	// b0 - SSPM0: MSSP Mode Select bit 0           1: /  
   SSP1CON1 = 0b00010001;

   // Initialise directions of used I/O lines.
   SSP1_SDI_TRIS = TRIS_BIT_INPUT;
   SSP1_SDO_TRIS = TRIS_BIT_OUTPUT;
   SSP1_SCK_TRIS = TRIS_BIT_OUTPUT;
   
   // Enable the SSP module.
   SSP1CON1bits.SSPEN = SSP_ENABLE;
}

//
//
//

UINT8 DrvSsp1SpiWrite( UINT8 Data )
{
   // Initiate transfer cycle by writing data to the
   // transfer buffer.
   SSP1BUF = Data;
   
   // Wait until cycle is comlete.
   while( !SSP1STATbits.BF );

   // Return received data in transfer buffer.
   Data = SSP1BUF;
   return( Data );
}

//
//
//

UINT8 DrvSsp1SpiRead( void )
{
   return( DrvSsp1SpiWrite( 0 ) );
}

