/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          Eeprom_25AA320.c
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvEeprom_25AA320.c $
 * $Archive: /MDXP600/192-000039 PCB/192-110276 Hella/Drivers/DrvEeprom_25AA320.c $
 * $History: DrvEeprom_25AA320.c $
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 5/29/12    Time: 6:02a
 * Created in $/MDXP600/192-000039 PCB/192-110276 Hella/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 10/03/11   Time: 4:14a
 * Created in $/MDXP600/192-000039 PCB/192-110276 Hella/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Abremen      Date: 4/19/11    Time: 8:38a
 * Created in $/MDXP600/192-000039 PCB/192-110240 MDX-645P_YUASA/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 1-12-10    Time: 16:37
 * Created in $/MDXP600/192-000039 PCB/192-110223 MDX-645P KRAMP/Drivers/Standard
 * Added driver files from the master
 * 
 * *****************  Version 2  *****************
 * User: Rick         Date: 2/29/08    Time: 4:42p
 * Updated in $/MDXP600/192-000039 PCB/Master/Drivers/Standard
 * File comment format for Source Safe
 * 
 * *****************  Version 1  *****************
 * User: Rick         Date: 2/26/08    Time: 8:03a
 * Created in $/MDXP600/192-000039 PCB/Master/Drivers
 *
 * Description:
 *
 * Contains all required definitioans of the 25AA320 32K EEPROM chip. 
 * 
 *
 * 25AA320/25LC320/25C320 Datasheet - DS21227E
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvEeprom_25AA320.h"
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

//
// Function:      
// 
// Parameters:    
// Return Value:  - Status: The value of the EEPROM status register.
// 
// Description:   This function reads the specified number of bytes from the
//                EEPROM starting at the specified address.
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

_EepromStatus EepromReadStatus( void )
{
   _EepromStatus Status;

   //DrvSpiSelectDevice( SPI_DEVICE_EEPROM );
   SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_ENABLE;
   //  CS setup time: Tsu > 250ns
   MDX_DELAY_250NS();

   DrvSsp1SpiWrite( EEPROM_CMD_RDSR );

   Status.Byte = DrvSsp1SpiRead();

  // DrvSpiSelectDevice( SPI_DEVICE_NONE );
   SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_DISABLE;
   
   //  CS disable time: Tcsd > 500ns
   MDX_DELAY_500NS();

   return( Status );
}

void EepromWaitForWriteCompletion( UINT8 RequiredStatus )
{
   _EepromStatus  Status;
   UINT16         TimeOut;
   
   TimeOut = EEPROM_WRITE_COMPLETE_TIME_OUT;
   do
   {
      Status = EepromReadStatus();
      TimeOut--;

      CLRWDT();
   }
   while( ((Status.Byte & 0x7F) != RequiredStatus) && TimeOut );
}

void EepromWriteEnable( void )
{
   EEPROM_WP_IO = EEPROM_WP_DISABLE;
   EEPROM_HOLD_IO = EEPROM_HOLD_DISABLE;

   //DrvSpiSelectDevice( SPI_DEVICE_EEPROM );
   SPI_EEPROM_CS_IO = SPI_EEPROM_CS_ENABLE;

   // Delay (see spec):
   //  CS setup time: Tsu > 250ns
   MDX_DELAY_250NS();

   DrvSsp1SpiWrite( EEPROM_CMD_WREN );

   //DrvSpiSelectDevice( SPI_DEVICE_NONE );
   SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_DISABLE;
   // Delay (see spec):
   //  CS disable time: Tcsd > 500ns
   MDX_DELAY_500NS();

   EepromWaitForWriteCompletion(0x02);
}

void EepromWriteDisable( void )
{
   //DrvSpiSelectDevice( SPI_DEVICE_EEPROM );
   SPI_EEPROM_CS_IO = SPI_EEPROM_CS_ENABLE;

   // Delay (see spec):
   //  CS setup time: Tsu > 250ns
   MDX_DELAY_250NS();

   DrvSsp1SpiWrite( EEPROM_CMD_WRDI )    ;

   //DrvSpiSelectDevice( SPI_DEVICE_NONE );
   SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_DISABLE;
   // Delay (see spec):
   //  CS disable time: Tcsd > 500ns
   MDX_DELAY_500NS();

   EepromWaitForWriteCompletion(0x00);
   
   EEPROM_WP_IO = EEPROM_WP_ENABLE;
   EEPROM_HOLD_IO = EEPROM_HOLD_DISABLE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Function:      
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvEepromInit( void )
{
   EEPROM_WP_TRIS       = TRIS_BIT_OUTPUT;
   EEPROM_HOLD_TRIS     = TRIS_BIT_OUTPUT;
   SPI_EEPROM_CS_TRIS = TRIS_BIT_OUTPUT;
   
   
   EEPROM_WP_IO         = EEPROM_WP_ENABLE;
   EEPROM_HOLD_IO       = EEPROM_HOLD_DISABLE;
   SPI_EEPROM_CS_IO 		= SPI_EEPROM_CS_DISABLE;
   // Delay (see spec):
   //  CS setup time: Tsu > 250ns
   MDX_DELAY_500NS();
   
}

//
// Function:      DrvEepromRead
// 
// Parameters:    - Address: a 16 bit integer value indicating the EEPROM 
//                address where the read has to start.
//                - Buffer: a buffer where the read bytes are stored.
//                - Size: the number of bytes to read.
// Return Value:  None.
// 
// Description:   This function reads the specified number of bytes from the
//                EEPROM starting at the specified address.
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvEepromRead( UINT16 Address, UINT8 *Buffer, UINT16 Size )
{
   UINT8 Data;
   EEPROM_HOLD_IO = EEPROM_HOLD_DISABLE;
   //DrvSpiSelectDevice( SPI_DEVICE_EEPROM );
   SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_ENABLE;
   // Delay (see spec):
   //  CS setup time: Tsu > 250ns
   MDX_DELAY_250NS();
      
   DrvSsp1SpiWrite( EEPROM_CMD_READ );           
   DrvSsp1SpiWrite( GET_HIGH_BYTE( Address ) );
   DrvSsp1SpiWrite( GET_LOW_BYTE( Address ) );
     
   while( Size-- > 0 )
   {
      Data = DrvSsp1SpiRead();
      *Buffer++ = Data;

      CLRWDT();
   };
   SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_DISABLE;
   //DrvSpiSelectDevice( SPI_DEVICE_NONE );
   // Delay (see spec):
   //  CS disable time: Tcsd > 500ns
   MDX_DELAY_500NS();
}

//
// Function:      DrvEepromVerify
// 
// Parameters:    - Address: a 16 bit integer value indicating the EEPROM 
//                address where the verify has to start.
//                - Buffer: a buffer with which the data has to be verified.
//                - Size: the number of bytes to verify
// Return Value:  None.
// 
// Description:   This function verifies the specified number of bytes in the
//                EEPROM starting at the specified address with the buffer.
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

_Bool DrvEepromVerify( UINT16 Address, UINT8 *Buffer, UINT8 Size )
{
   _Bool Result;
   UINT8  Byte;

   SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_ENABLE;
   //DrvSpiSelectDevice( SPI_DEVICE_EEPROM );
   // Delay (see spec):
   //  CS setup time: Tsu > 250ns
   MDX_DELAY_250NS();
      
   DrvSsp1SpiWrite( EEPROM_CMD_READ );           
   DrvSsp1SpiWrite( GET_HIGH_BYTE( Address ) );
   DrvSsp1SpiWrite( GET_LOW_BYTE( Address ) );

   Result = TRUE;     
   while( (Size-- > 0) && Result )
   {
      Byte     = DrvSsp1SpiRead();
      Result   = (*Buffer == Byte);
      Buffer++;                  

      CLRWDT();
   };

   //DrvSpiSelectDevice( SPI_DEVICE_NONE );
   SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_DISABLE;
   // Delay (see spec):
   //  CS disable time: Tcsd > 500ns
   MDX_DELAY_500NS();

   return( Result );
}

//
// Function:      
// 
// Parameters:    - Address: a 16 bit integer value indicating the EEPROM 
//                address where the read has to start.
//                - Buffer: a buffer where the bytes to write are stored.
//                - Size: the number of bytes to read.
// Return Value:  None.
// 
// Description:   This function writes the specified number of bytes from a
//                buffer to the EEPROM starting at the specified address. The
//                write is done byte by byte and does not use the page mode.
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvEepromWrite( UINT16 Address, UINT8 *Buffer, UINT16 Size )
{
   while( Size-- > 0 )
   {
      	EepromWriteEnable();
   	SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_ENABLE;
      //DrvSpiSelectDevice( SPI_DEVICE_EEPROM );
   
      // Delay (see spec):
      //  CS setup time: Tsu > 250ns
      MDX_DELAY_250NS();
      
      DrvSsp1SpiWrite( EEPROM_CMD_WRITE );           
      DrvSsp1SpiWrite( GET_HIGH_BYTE( Address ) );
      DrvSsp1SpiWrite( GET_LOW_BYTE( Address ) );

      DrvSsp1SpiWrite( *Buffer );

      Buffer++;
      Address++;

      //DrvSpiSelectDevice( SPI_DEVICE_NONE );
   	SPI_EEPROM_CS_IO  = SPI_EEPROM_CS_DISABLE;
      // Delay (see spec):
      //  CS disable time: Tcsd > 500ns
      MDX_DELAY_500NS();

      EepromWaitForWriteCompletion(0x00);

      CLRWDT();
   }

   EepromWriteDisable();
}

//
// Function:      
// 
// Parameters:    - Address: a 16 bit integer value indicating the EEPROM 
//                address where the read has to start.
//                - Buffer: a buffer where the bytes to write are stored.
//                - Size: the number of bytes to read.
// Return Value:  None.
// 
// Description:   This function writes the specified number of bytes from a
//                buffer to the EEPROM starting at the specified address. The
//                write is done byte by byte and does not use the page mode.
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

_Bool DrvEepromWriteAndVerify( UINT16 Address, UINT8 *Buffer, UINT16 Size )
{
   DrvEepromWrite( Address, Buffer, Size );

   return( DrvEepromVerify( Address, Buffer, Size ) );
}
