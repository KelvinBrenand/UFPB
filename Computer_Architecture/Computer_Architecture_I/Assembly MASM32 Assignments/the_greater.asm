;A program that prints the greater of two numbers.

.686
.model flat, stdcall
option casemap :none

include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib
include \masm32\macros\macros.asm

.const
    x EQU 69
    y EQU 420
    
.code
start:

    mov eax, x
    cmp eax, y
    jge xGreater
    mov eax, y
    xGreater:
    printf("%d\n", eax)
    invoke ExitProcess, 0

end start