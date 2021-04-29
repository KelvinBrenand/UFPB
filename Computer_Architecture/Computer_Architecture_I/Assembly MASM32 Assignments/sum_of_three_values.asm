;A program that adds 3 values and prints the sum.

.686
.model flat, stdcall
option casemap :none

include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib
include \masm32\macros\macros.asm

.data

    a DWORD 0
    b DWORD 69
    d DWORD 420
    
.code
start:

    ;a = b + d + 100
    mov eax, 0
    add eax, b
    add eax, d
    add eax, 100
    add a, eax
    printf("a: %d\n", a)
    invoke ExitProcess, 0

end start

