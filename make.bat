@echo off
@set PROJ=bcd_test
@set GBDK=..\..\gbdk\
@set GBDKLIB=%GBDK%lib\small\asxxxx\
@set OBJ=build\
@set SRC=src\

@set CFLAGS=-mgbz80 --no-std-crt0 -I %GBDK%include -I %GBDK%include\asm -I %SRC%include -c


@set LNAMES=-g .OAM=0xC000 -g .STACK=0xE000 -g .refresh_OAM=0xFF80 -b _DATA=0xc0a0 -b _CODE=0x0200
@set LFLAGS=-n -m -w -i -k %GBDKLIB%\gbz80\ -l gbz80.lib -k %GBDKLIB%\gb\ -l gb.lib %LNAMES%
@rem @set LFLAGS=%LFLAGS% -yt2 -yo4 -ya4
@rem @set LFLAGS=%LFLAGS% -yp0x143=0x80
@set LFILES=%GBDKLIB%gb\crt0.o

@set ASMFLAGS=-plosgff -I%GBDKLIB%

@set BINFLAGS=


@echo Cleanup...

@if exist %OBJ% rd /s/q %OBJ%
@if exist %PROJ%.gb del %PROJ%.gb
@if exist %PROJ%.sym del %PROJ%.sym
@if exist %PROJ%.map del %PROJ%.map

@if not exist %OBJ% mkdir %OBJ%

@echo COMPILING WITH SDCC4...

sdcc %CFLAGS% %SRC%bcd.c -o %OBJ%bcd.rel
set LFILES=%LFILES% %OBJ%bcd.rel

sdcc %CFLAGS% %SRC%%PROJ%.c -o %OBJ%%PROJ%.rel
set LFILES=%LFILES% %OBJ%%PROJ%.rel

@echo LINKING...
sdldgb %LFLAGS% %PROJ%.ihx %LFILES%

@echo MAKING BIN...
makebin -Z %BINFLAGS% %PROJ%.ihx %PROJ%.gb

@echo DONE!
