@ECHO OFF
SET TARGET_CHIP=HT32L64041
SET PACK_FILE=..\..\..\..\utilities\pack\Holtek.HT32_DFP.latest.pack

start Project_64041.emProject

REM pyocd erase --chip -t %TARGET_CHIP% --pack=%PACK_FILE%
pyocd gdbserver -t %TARGET_CHIP% --pack=%PACK_FILE%