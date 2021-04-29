;A program that prints the numbers between 1000 and 1999 that divided by 11 give 5 as the remainder.

.686
.model flat, stdcall
option casemap :none

include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib
include \masm32\macros\macros.asm

.data

    divisor DWORD 11

.code
start:
    mov ebx, 1000
    loop1:
    inc ebx
    mov eax, ebx
    xor edx, edx
    div divisor
    cmp edx, 5
    jne doAnything
    printf("%d\n", ebx)
    doAnything:
    cmp ebx, 1999
    je lblOut
    jmp loop1
    lblOut:
    invoke ExitProcess, 0

end start