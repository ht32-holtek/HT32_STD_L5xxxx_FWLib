@ECHO OFF
SET TARGET_CHIP=HT50L3200U
SET PACK_FILE=..\..\..\..\utilities\pack\Holtek.HT32_DFP.latest.pack

start Project_3200U.emProject

REM pyocd erase --chip -t %TARGET_CHIP% --pack=%PACK_FILE%
pyocd gdbserver -t %TARGET_CHIP% --pack=%PACK_FILE%