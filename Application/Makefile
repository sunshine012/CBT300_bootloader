# MPLAB IDE generated this makefile for use with GNU make.
# Project: MDX-P600 BootLoader.mcp
# Date: Mon Jul 02 13:10:45 2012

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

MDX-P600\ BootLoader.cof : Font6x8.o Main.o MdxP600.o ChkSCod.o BootLoad.o DrvUsart_18F87J10.o DrvAdc_18F87J10.o DrvEeprom_25AA320.o DrvFlash_M25P16_.o DrvGain.o DrvInt_18F87J10.o DrvKey.o DrvLoad.o DrvPri_BD2_2880.o DrvRtc_M41T94.o DrvSound.o DrvSpi.o DrvSsp_18F87J10.o DrvTimer_18F87J10.o DrvPre_MCP8830.o DrvPower.o DrvIrda.o SysGraphic.o DrvMmc.o DrvLcd_MID184_310.o mem-ffs.o mem-mmcsd.o
	$(LD) /p18F87J10 /l"C:\Program Files\Microchip\MCC18\lib" "18f87j10i_e.lkr" "Font6x8.o" "Main.o" "MdxP600.o" "ChkSCod.o" "BootLoad.o" "DrvUsart_18F87J10.o" "DrvAdc_18F87J10.o" "DrvEeprom_25AA320.o" "DrvFlash_M25P16_.o" "DrvGain.o" "DrvInt_18F87J10.o" "DrvKey.o" "DrvLoad.o" "DrvPri_BD2_2880.o" "DrvRtc_M41T94.o" "DrvSound.o" "DrvSpi.o" "DrvSsp_18F87J10.o" "DrvTimer_18F87J10.o" "DrvPre_MCP8830.o" "DrvPower.o" "DrvIrda.o" "SysGraphic.o" "DrvMmc.o" "DrvLcd_MID184_310.o" "mem-ffs.o" "mem-mmcsd.o" /u_CRUNTIME /u_EXTENDEDMODE /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /z__MPLAB_DEBUGGER_ICD3=1 /z__ICD2RAM=1 /m"MDX-P600 BootLoader.map" /w /o"MDX-P600 BootLoader.cof"

Font6x8.o : Font6x8.c Font6x8.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Font6x8.c" -fo="Font6x8.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Main.o : Main.c pic18f87J10.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdio.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdarg.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stddef.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/string.h MplabC18.h Pic18f87J10.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvSpi.h MpLabC18.h Drivers/DrvSound.h Drivers/DrvFlash_M25P16.h Drivers/DrvEeprom_25AA320.h Drivers/DrvRtc_M41T94.h Drivers/DrvLcd_MID184_310.h Drivers/DrvSsp_18F87J10.h Drivers/DrvUsart_18F87J10.h Drivers/DrvInt_18F87J10.h Font6x8.h Drivers/DrvLoad.h Drivers/DrvGain.h Drivers/DrvKey.h Drivers/DrvTimer_18F87J10.h Drivers/DrvAdc_18F87J10.h Drivers/DrvCca.h Drivers/DrvPri_BD2_2880.h Drivers/DrvMMC.h SDCard/mem-ffs.h SDCard/mem-mmcsd.h bootload.h p18f87J10.h ChkSCod.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Main.c" -fo="Main.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

MdxP600.o : MdxP600.c p18f87J10.h MpLabC18.h Pic18f87J10.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "MdxP600.c" -fo="MdxP600.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

ChkSCod.o : ChkSCod.c ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdlib.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/string.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stddef.h pic18f87J10.h MpLabC18.h Pic18f87J10.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h bootload.h p18f87J10.h MplabC18.h SDCard/mem-ffs.h Drivers/DrvTimer_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "ChkSCod.c" -fo="ChkSCod.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

BootLoad.o : BootLoad.c pic18f87J10.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdio.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdarg.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stddef.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/string.h MpLabC18.h Pic18f87J10.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h BootLoad.h p18f87J10.h MplabC18.h SDCard/mem-ffs.h Drivers/DrvTimer_18F87J10.h Drivers/DrvSpi.h Drivers/DrvSound.h Drivers/DrvFlash_M25P16.h Drivers/DrvEeprom_25AA320.h Drivers/DrvRtc_M41T94.h Drivers/DrvLcd_MID184_310.h Drivers/DrvSsp_18F87J10.h Drivers/DrvUsart_18F87J10.h Drivers/DrvInt_18F87J10.h Font6x8.h Drivers/DrvLoad.h Drivers/DrvGain.h Drivers/DrvKey.h Adc_18F87J10.h Drivers/DrvCca.h Pri_BD2_2880.h Drivers/DrvMMC.h SDCard/mem-mmcsd.h System/SysGraphic.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "BootLoad.c" -fo="BootLoad.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvUsart_18F87J10.o : Drivers/DrvUsart_18F87J10.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvInt_18F87J10.h MplabC18.h Drivers/DrvUsart_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvUsart_18F87J10.c" -fo="DrvUsart_18F87J10.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvAdc_18F87J10.o : Drivers/DrvAdc_18F87J10.c Pic18f87J10.h MplabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvAdc_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvAdc_18F87J10.c" -fo="DrvAdc_18F87J10.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvEeprom_25AA320.o : Drivers/DrvEeprom_25AA320.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvInt_18F87J10.h MplabC18.h Drivers/DrvEeprom_25AA320.h Drivers/DrvSpi.h Drivers/DrvSsp_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvEeprom_25AA320.c" -fo="DrvEeprom_25AA320.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvFlash_M25P16_.o : Drivers/DrvFlash_M25P16_.c Pic18f87J10.h MplabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvFlash_M25P16.h Drivers/DrvSpi.h MpLabC18.h Drivers/DrvSsp_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvFlash_M25P16_.c" -fo="DrvFlash_M25P16_.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvGain.o : Drivers/DrvGain.c p18f87J10.h MplabC18.h Pic18f87J10.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvGain.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvGain.c" -fo="DrvGain.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvInt_18F87J10.o : Drivers/DrvInt_18F87J10.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h BootLoad.h p18f87J10.h MplabC18.h SDCard/mem-ffs.h Drivers/DrvTimer_18F87J10.h Drivers/DrvInt_18F87J10.h Drivers/DrvPri_BD2_2880.h Drivers/DrvUsart_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvInt_18F87J10.c" -fo="DrvInt_18F87J10.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvKey.o : Drivers/DrvKey.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvKey.h Drivers/DrvSound.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvKey.c" -fo="DrvKey.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvLoad.o : Drivers/DrvLoad.c Pic18f87J10.h MplabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvLoad.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvLoad.c" -fo="DrvLoad.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvPri_BD2_2880.o : Drivers/DrvPri_BD2_2880.c Pic18f87J10.h MplabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvInt_18F87J10.h Drivers/DrvPri_BD2_2880.h MpLabC18.h Drivers/DrvTimer_18F87J10.h Drivers/DrvUsart_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvPri_BD2_2880.c" -fo="DrvPri_BD2_2880.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvRtc_M41T94.o : Drivers/DrvRtc_M41T94.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvRtc_M41T94.h MplabC18.h Drivers/DrvSpi.h Drivers/DrvSsp_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvRtc_M41T94.c" -fo="DrvRtc_M41T94.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvSound.o : Drivers/DrvSound.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvSound.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvSound.c" -fo="DrvSound.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvSpi.o : Drivers/DrvSpi.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvSpi.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvSpi.c" -fo="DrvSpi.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvSsp_18F87J10.o : Drivers/DrvSsp_18F87J10.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvSsp_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvSsp_18F87J10.c" -fo="DrvSsp_18F87J10.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvTimer_18F87J10.o : Drivers/DrvTimer_18F87J10.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvCca.h MplabC18.h Drivers/DrvInt_18F87J10.h Drivers/DrvIrda.h Drivers/DrvKey.h Drivers/DrvPower.h Drivers/DrvPre_MCP8830.h Drivers/DrvPri_BD2_2880.h Drivers/DrvTimer_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvTimer_18F87J10.c" -fo="DrvTimer_18F87J10.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvPre_MCP8830.o : Drivers/DrvPre_MCP8830.c Pic18f87J10.h MplabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvIrda.h MpLabC18.h Drivers/DrvPre_MCP8830.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvPre_MCP8830.c" -fo="DrvPre_MCP8830.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvPower.o : Drivers/DrvPower.c Pic18f87J10.h MplabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvPower.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvPower.c" -fo="DrvPower.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvIrda.o : Drivers/DrvIrda.c Pic18f87J10.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h MplabC18.h MdxP600.h Drivers/DrvIrda.h MpLabC18.h Drivers/DrvInt_18F87J10.h Drivers/DrvTimer_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvIrda.c" -fo="DrvIrda.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

SysGraphic.o : System/SysGraphic.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvLcd_MID184_310.h System/SysGraphic.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "System\SysGraphic.c" -fo="SysGraphic.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvMmc.o : Drivers/DrvMmc.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvMmc.h Drivers/DrvSpi.h Drivers/DrvSsp_18F87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvMmc.c" -fo="DrvMmc.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DrvLcd_MID184_310.o : Drivers/DrvLcd_MID184_310.c Pic18f87J10.h MpLabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h Drivers/DrvLcd_MID184_310.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "Drivers\DrvLcd_MID184_310.c" -fo="DrvLcd_MID184_310.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

mem-ffs.o : SDCard/mem-ffs.c SDCard/mem-ffs.h SDCard/mem-ffs.c MpLabC18.h Pic18f87J10.h Drivers/DrvTimer_18F87J10.h MplabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h SDCard/mem-mmcsd.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdio.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdarg.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stddef.h Drivers/DrvSpi.h Drivers/DrvLcd_MID184_310.h Drivers/DrvRtc_M41T94.h System/SysGraphic.h BootLoad.h p18f87J10.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "SDCard\mem-ffs.c" -fo="mem-ffs.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

mem-mmcsd.o : SDCard/mem-mmcsd.c SDCard/mem-mmcsd.h SDCard/mem-mmcsd.c MpLabC18.h Pic18f87J10.h SDCard/mem-ffs.h Drivers/DrvTimer_18F87J10.h MplabC18.h MdxP600.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/delays.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/p18cxxx.h p18f87j10.h SDCard/MMCmbr.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdlib.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/string.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stddef.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdio.h ../../../Program\ Files/Microchip/mplabc18/v3.42/h/stdarg.h Drivers/DrvSpi.h Drivers/DrvLcd_MID184_310.h BootLoad.h p18f87J10.h Drivers/DrvMMC.h
	$(CC) -p=18F87J10 /i"C:\MDXP600\Source\Bootloader" -I"C:\MDXP600\Source\Bootloader\System" -I"C:\MDXP600\Source\Bootloader\Drivers" -I"C:\MDXP600\Source\Bootloader\SDCard" "SDCard\mem-mmcsd.c" -fo="mem-mmcsd.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 --extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Font6x8.o" "Main.o" "MdxP600.o" "ChkSCod.o" "BootLoad.o" "DrvUsart_18F87J10.o" "DrvAdc_18F87J10.o" "DrvEeprom_25AA320.o" "DrvFlash_M25P16_.o" "DrvGain.o" "DrvInt_18F87J10.o" "DrvKey.o" "DrvLoad.o" "DrvPri_BD2_2880.o" "DrvRtc_M41T94.o" "DrvSound.o" "DrvSpi.o" "DrvSsp_18F87J10.o" "DrvTimer_18F87J10.o" "DrvPre_MCP8830.o" "DrvPower.o" "DrvIrda.o" "SysGraphic.o" "DrvMmc.o" "DrvLcd_MID184_310.o" "mem-ffs.o" "mem-mmcsd.o" "MDX-P600 BootLoader.cof" "MDX-P600 BootLoader.hex" "MDX-P600 BootLoader.map"

