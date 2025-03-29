

;print its length;
;print its compressed form;
;print its compressed form converted to lowercase;
;after displaying an appropriate message, read a second string;
;print its length;
;print its compressed form;
;print its compressed form converted to uppercase;
;create a new string in memory: append the lowercase version of the second string to the uppercase version of the first string;
;print the newly created string;
;print the length of the newly created string;
;terminate the program.



%include 'mio.inc'
;%include 'iostr.inc'
;%include 'strings.inc'
%include 'ionum.inc'

global main

section .text




main:

xor eax,eax

mov esi,feladat
mov ecx, 256
call WriteStr
call NewLine

mov esi,stra
mov ecx,256        ;first string read
call ReadLnStr

mov esi,stra
call StrLen      ;print first strings length

call WriteInt
call NewLine

mov edi,strac
mov esi,stra
call StrCompact   ;print compact form
mov esi,strac
call WriteLnStr

mov esi,strac
call StrLower    ;print compact form with lowercase
mov esi,strac
call WriteLnStr




mov esi,feladat2
mov ecx,256
call WriteStr
call NewLine

mov esi,strb
mov ecx,256        ;second string read
call ReadLnStr

mov esi,strb
call StrLen      ;print second strings length

call WriteInt
call NewLine

mov edi,strbc
mov esi,strb
call StrCompact   ;print compact form
mov esi,strac
mov esi,strbc
call WriteLnStr

mov esi,strbc
call StrUpper    ;print compact form with lowercase
mov esi,strbc
call WriteLnStr

mov esi,stra
call StrUpper     ;the first string to uppercase
mov esi,strb      
call StrLower    ;second string to lowercase
mov edi,stra
mov esi,strb
call StrCat     ;concatenate them using edi, so the result will be stored in stra

mov esi,stra
call WriteLnStr  ;print concatenated string
mov esi,stra
call StrLen

call WriteInt
call NewLine          
;print concatenated strings length

   




ret

section .data
   feladat db 'Enter a string: ', 0
   feladat2 db 'Enter an another string: ', 0



  section .bss
  stra resb 257
  strb resb 257
  strac resb 257
  strbc resb 257
  