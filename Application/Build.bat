@REM  MDXP600Build.bat - A Batch script that will build the MDXP600 bootloader
@REM  09-13-07   RJ    Developed
@REM

color 1F

@ECHO OFF
SET COMP="C:\MCC18\bin\mcc18.exe"
SET LINKR="C:\MCC18\bin\mplink.exe"
SET LIBR="C:\MCC18\lib"
SET HFILES="C:\MCC18\h"
SET LNKFILE="18f67j10i_e.lkr"

SET PROCESSOR=-p=18F67J10
SET COMP_ARG_OPT=--extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-
SET DEFINES=

SET APP_DIR="C:\CBT\CBT-300 bootloader\Application"
SET DRV_DIR="C:\CBT\CBT-300 bootloader\Drivers"
SET SYS_DIR="C:\CBT\CBT-300 bootloader\System"

SET INCLUDE=

SET MAPFILE="CBT-300Bootloader.map"
SET COFFILE="CBT-300Bootloader.cof"
SET HEXFILE="CBT-300Bootloader.hex"
SET S19FILE=
SET OUTPUTFILE="192-160002C.hex"

SET APPFILES= Font6x8 Main ChkSCod BootLoad AppData AppBluetooth

SET DRVFILES= DrvMdxP600 DrvUsart_18F67J10 DrvInt_18F67J10 DrvPan1026
SET DRVFILES=%DRVFILES% DrvEeprom_25AA320 DrvKey DrvLCD_OPTO1140GG DrvLoad
SET DRVFILES=%DRVFILES% DrvSsp_18F67J10 DrvTimer_18F67J10 DrvConfigBoard

SET SYSFILES= SysDisplay SysBluetooth


CD %APP_DIR%
@ECHO Delete the error files
del *.err

@ECHO Delete the hex output file
if exist OUTPUTFILE del OUTPUTFILE

@ECHO Delete the hex output file
if exist HEXFILE del HEXFILE

@ECHO Delete the s19 output file
if exist S19FILE del S19FILE

@ECHO Delete the application object file
CD %APP_DIR%
FOR %%x in (%APPFILES%) DO del %%x.o

@ECHO Delete the driver object file
CD %DRV_DIR%
FOR %%x in (%DRVFILES%) DO del %%x.o

@ECHO Delete the System object file
CD %SYS_DIR%
FOR %%x in (%SYSFILES%) DO del %%x.o


@ECHO Compile files
@ECHO ON
CD %DRV_DIR%
FOR %%x in (%DRVFILES%) DO %COMP% %PROCESSOR% -I%HFILES% -I%APP_DIR% -I%DRV_DIR% -I%SYS_DIR% %%x.c -fo=%%x.o %DEFINES% %COMP_ARG_OPT%
@ECHO OFF
if exist *.err goto COMP_ERRS

@ECHO ON
CD %APP_DIR%
FOR %%x in (%APPFILES%) DO %COMP% %PROCESSOR% -I%HFILES% -I%APP_DIR% -I%DRV_DIR% -I%SYS_DIR% %%x.c -fo=%%x.o %DEFINES% %COMP_ARG_OPT%
@ECHO OFF
if exist *.err goto COMP_ERRS

@ECHO ON
CD %SYS_DIR%
FOR %%x in (%SYSFILES%) DO %COMP% %PROCESSOR% -I%HFILES% -I%APP_DIR% -I%DRV_DIR% -I%SYS_DIR% %%x.c -fo=%%x.o %DEFINES% %COMP_ARG_OPT%
@ECHO OFF
if exist *.err goto COMP_ERRS


CD %APP_DIR%

@REM Link
SET LINKFILES=Font6x8.o Main.o ChkSCod.o BootLoad.o AppData.o AppBluetooth.o
SET LINKFILES=%LINKFILES% DrvEeprom_25AA320.o DrvUsart_18F67J10.o DrvMdxP600.o DrvPan1026.o
SET LINKFILES=%LINKFILES% DrvInt_18F67J10.o DrvKey.o DrvLCD_OPTO1140GG.o DrvLoad.o
SET LINKFILES=%LINKFILES% DrvSsp_18F67J10.o DrvTimer_18F67J10.o DrvConfigBoard.o
SET LINKFILES=%LINKFILES% SysDisplay.o SysBluetooth.o
@ECHO ON
%LINKR% %LNKFILE% %LINKFILES% /l%LIBR% /l%APP_DIR% /l%DRV_DIR% /l%SYS_DIR% /m%MAPFILE% /o%COFFILE%

copy %HEXFILE% %OUTPUTFILE%

@ECHO OFF
goto EXIT

:COMP_ERRS

color 4F

@ECHO There are Compile errors
FOR %%x in (*.err) DO ECHO %%x

CD %APP_DIR%

:EXIT
pause
