/*********************************************************************
 *
 *                  External LCD access routines
 *
 *********************************************************************
 * FileName:        XLCD.c
 * Dependencies:    xlcd.h
 * Processor:       PIC18
 * Complier:        MCC18 v1.00.50 or higher
 *                  HITECH PICC-18 V8.10PL1 or higher
 * Company:         Microchip Technology, Inc.
 *
 *
 * Author               Date           Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * King Chen     06/12/2015    Original        (Rev 1.0)
 ********************************************************************/
#include "DrvLCD_OPTO1140GG.h"
#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include <string.h>
#include <stdio.h>

void LCD_Delay1ms(void)
{
  	DelayXus(1000);
}

void DelayXus(unsigned int microsecs)
{
	while(microsecs > 0)
	{
		LCD_Delay1us();
		microsecs--;
	}
}

void DelayXms(unsigned int millisecs)
{
	while(millisecs > 0)
	{
		LCD_Delay1ms();
		millisecs--;
	}
}

//=============transfer command to LCM===============
void XLCD_Command(unsigned char Data)
{
        unsigned char i;
        LCD12832_CS=0;
        LCD12832_RS=0;
        for(i=8;i>0; i--)
        {
            LCD12832_SCLK=0;
            if(Data&0x80)
                LCD12832_SID=1;
            else
                LCD12832_SID=0;
            LCD12832_SCLK=1;
            Data <<=1;
        }
        LCD12832_CS=1;
}

//-----------transfer data to LCM---------------
void XLCD_Data(unsigned char Data)
{
        unsigned char i;
        LCD12832_CS=0;
        LCD12832_RS=1;
        for(i=8; i>0; i--)
        {
            LCD12832_SCLK=0;
            if(Data&0x80)
                LCD12832_SID=1;
            else
                LCD12832_SID=0;
            LCD12832_SCLK=1;
            Data <<=1;
        }
        LCD12832_CS=1;
}

void Clear_Screen(void)
{
        unsigned char i,j;
        for(i=0;i<9;i++)
        {
            XLCD_Address(1+i,1);
            for(j=132; j>0; j--)
            {
               XLCD_Data(0x00);				//send "0x00" to lcm,clear all dots
            }
        }
}

void Initial_LCD(void)
{
      LCD_CS_TRIS    = TRIS_BIT_OUTPUT;
      LCD_RESET_TRIS = TRIS_BIT_OUTPUT;
      LCD_RS_TRIS    = TRIS_BIT_OUTPUT;
      LCD_SID_TRIS   = TRIS_BIT_OUTPUT;
      LCD_SCLK_TRIS  = TRIS_BIT_OUTPUT;

       LCD12832_CS    = 0;
    	LCD12832_SID   = 0;
    	LCD12832_SCLK  = 0;
    	LCD12832_RESET = 0;
    	LCD12832_RS    = 0;

      LCD12832_CS=0;
      LCD12832_RESET=0;   //LCD12832_RESET=0:reset starting
      DelayXms(50);       //Delay more than 10ms
      LCD12832_RESET=1;		//Stop reset
      DelayXms(50);       //Delay more than 1ms

      XLCD_Command(0xe2);	 //Software reset
      DelayXms(10);
      XLCD_Command(0xa2);  //BIAS:0xa2£º1/9
      XLCD_Command(0xa1);  //seg direction:reverse
      XLCD_Command(0xc8);  //com output mode selection: normal C0

/*	XLCD_Command(0xAC);
	XLCD_Command(0x00);
	XLCD_Command(0xD5); 
	XLCD_Command(0x00);*/

      XLCD_Command(0x22);  //V5 voltage regulator internal resistor ratio set
      XLCD_Command(0x81);  //set electronic mode set
      XLCD_Command(0x27);  //set electronic register set 8.0v--0x27;8.2v--0x2a;8.5v--0x2f

      XLCD_Command(0xa6);  //Normal display
      XLCD_Command(0x2f);  //power controller set
      XLCD_Command(0xaf);  //turn on display

      LCD12832_CS=1;
      Clear_Screen();
}

//set the page address and column address of LCD
void XLCD_Address(unsigned char page,unsigned char column)
{
        LCD12832_CS=0;
        column=column +3;  	    					//Because column address is from 0 to 127,so column=column-1
        page=page-1;
        XLCD_Command(0xb0+page);   				//set page address,LCD panel is divided to 8 pages,1 page is include 8 lines.
        XLCD_Command(((column>>4)&0x0f)+0x10);	//set the upper 4 bits of column address
        XLCD_Command(column&0x0f);				//set the lower 4 bits of column address
}

void Display_Graphic_8X8(unsigned char page, unsigned char col, const unsigned char *dp)
{
    	unsigned char i;
        XLCD_Address(page,col);
        for(i=8; i>0; i--)
        {
            XLCD_Data(*dp);
            dp++;
        }
}
void Display_Graphic_6X16(unsigned char page, unsigned char col, const unsigned char *dp, unsigned char Options)
{
    unsigned char i,j;
    unsigned char TempChar;
    for(j=0; j<2; j++)
    {
        XLCD_Address(page+j,col);
        for(i=6; i>0; i--)
        {
            if(Options & DISPLAY_I)
			TempChar = 	~(*dp);
	     else
		 	TempChar = 	*dp;
            XLCD_Data(TempChar);
            dp++;
        }
    }
}

void Display_Graphic_12X16(unsigned char page, unsigned char col, const unsigned char *dp)
{
    unsigned char i,j;
    for(j=0; j<2; j++)
    {
        XLCD_Address(page+j,col);
        for(i=12; i>0; i--)
        {
            XLCD_Data(*dp);
            dp++;
        }

    }
}

void Display_Graphic_6X8(unsigned char page, unsigned char col, const unsigned char *dp, unsigned char Options)
{
   unsigned char i;
   unsigned char TempBuffer;
   XLCD_Address(page,col);
   for(i=0; i<6; i++)
   {
        if(Options & DISPLAY_I)
            TempBuffer=~(*dp);
        else
            TempBuffer=*dp;
        XLCD_Data(TempBuffer);
        dp++;
   }
}

void Full_Screen(void)
{
        unsigned char i,j;
        for(i=0;i<9;i++)
        {
            XLCD_Address(1+i,1);
            for(j=132; j>0; j--)
            {
               	XLCD_Data(0xFF);				//send "0x00" to lcm,clear all dots
            }
        }
}


/*
void Display_Graphic_1X128(unsigned char Row, ,const unsigned char *dp)
{
    unsigned char i,j;
    unsigned char TempChar;

        XLCD_Address(page+j,col);
        for(i=16; i>0; i--)
        {
		TempChar = 	*dp;
            XLCD_Data(TempChar);
            dp++;
        }

}
*/


