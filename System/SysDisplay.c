/******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:             SysDisplay.c
 *
 * Designed by:   King Chen
 *
 *
 * Description:
 *
 * 
 * References:
 *
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include "SysDisplay.h"
#include "DrvLCD_OPTO1140GG.h"
#include "Font6x8.h"

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
// Gobal functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Function:    
// 
// Parameters:  
// Return Value:
// 
// Description:
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 09/02/15    KC         Developed
//

void SysClear_Line(unsigned char Line)
{
	unsigned char SpaceBufer[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  	unsigned char i;
  	unsigned char Col=0;
	Line = (Line<<1)+1;
	for(i=0; i<20; i++)
	{
		Display_Graphic_6X16(Line,Col,SpaceBufer, DISPLAY_N);// BLANK  a line
		Col = Col +6;
	}
}
void SysClear_Line_S(unsigned char Line)
{
	unsigned char SpaceBufer[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  	unsigned char i;
  	unsigned char Col=0;
	Line = Line+2;
	for(i=0; i<16; i++)
	{
		Display_Graphic_8X8(Line,Col, SpaceBufer);// BLANK  a line
		Col = Col +8;
	}
}
    

void DisplayString_S(const unsigned char *string, unsigned char row, unsigned char Mask)
{
  unsigned char ByLen;
  unsigned char ByColCount;
  unsigned char i;
  unsigned char Temp;
  unsigned char Buffer[ 8 ];

	//ByLen = strlen((char *)string);
	ByLen = 0;
	i = 0;
	while(string[i] != '\0')
	{
		ByLen++;
		i++;
	}
	
	ByColCount = 0;
	if(!ByLen)
	     return ;	
	//row = (row<<1)+1;
	row = row +2;
	if(DISPLAY_C&Mask)
		ByColCount =(128-ByLen*6)>>1;  // Centre  
	else if(DISPLAY_R&Mask)
		ByColCount =128-ByLen*6;          // Right
	else if(DISPLAY_N&Mask)
		ByColCount =0;                           // Normal	
	for(i=0; i<ByLen; i++)
	{
		Temp = string[i]-dFont6x8_CharacterOffset;
		memcpypgm2ram( Buffer, Font6x8[ Temp ], 6 );
		Buffer[ 6 ] = 0;
		Display_Graphic_6X8(row, ByColCount, Buffer, Mask);
		ByColCount = ByColCount+6;
	}
}
