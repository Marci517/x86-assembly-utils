
%include 'mio.inc'

global StrCat, StrCompact, StrLen, StrLower, StrUpper

section .text



StrLen:
push ebx   ;eax is not needed because it is the output parameter

push ecx
push edx   ;save
push esi
push edi


xor ebx, ebx
.szamol:
mov al,[esi]

cmp al,0        ;keep writing until a null (0) character is received

je .vege
inc esi
inc ebx
jmp .szamol

.vege:
mov eax,ebx
pop edi
pop esi
pop edx     ;save
pop ecx
pop ebx


ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

StrCat:
pusha ;ment
.for1:
mov al,[edi]
cmp al,0
je .for2
inc edi
jmp .for1

.for2:   ;currently, the edi pointer is at the binary 0 value, copying starts from there

mov al,[esi]
cmp al,0
je .vege
mov [edi],al
inc esi
inc edi
jmp .for2

.vege:
mov al,0    ;no need to increment the edi pointer, since it always moved first and then stored if valid

mov [edi],al
popa ;save
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
StrLower:
pusha
.for:
mov al,[esi]
cmp al,0
je .vege
cmp al,'A'
jl .tovabb
cmp al,'Z'
jg .tovabb
add al,32   ;this is enough to make its ASCII code match the corresponding lowercase character

mov [esi],al
inc esi
jmp .for


.tovabb:
inc esi
jmp .for

.vege:
popa
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
StrUpper:
pusha
.for:
mov al,[esi]
cmp al,0
je .vege
cmp al,'a'
jl .tovabb
cmp al,'z'
jg .tovabb
sub al,32   ;this is enough to make its ASCII code match the corresponding uppercase character

mov [esi],al
inc esi
jmp .for


.tovabb:
inc esi
jmp .for

.vege:
popa
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
StrCompact:
pusha
.for:
mov al,[esi]
cmp al,0 
je .vege
cmp al,10
je .tovabb
cmp al,9
je .tovabb    ;if the character is not valid, only advance the esi pointer

cmp al,13
je .tovabb
cmp al, ' '
je .tovabb
mov [edi],al   ;if the character is valid, copy it and advance both pointers

inc edi
inc esi
jmp .for


.tovabb:
inc esi
jmp .for

.vege:
mov al,0     ;again, I move the pointer first and then check if the character is valid, so I don't need to increment it now to insert the binary 0

mov [edi],al
popa
ret





