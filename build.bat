@echo off
echo === Starting.. ===

nasm.exe -f win32 iopelda.asm -o iopelda.obj
nasm.exe -f win32 strpelda.asm -o strpelda.obj

echo === Links ===
nlink iopelda.obj -lmio -o iopelda.exe
nlink strpelda.obj -lmio -o strpelda.exe

echo === Done ===
pause
