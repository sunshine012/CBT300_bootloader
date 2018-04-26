////////////////////////////////////////////////////////////////////////////////
//
// Main.c
//
////////////////////////////////////////////////////////////////////////////////

//
// Required include files.
//

#include "DrvPic18f67J10.h"
#include <stdio.h>
#include <string.h>

#include "MplabC18.h"
#include "DrvMdxP600.h"

//#include "DrvSpi.h"
//#include "DrvSound.h"
//#include "DrvRtc_M41T94.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvSsp_18F67J10.h"
#include "DrvUsart_18F67J10.h"
#include "DrvEeprom_25AA320.h"
#include "DrvInt_18F67J10.h"
#include "DrvConfigBoard.h"
#include "DrvPan1026.h"
#include "Font6x8.h"
#include "DrvLoad.h"
//#include "DrvGain.h"
#include "DrvKey.h"
#include "DrvTimer_18F67J10.h"
#include "SysBluetooth.h"
//#include "DrvCca.h"
//#include "DrvPri_BD2_2880.h"
//#include "DrvMMC.h"

#include "bootload.h"
#include "ChkSCod.h"
#include "AppData.h"
#include "AppBluetooth.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

typedef void (*pFVoidVoid)(void);      
typedef UINT8 (*pFByteByte)(UINT8 data);


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
void AppInit( void )
{
    DrvCBT300Init();
    DrvSsp1InitAsSpiMaster();
    DrvEepromInit();
    DrvLoadInit();
    DrvConfigBoardInit();
    
    DrvKeyInit();
    DrvIntInit();
    Initial_LCD();
    DrvTimer0Init();

    DrvUsartInit( USART_PORT_1, USART_BAUD_RATE_57600, SerialRxBuffer1, sizeof(SerialRxBuffer1) );   // for MXT programing

    //DrvTimer1Init();
    //DrvTimer2Init();
    DisableWatchDog();
}

void VariableInitialize(void)	
{
    ConfigData = DrvConfigBoardGet();
	DelayXms( 10 );
	ConfigData = DrvConfigBoardGet();
   	ConnectionFlag = FALSE;
	ConnectionCounter = 0;
	BTSystemConfig 	= OPERATE_SYSTEM_NONE;//OPERATE_SYSTEM_ANDROID;
	UpdateSrcSerialNum = UPDATE_SOURCE_NONE;
}


/*int _user_putc( char c )
{
   BYTE     Buffer[ 8 ];
   UINT8    Index;   

   if( c == '\0' )
   { 
      return( c );
   }

   if( (c < dFont6x8_CharacterOffset) || (c >= (dFont6x8_CharacterOffset + dFont6x8_FontSize)  ) )
   {
      c = dFont6x8_UpDownArrow;
   }

   memcpypgm2ram( Buffer, Font6x8[ c - dFont6x8_CharacterOffset ], 6 );
   Buffer[ 6 ] = 0;
   Buffer[ 7 ] = 0;

   DrvLcdDisplayGraphic( Buffer, 6 );

   return( c );
}*/

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

void main( void )
{
    UINT8       RunApplication;
    
    memset(SerialPort2DrvBuffer, 0x00, sizeof(SerialPort2DrvBuffer));
    memset(SerialRxBuffer1, 0x00, sizeof(SerialRxBuffer1));
    memset(SerialRxBuffer2, 0x00, sizeof(SerialRxBuffer2));
    
    AppInit();
	CLRWDT();
    VariableInitialize();
	CLRWDT();
    
    RunApplication = ChkSumCode();      //verify the checksum
  
   if(KEY_SW1_IO == 0 && KEY_SW3_IO == 0)
      RunApplication = 0;              //force to stay in 
   if(RunApplication == 2)
   {                                   //call address sent with data sent
      RunApplication = (*((pFByteByte)(P18F87_FLASH_START_ADDRESS + 0x30)))(0xAA);         
   }
   
    if(CBT100_COMFIG == ConfigData)
    {
        DrvUsartInit( USART_PORT_1, USART_BAUD_RATE_57600, 0, 0);   // for MXT programing
        BootLoad();     //run serial bootloader
    }
    else if(CBT300_CONFIG == ConfigData)
    {	
        //DrvUsartInit( USART_PORT_1, USART_BAUD_RATE_57600, SerialRxBuffer1, sizeof(SerialRxBuffer1) );   // for MXT programing
        DrvUsartInit( USART_PORT_2, USART_BAUD_RATE_115200, SerialPort2DrvBuffer, sizeof(SerialPort2DrvBuffer) );
        DrvPan1026Init();
        DelayXms(200);
        BTSystemConfig = OPERATE_SYSTEM_ANDROID;
        BLOperatingState = BL_BLUETOOTH_INIT;
        BlueToothState();
    }     
}

