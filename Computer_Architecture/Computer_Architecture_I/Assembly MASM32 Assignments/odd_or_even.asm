;A program that prints if either a number is odd or even.

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
    
.code
start:

    mov eax, x
    and eax, 1
    cmp eax, 1
    je impar
    jmp par
    impar:
    printf("The number is odd\n")
    jmp theEnd
    par:
    printf("The number is even\n")
    theEnd:
    invoke ExitProcess, 0

end start