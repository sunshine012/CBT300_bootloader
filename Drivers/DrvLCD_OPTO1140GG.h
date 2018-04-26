 /*********************************************************************
 *
 *                  External LCD access routines defs
 *
 *********************************************************************
 * FileName:        XLCD.h
 * Dependencies:    compiler.h
 * Processor:       PIC16
 * Complier:        MCC18 v1.00.50 or higher
 *                  HITECH PICC-18 V8.10PL1 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * King Chen     6/12/2015   Original        (Rev 1.0)
 ********************************************************************/
#ifndef __DRVLCD_OPTO1140GG_H
#define __DRVLCD_OPTO1140GG_H

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

#define LCD12832_CS             MDX_LCDCSB_IO
#define LCD12832_RESET          MDX_LCDRST_IO
#define LCD12832_RS             MDX_LCDAO_IO
#define LCD12832_SID            MDX_LCDSDA_IO
#define LCD12832_SCLK           MDX_LCDSCL_IO

#define LCD_CS_TRIS             MDX_LCDCSB_TRIS
#define LCD_RESET_TRIS          MDX_LCDRST_TRIS
#define LCD_RS_TRIS             MDX_LCDAO_TRIS
#define LCD_SID_TRIS            MDX_LCDSDA_TRIS
#define LCD_SCLK_TRIS           MDX_LCDSCL_TRIS

#define CLEARSCREEN()           Clear_Screen()

// Display options.
#define DISPLAY_NORMAL     0b00000000
#define DISPLAY_CENTERED   0b00000001
#define DISPLAY_INVERTED   0b00000010
#define DISPLAY_UNDERLINED 0b00000100
#define DISPLAY_FILL       0b00001000
#define DISPLAY_RIGHT       0b00010000
#define DISPLAY_LINEFEED   0b10000000

#define DISPLAY_N          DISPLAY_NORMAL
#define DISPLAY_C          DISPLAY_CENTERED
#define DISPLAY_I          DISPLAY_INVERTED
#define DISPLAY_U          DISPLAY_UNDERLINED
#define DISPLAY_F          DISPLAY_FILL
#define DISPLAY_R   		DISPLAY_RIGHT
#define DISPLAY_L          DISPLAY_LINEFEED

#define LCD_SCREEN_WIDTH            128
//32MHZ,
#define LCD_Delay1us()    {_asm nop nop nop nop nop nop nop nop _endasm}
#define LCD_DELAY_500NS()     {_asm nop nop nop nop _endasm}

//extern void DisplayString(const char *string, unsigned char row, unsigned char Mask);
//extern void DisplayString_S(const char *string, unsigned char row, unsigned char Mask);
//extern void LCD_Delay1us(void);
extern void LCD_Delay1ms(void);
extern void DelayXus(unsigned int microsecs);
extern void DelayXms(unsigned int millisecs);
extern void XLCD_Command(unsigned char Data);
extern void XLCD_Data(unsigned char Data);
extern void Initial_LCD(void);
//extern void Clear_Line(unsigned char Line);
//extern void Clear_Line_S(unsigned char Line);
extern void XLCD_Address(unsigned char page,unsigned char column);
extern void Clear_Screen(void);
extern void Display_Graphic_8X8(unsigned char page,unsigned char col,const unsigned char *dp);
extern void Display_Graphic_6X16(unsigned char page, unsigned char col, const unsigned char *dp, unsigned char Options);
extern void Display_Graphic_12X16(unsigned char page, unsigned char col, const unsigned char *dp);
extern void Display_Graphic_6X8(unsigned char page, unsigned char col, const unsigned char *dp, unsigned char Options);
//extern void AppControlStatus(unsigned char Mask);
extern void Full_Screen(void);

#endif
