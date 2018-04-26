#include "DrvPan1026.h"
#include "DrvLCD_OPTO1140GG.h"

void DrvPan1026Init( void )
{
	BT_RESET_TRIS 		= TRIS_BIT_OUTPUT;
	BT_PWR_ENABLE_TRIS 	= TRIS_BIT_OUTPUT;

	BT_PWR_ENABLE_IO = 0;
	BT_RESET_IO       = 0;
	DelayXms( 2 );
	BT_PWR_ENABLE_IO = 1;
	BT_RESET_IO = 1;
}

void DrvPan1026Off(void)
{
	DrvBluetoothOff();
	DrvBluetoothResetOff();
}



