@echo off
REM ############################
REM ENVIRONMENT VARIABLES
REM ############################

REM keep track of current root directory
SET ROOT=%cd%

REM set compiler and utility paths
SET WATCOM=D:\WATCOM
SET TASM=D:\Projects\TASM
SET MASM=D:\Projects\utils\utils
SET UTILS=D:\Projects\utils\utils

REM set windows dir to be able to use any needed win commands
SET PATH=%windir%;%windir%\System32

REM set path variable so these are accessable
SET PATH=%WATCOM%\BINNT;%WATCOM%\BIN;%WATCOM%\BINW;%PATH%

SET PATH=%TASM%\BIN;%PATH%

REM set include paths
SET INCLUDE=%WATCOM%\H\NT;%WATCOM%\H

REM set library include paths
SET WIN32LIB=%ROOT%\WIN32LIB
SET WINVQ=%ROOT%\WINVQ

REM ############################
REM BUILD DIR SETUP
REM ############################

REM set build output dir
SET BLDDIR=%ROOT%\BUILD

REM make needed dirs as wmake doesn't make them
mkdir BUILD

mkdir BUILD\TD
mkdir BUILD\TD\OBJ

mkdir BUILD\RA
mkdir BUILD\RA\OBJ

mkdir BUILD\WIN32LIB
mkdir BUILD\WIN32LIB\OBJ

mkdir BUILD\WINVQ
mkdir BUILD\WINVQ\VQM32
mkdir BUILD\WINVQ\VQM32\OBJ
mkdir BUILD\WINVQ\VQA32
mkdir BUILD\WINVQ\VQA32\OBJ

mkdir BUILD\IPX
mkdir BUILD\IPX\OBJ

REM ############################
REM COMPILATION
REM ############################

REM ############################
REM COMPILE WWIPX
REM ############################

REM ############################
REM COMPILE WinVQ
REM ############################
cd WINVQ

cd VQM32
wmake
cd ..

cd VQA32
wmake
cd ..

cd ..

REM ############################
REM COMPILE Win32Lib
REM ############################
cd WIN32LIB
wmake
cd ..

REM compile TD

REM compile RA

pause