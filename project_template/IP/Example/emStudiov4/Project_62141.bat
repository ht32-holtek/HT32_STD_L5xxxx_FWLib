@ECHO OFF
SET TARGET_CHIP=HT32L62141
SET PACK_FILE=..\..\..\..\utilities\pack\Holtek.HT32_DFP.latest.pack

start Project_62141.emProject

REM pyocd erase --chip -t %TARGET_CHIP% --pack=%PACK_FILE%
pyocd gdbserver -t %TARGET_CHIP% --pack=%PACK_FILE%