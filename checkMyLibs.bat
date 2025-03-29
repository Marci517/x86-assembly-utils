@echo off
echo === Starting.. ===

nasm.exe -f win32 iostr.asm -o iostr.obj
nasm.exe -f win32 strings.asm -o strings.obj
nasm.exe -f win32 ionum.asm -o ionum.obj

echo === Done ===
pause