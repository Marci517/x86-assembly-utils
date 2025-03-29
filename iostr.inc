
%include 'mio.inc'

global ReadStr, ReadLnStr, WriteStr, WriteLnStr, NewLine

section .text

ReadStr:
pusha
mov ebx,0 ;ebx is used to "step through" the memory address

mov edx,0
.be:
call mio_readchar
call mio_writechar
cmp al,13   ;if enter then end
je .vege
cmp al, 8   ;if it's a backspace, check which case it is

je .megnez

inc edx
cmp edx,ecx
jg .be
mov [esi+ebx],al
inc ebx
jmp .be

.vege:
mov dl,0
mov [esi+ebx],dl
popa   ;save
ret

.megnez:
cmp edx,0  ;if there's nothing to delete, simply go back to reading input

je .be

cmp edx,ecx  
jle .csinal   ;if there is a character and it is allowed


dec edx
mov al,' '       ;if the character is not allowed, delete it from the screen and only decrement the allowed characters counter

call mio_writechar
mov al,8
call mio_writechar
jmp .be

.csinal:
mov al,' '    ;then it deletes the character and moves the cursor back

call mio_writechar
mov al,8
call mio_writechar
dec ebx   ;decrease the pointer by one

dec edx   ;also decrease the number of allowed characters

jmp .be




;//////////////////////////////////////////////////////////////////
WriteStr:
pusha
.ki:
mov al,[esi]
cmp al,0        ;keep writing until a null (0) character is received

je .vege
call mio_writechar
inc esi
jmp .ki

.vege:
popa
ret

;////////////////////////////////////////////////


ReadLnStr:
pusha
mov ebx,0 ;ebx is used to step through the memory address

mov edx,0
.be:
call mio_readchar
call mio_writechar
cmp al,13   ;if enter then end
je .vege
cmp al, 8   ;if it's a backspace, check which case applies

je .megnez

inc edx
cmp edx,ecx
jg .be
mov [esi+ebx],al
inc ebx
jmp .be

.vege:
mov dl,0
mov [esi+ebx],dl
mov al,13
call mio_writechar    ;move to a new line

mov al,10
call mio_writechar
popa
ret

.megnez:
cmp edx,0  ;if there’s nothing to delete, simply return to reading input

je .be

cmp edx,ecx  
jle .csinal   ;if there is a character and it is allowed


dec edx
mov al,' '       ;if the character is not allowed, remove it from the screen and only decrement the allowed characters counter

call mio_writechar
mov al,8
call mio_writechar
jmp .be

.csinal:
mov al,' '    ;then it deletes the character and moves the cursor backward

call mio_writechar
mov al,8
call mio_writechar
dec ebx   ;decrease the pointer by one

dec edx   ;also decrease the number of allowed characters

jmp .be




;//////////////////////////////////////////////////////////////////
WriteLnStr:
pusha
.ki:
mov al,[esi]
cmp al,0        ;keep printing until a null (0) character is received

je .vege
call mio_writechar
inc esi
jmp .ki

.vege:
mov al,13
call mio_writechar
mov al,10              ;move to a new line

call mio_writechar
popa
ret

;////////////////////////////////////////////////

NewLine:
pusha
mov al,13
call mio_writechar
mov al,10               ;move to a new line

call mio_writechar
popa
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
