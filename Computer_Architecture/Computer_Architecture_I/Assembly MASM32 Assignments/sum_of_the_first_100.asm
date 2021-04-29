;A program that prints the sum of the first 100 positive integers in Assembly masm32

.686
.model flat, stdcall
option casemap :none

include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib
include \masm32\macros\macros.asm

.data

    sum DWORD 0

.code
start:
    mov ecx, 0
    loop1:
    inc ecx
    add sum, ecx
    cmp ecx, 100
    je lblOut
    jmp loop1
    lblOut:
    mov eax, sum
    printf("EAX: %d\n", eax)
    invoke ExitProcess, 0

end start

