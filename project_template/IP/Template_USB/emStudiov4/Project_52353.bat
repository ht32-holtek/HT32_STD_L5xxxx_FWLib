@ECHO OFF
SET TARGET_CHIP=HT32L52353
SET PACK_FILE=..\..\..\..\utilities\pack\Holtek.HT32_DFP.latest.pack

start Project_52353.emProject

REM pyocd erase --chip -t %TARGET_CHIP% --pack=%PACK_FILE%
pyocd gdbserver -t %TARGET_CHIP% --pack=%PACK_FILE%