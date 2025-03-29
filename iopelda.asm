
;reads a signed 32-bit integer in decimal;
;prints the input value in decimal as a signed integer, its two's complement representation in hexadecimal and binary;
;reads a 32-bit hexadecimal number;
;prints the input value in decimal as a signed integer, its two's complement representation in hexadecimal and binary;
;reads a 32-bit binary number;
;prints the input value in decimal as a signed integer, its two's complement representation in hexadecimal and binary;
;prints the sum of the three input values in decimal as a signed integer, its two's complement representation in hexadecimal and binary;
;performs the previous steps for 64-bit values as well.




%include 'mio.inc'
;%include 'iostr.inc'
;%include 'strings.inc'
%include 'ionum.inc'
global main

section .text


main:



.hivas1:                  ;read and print the decimal value in three different formats

mov esi,fdec
mov ecx,256
call WriteStr
call NewLine

call ReadInt   ;read
jc .kiirhiba1

mov [szam1],eax    ;I store the decimal numbers in num1, num2, and num3 so that I can add them later

mov esi,deci
mov ecx,256
call WriteStr
call WriteInt
call NewLine

mov esi,hexi
mov ecx,256
call WriteStr
call WriteHex
call NewLine

mov esi,bini
mov ecx,256
call WriteStr
call WriteBin
call NewLine
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


.hivas2:                             ;read and print the hexadecimal value in three different formats

mov esi,fhex
mov ecx,256
call WriteStr
call NewLine

call ReadHex
jc .kiirhiba2

mov [szam2],eax

mov esi,deci
mov ecx,256
call WriteStr
call WriteInt
call NewLine

mov esi,hexi
mov ecx,256
call WriteStr
call WriteHex
call NewLine

mov esi,bini
mov ecx,256
call WriteStr
call WriteBin
call NewLine


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.hivas3:
mov esi,fbin                              ;read and print the binary value in three different formats

mov ecx,256
call WriteStr
call NewLine

call ReadBin
jc .kiirhiba3

mov [szam3],eax

mov esi,deci
mov ecx,256
call WriteStr
call WriteInt
call NewLine

mov esi,hexi
mov ecx,256
call WriteStr
call WriteHex
call NewLine

mov esi,bini
mov ecx,256
call WriteStr
call WriteBin
call NewLine




mov eax,[szam1]        ;add the three numbers together

mov ebx,[szam2]
mov ecx,[szam3]
add eax,ebx
add eax,ecx

mov esi, ossz
mov ecx,256
call WriteLnStr


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.hivas4:                   ;sum of the three numbers: print it in three different formats


mov esi,deci
mov ecx,256
call WriteStr
call WriteInt
call NewLine

mov esi,hexi
mov ecx,256
call WriteStr
call WriteHex
call NewLine

mov esi,bini
mov ecx,256
call WriteStr
call WriteBin
call NewLine



ret



.kiirhiba1:
mov esi,hiba   ;in case of an error, I print "error" and return to the caller

mov ecx,256
call WriteStr
call NewLine
jmp .hivas1

.kiirhiba2:
mov esi,hiba
mov ecx,256
call WriteStr
call NewLine
jmp .hivas2

.kiirhiba3:
mov esi,hiba
mov ecx,256
call WriteStr
call NewLine
jmp .hivas3

.kiirhiba4:
mov esi,hiba
mov ecx,256
call WriteStr
call NewLine
ret





section .data
  fdec db 'Enter a decimal number: ', 0
  fhex db 'Enter a hexa number: ', 0
  fbin db 'Enter a binary number: ', 0
  ossz db 'The sum of the three numbers in 3 formats: ',0
  deci db 'Decimal: ' ,0
  hexi db 'Hexa: ' ,0
  bini db 'Binary: ' ,0
  hiba db 'Error', 0
  


section .bss
szam1 resd 1
szam2 resd 1
szam3 resd 1
