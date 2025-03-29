
%include 'mio.inc'
%include 'iostr.inc'
%include 'strings.inc'

global ReadBin, ReadHex, ReadInt, WriteBin, WriteHex, WriteInt

section .text

ReadInt:
push ebx
push ecx
push edx
push edi
push esi

mov esi,strs
mov ecx,257
       
call ReadLnStr  ;read chars


mov al,[esi]     

.kezd:
xor ebx,ebx
xor eax,eax
mov ecx,1     ;ecx indicates the sign of the number

mov al,[esi]
cmp al,0   ;if we don't enter anything, it is also considered invalid
je .rossz
cmp al,'-'  ;if the first character is '-', then set ecx to -1

jne .plusz ;check if there's a '+' character at the beginning if there is no '-'


mov ecx,-1

.egyke:

inc esi
mov al,[esi]
cmp al,0     ;because entering only a '-' or '+' character is also invalid

je .rossz 

.for:
mov al,[esi]

cmp al,0
je .vege

cmp al,'0'
jl .rossz

cmp al,'9'
jg .rossz

imul ebx,10
jo .rossz   ;overflow check

sub al,'0'
add ebx, eax
jo .rossz

inc esi
jmp .for


.rossz:
stc  ;set carry to 1
pop esi
pop edi
pop edx
pop ecx
pop ebx
ret

.vege:
imul ebx,ecx  ;at the end, I apply the sign and, just to be safe, check for overflow here as well

jo .rossz
mov eax,ebx  ;eax=value
clc  ;if the characters are valid, I clear the carry flag with clc (set to 0), meaning there’s no error

pop esi
pop edi
pop edx
pop ecx
pop ebx
ret

.plusz:
cmp al,'+' ;if yes, I move on and do not consider it an error

je .egyke
jmp .for ;if it's not '+', then I don't move on, but instead continue the loop and check the current element to see what it is






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
WriteInt:

pusha

cmp eax,0   ;if eax = 0, then I print it and finish the writing process

je .irveg


 mov ecx, eax ;first, I save the value in ecx because if a '-' sign needs to be printed, the value in eax will change

  push -1        ;this -1 indicates the end of the stack

  mov ebx,10
  cmp eax,0    ;I check whether eax is less than 0, this determines whether the number is negative or not
  jge .eleje  ; jump if greater or equal (i.e., number is not negative)

  mov   eax, '-'   ;if the number is negative, print the '-' sign

  imul ecx,-1     ;make it positive

  call   mio_writechar  
  mov eax,ecx   
  .eleje:  
   cmp eax,0   ;if it's 0, I can print it later from the stack

   je .ir        
   cdq
   idiv ebx    ;this is where I push the elements onto the stack

   push edx
   jmp .eleje

  .ir:
   pop edx
   cmp edx, -1           ;here I pop the values until -1 and print them

   je .vege
   mov eax,edx
   add eax,'0'
   call mio_writechar
   jmp .ir

  .vege:
   popa
   ret

  .irveg:
  mov eax,'0'    ;this is for the case where the number starts as 0

  call mio_writechar
  popa
  ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ReadBin:
push ebx
push ecx
push edx
push edi
push esi

mov esi,strs
mov ecx,257
       
call ReadLnStr  ;I read the character string


mov ecx,[esi]
cmp ecx,0     ;since pressing enter alone is invalid, if it's empty, I cannot decrement ecx, otherwise it would become -1

je .rossz


xor eax,eax
xor edi,edi
xor edx,edx
xor ebx,ebx


.for:
mov al,[esi]

cmp al,0
je .vege

cmp al,'0'   ;if it's less than 0, it's invalid

jl .rossz

cmp al,'1' ;if it's greater than 1 in ASCII value, it's invalid

jg .rossz


.tov:
mov edi,eax    ;I perform the calculation for the given part in edi, and the result is in ebx, ecx is the counter, and I read characters into eax

sub edi,'0'
shl ebx,1
jc .rossz    ;carry check, since I am performing a shift operation here


add ebx,edi

inc esi
jmp .for


.rossz:
stc        ;set carry to 1
pop esi
pop edi
pop edx
pop ecx
pop ebx
ret

.vege:
mov eax,ebx  ;eax=value
clc          ;if the characters are valid, I clear the carry flag (clc), setting it to 0, meaning no error

pop esi
pop edi
pop edx
pop ecx
pop ebx
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

WriteBin:
pusha         ;save


push -1      ;I know this is the end of the binary number

xor ecx,ecx
mov edi,0


.for:
xor ebx,ebx
cmp ecx,32    ;I go 32 times, since that's the number of bits

je .iro
mov ebx,eax
mov edx, 01h   ;I mask the last bit

and ebx,edx
shr eax,1
push ebx
inc ecx
jmp .for

.iro:
cmp edi,4       ;edi is used as a counter due to the tagging

je .space
pop eax             ;I can print it, I know how

cmp eax,-1
je .vege
add eax,'0'         ;I convert it to a character

call mio_writechar
inc edi
jmp .iro


.vege:
popa
ret

.space:
mov al,' '
call mio_writechar   ;I divide it into groups of 4

mov edi,0
jmp .iro


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ReadHex:
push ebx
push ecx
push edx
push edi
push esi
mov esi,strs
mov ecx,257
       
call ReadLnStr  ;I read the character string


mov ecx,[esi]
cmp ecx,0     ;since pressing only enter is invalid, if it's empty, I cannot decrement ecx, otherwise it would become -1

je .rossz

xor edx,edx
xor ebx,ebx
xor eax,eax


.for:
  
  mov al,[esi]

  cmp al,0
  je .vege

  

  cmp eax,'0'   ;I check each case separately, and add the corresponding character if it matches; if no match is found, the character is invalid

  jne .t1
  mov edi,eax
  shl ebx,4    ;shifting
  jc .rossz
  sub edi,'0'    ;transform to int
  add ebx,edi    ;add
  inc  esi
  jmp .for
  ;;;;;;
                      ;here, I did the same for the others, one by one, as I did for the previous one


  .t1:
  cmp eax, '1'
  jne .t2
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  .t2:
  cmp eax, '2'
  jne .t3
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  .t3:
  cmp eax, '3'
  jne .t4
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  .t4:
  cmp eax, '4'
  jne .t5
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  .t5:
  cmp eax, '5'
  jne .t6
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  .t6:
  cmp eax, '6'
  jne .t7
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  .t7:
  cmp eax, '7'
  jne .t8
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  .t8:
  cmp eax, '8'
  jne .t9
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  .t9:
  cmp eax, '9'
  jne .t10
  mov edi,eax
  shl ebx,4
  jc .rossz
  sub edi,'0'
  add ebx,edi
  inc  esi
  jmp .for

  
  .t10:
  cmp eax, 'A'
  je .ad10
  cmp eax,'a'
  jne .t11
 .ad10:
  mov edi,10
  shl ebx,4
  jc .rossz
  add ebx,edi
  inc  esi
  jmp .for

  .t11:
  cmp eax, 'B'
  je .ad11
  cmp eax,'b'
  jne .t12
 .ad11:
  mov edi,11
  shl ebx,4
  jc .rossz
  add ebx,edi
  inc  esi
  jmp .for

  .t12:
  cmp eax, 'C'
  je .ad12
  cmp eax,'c'
  jne .t13
 .ad12:
  mov edi,12
  shl ebx,4
  jc .rossz
  add ebx,edi
  inc  esi
  jmp .for

  .t13:
  cmp eax, 'D'
  je .ad13
  cmp eax,'d'
  jne .t14
 .ad13:
  mov edi,13
  shl ebx,4
  jc .rossz
  add ebx,edi
  inc  esi
  jmp .for

  .t14:
  cmp eax, 'E'
  je .ad14
  cmp eax,'e'
  jne .t15
 .ad14:
  mov edi,14
  shl ebx,4
  jc .rossz
  add ebx,edi
  inc  esi
  jmp .for

  .t15:
  cmp eax, 'F'
  je .ad15
  cmp eax,'f'
  jne .rossz
 .ad15:
  mov edi,15
  shl ebx,4
  jc .rossz
  add ebx,edi
  inc  esi
  jmp .for





.rossz:
pop esi
pop edi
pop edx
pop ecx
pop ebx
ret

.vege:
mov eax,ebx  ;eax=value
clc          ;if the characters are valid, I clear the carry flag (clc), setting it to 0, meaning no error (just for safety)

pop esi
pop edi
pop edx
pop ecx
pop ebx
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



WriteHex:
pusha            ;save registers
mov esi,prefix
mov ecx,256
call WriteStr

push -1          ;here the same principle applies with the stack, but here I push the remainders

mov ecx,8        ;ecx indicates how many times to perform the operations, since we are working with 8 bits, ecx = 8

.csinal:
cmp ecx,0
je .kiir
mov ebx,eax
mov edx,0Fh      ;edx= 0000 0000 0000 0000 0000 0000 0000 1111
AND ebx,edx
push ebx
SHR eax,4
sub ecx,1
jmp .csinal



.kiir:       ;now comes the actual output, with many jumps


pop eax
cmp eax, -1
je .vege

cmp eax, 10
je .tiz

cmp eax, 11
je .tizenegy

cmp eax, 12
je .tizenketto

cmp eax, 13
je .tizenharom

cmp eax, 14
je .tizennegy

cmp eax, 15
je .tizenot
                  ;if the number is less than 10, simply print it; if it's between 10 and 15, print the corresponding letter

add eax,'0'
call mio_writechar
jmp .kiir

.tiz:
mov eax,'A'
call mio_writechar
jmp .kiir

.tizenegy:
mov eax,'B'
call mio_writechar
jmp .kiir

.tizenketto:
mov eax,'C'
call mio_writechar
jmp .kiir

.tizenharom:
mov eax,'D'
call mio_writechar
jmp .kiir

.tizennegy:
mov eax,'E'
call mio_writechar
jmp .kiir

.tizenot:
mov eax,'F'
call mio_writechar
jmp .kiir

.vege:
  popa
  ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



section .data
prefix db '0x',0

section .bss
strs resb 257
