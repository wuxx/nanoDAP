@echo off
if "%PROCESSOR_ARCHITECTURE%"=="x86" goto X86
dpinst_amd64.exe
goto END
:X86
dpinst_x86.exe
:END
