/*******************************************************************
;
;  Copyright (c) Midtronics 2006
;
;     Structure definitions.
;
*******************************************************************/
#ifndef BOOT_LOAD_H
#define BOOT_LOAD_H

#include "DrvPic18f67J10.h"
#include "MplabC18.h"
#include "DrvMdxP600.h"

/* Flash Defines */
#define P18F87_FLASH_SIZE               0x20000        //flash size
#define P18F87_FLASH_ROW_SIZE           64             //erase bank size
#define P18F87_FLASH_SECTOR_SIZE        1024           //erase bank size
#define P18F87_FLASH_CONFIG_SIZE        8              //number of bytes reserved for config bits
#define P18F87_FLASH_CHECKSUM_SIZE      2              //number of bytes reserved for checksum before config bits
#define P18F87_FLASH_START_ADDRESS      0x8000         //start of user application flash
/* The rest are automatically calculated */
#define P18F87_FLASH_END_ADDRESS        (P18F87_FLASH_SIZE - 1)
#define P18F87_FLASH_LAST_SECTOR        (P18F87_FLASH_SIZE - P18F87_FLASH_SECTOR_SIZE)  //last erase bank
#define P18F87_FLASH_CONFIG_ADDRESS     (P18F87_FLASH_SIZE - P18F87_FLASH_CONFIG_SIZE)
#define P18F87_FLASH_CHECKSUM_ADDRESS   (P18F87_FLASH_LAST_SECTOR - P18F87_FLASH_CHECKSUM_SIZE)
#define P18F87_FLASH_LAST_CODE_ADDRESS  (P18F87_FLASH_CHECKSUM_ADDRESS - 1)
#define P18F87_FLASH_LAST_ROW           (P18F87_FLASH_SIZE - P18F87_FLASH_ROW_SIZE)     //last programable row
/* End of Flash Location Defines */

#define PROGRAM_ALL              0           //write flash row and add config bits if last row
#define PROGRAM_CONFIG_BITS      1           //only write flash row if last row and fill with
                                             //0xFF's and config bits

#define FAIL					 0
#define PASS					 1

// Test state definitions
#define BOOT_LOAD_INITIALIZE           0
#define BOOT_LOAD_WAIT_COMMAND         (BOOT_LOAD_INITIALIZE+1)

#define  INTERNAL_FLASH    0
#define  EXTERNAL_FLASH    1
#define  EXTERNAL_EEPROM   2

#define DATA_CARD_ERROR          0
#define INCORRECT_FORMAT_ERROR   1
#define DATA_CARD_FULL_ERROR     2
#define SRECORD_TYPE_ERROR       3
#define FILE_READ_ERROR          4

extern const rom char BootLoaderText[];
extern const rom char LoadingDataText[];
extern const rom char VersionNumberText[];


extern UINT8 MXTUpdateTestState;
extern UINT8 CodeBuf[P18F87_FLASH_ROW_SIZE + 2];

extern void DisplayRomString(UINT8 row, const rom char* string);

extern void BootLoad(void);
//extern void UploadFile(FFS_FILE* pFile, UINT8 Memory);
extern UINT8 EraseFlash(UINT32 RowAddress);
extern UINT8 WriteFlash(UINT32 RowAddress, UINT8* Buffer, UINT8 Mode);
extern UINT8 ReadCharacter(void);
extern void TransmitCharacter(UINT8 data);
//extern void DisplayRomString(UINT8 row, UINT8 column, const rom char* string);
//extern void VerifyError(UINT8 ErrorCode);

#endif

