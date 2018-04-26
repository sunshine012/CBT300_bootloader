/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          DrvEeprom_25AA320.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvEeprom_25AA320.h $
 * $Archive: /MDXP600/192-000039 PCB/192-110276 Hella/Drivers/DrvEeprom_25AA320.h $
 * $History: DrvEeprom_25AA320.h $
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
 * User: Bbroer       Date: 1-12-10    Time: 16:39
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
 * Contains all required definitions for the 25AA320 EEPROM chip. 
 * 
 *
 * 25AA320/25LC320/25C320 Datasheet - DS21227E
 *
*******************************************************************************/

#ifndef _EEPROM_25AA320_H_
#define _EEPROM_25AA320_H_

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

//
// The following types define the internal structures of the different registers
// as specified in the datasheet.
//

typedef union
{
   UINT8 Byte;
   struct
   {
      BITS  WriteInProcess:      1;
      BITS  WriteEnableLatch:    1;
      BITS  BlockProtection:     2;
      BITS  NotUsed:             3;
      BITS  WriteProtect:        1;
   };
} _EepromStatus, *_EepromStatusPtr;


////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

//
// I/O line definitions.
//

// I/O lines.
#define EEPROM_WP_IO          MDX_EEWP_IO
#define EEPROM_HOLD_IO        MDX_EEHOLD_IO

// I/O line direction bits.
#define EEPROM_WP_TRIS        MDX_EEWP_TRIS
#define EEPROM_HOLD_TRIS      MDX_EEHOLD_TRIS

// I/O line states.
#define EEPROM_WP_ENABLE      0
#define EEPROM_WP_DISABLE     1

#define EEPROM_HOLD_ENABLE    0
#define EEPROM_HOLD_DISABLE   1

//
// 
//

// Command definitions.
#define EEPROM_CMD_READ                0b00000011
#define EEPROM_CMD_WRITE               0b00000010
#define EEPROM_CMD_WRDI                0b00000100
#define EEPROM_CMD_WREN                0b00000110
#define EEPROM_CMD_RDSR                0b00000101
#define EEPROM_CMD_WSSR                0b00000001

// Status byte bit states.
#define EEPROM_WRITE_READY             0        // No write operation is going on.
#define EEPROM_WRITE_IN_PROGRESS       1        // Write operation in progress.

#define EEPROM_WRITE_ENABKE_LATCH_OFF  0        //
#define EEPROM_WRITE_ENABKE_LATCH_ON   1        //

#define EEPROM_BLOCK_PROTECT_NONE      0b00     // Protect nothing.
#define EEPROM_BLOCK_PROTECT_0C00_0FFF 0b01     // Protect upper 1/4.
#define EEPROM_BLOCK_PROTECT_0800_0FFF 0b10     // Protect upper 1/2.
#define EEPROM_BLOCK_PROTECT_0000_0FFF 0b11     // Protect all.

#define EEPROM_WRITE_PROTECT_ENABLE    0        // Enables write protection.
#define EEPROM_WRITE_PROTECT_DISABLE   1        // Disables write protection.

#define EEPROM_SIZE                    32768

// The write complete waits until the write cycle has been completed. To 
// prevent the loop from not terminating a timeout counter is set. When the
// counter reaches 0, the wait is terminated. The value if the counter is the
// calculated as follows: Twc / Tnop = 5ms / 125ns = 4000. Since the loop 
// consists of much more than just a NOP, this value is mor ethan enough
#define EEPROM_WRITE_COMPLETE_TIME_OUT 40000
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

void  DrvEepromInit( void );
void  DrvEepromRead( UINT16 Address, UINT8 *Buffer, UINT16 Size );
void  DrvEepromWrite( UINT16 Address, UINT8 *Buffer, UINT16 Size );
_Bool DrvEepromWriteAndVerify( UINT16 Address, UINT8 *Buffer, UINT16 Size );

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif





