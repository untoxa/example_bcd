@echo off
@set PROJ=bcd_test
@set GBDK=..\..\gbdk\
@set GBDKLIB=%GBDK%lib\small\asxxxx\
@set OBJ=build\
@set SRC=src\

@set CFLAGS=-mgbz80 --no-std-crt0 -Dnonbanked= -I %GBDK%include -I %GBDK%include\asm -I %SRC%include -c

@set LFLAGS=-n -- -z -m -j -k%GBDKLIB%gbz80\ -lgbz80.lib -k%GBDKLIB%gb\ -lgb.lib 
@rem @set LFLAGS=%LFLAGS% -yt2 -yo4 -ya4
@rem @set LFLAGS=%LFLAGS% -yp0x143=0x80
@set LFILES=%GBDKLIB%gb\crt0.o

@set ASMFLAGS=-plosgff -I"libc"

@echo Cleanup...

@if exist %OBJ% rd /s/q %OBJ%
@if exist %PROJ%.gb del %PROJ%.gb
@if exist %PROJ%.sym del %PROJ%.sym
@if exist %PROJ%.map del %PROJ%.map

@if not exist %OBJ% mkdir %OBJ%

@echo COMPILING WITH SDCC4...

sdcc %CFLAGS% %SRC%bcd.c -o %OBJ%bcd.rel
@set LFILES=%LFILES% %OBJ%bcd.rel

sdcc %CFLAGS% %SRC%%PROJ%.c -o %OBJ%%PROJ%.rel

@echo LINKING WITH GBDK...
%GBDK%bin\link-gbz80 %LFLAGS% %PROJ%.gb %LFILES% %OBJ%%PROJ%.rel 

@echo DONE!