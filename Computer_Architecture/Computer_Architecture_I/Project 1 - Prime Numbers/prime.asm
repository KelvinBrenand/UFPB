;UNIVERSIDADE FEDERAL DA PARAÍBA - UFPB
;CENTRO DE INFORMÁTICA - CI
;CURSO: CIÊNCIA DA COMPUTAÇÃO
;DISCIPLINA: ARQUITETURA DE COMPUTADORES
;PROFESSOR: EWERTON MONTEIRO SALVADOR
;ALUNO: KELVIN BRENAND - 20180005270

;A PROGRAM THAT PRINTS IF A GIVEN NUMBER IS PRIME.

.686
.model flat, stdcall
option casemap:none

include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc
include \masm32\include\windows.inc
include \masm32\include\masm32.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib
includelib \masm32\lib\masm32.lib
include \masm32\macros\macros.asm

.data?
converted_input_number dd ?
restart_option BYTE ?

.data
inputHandle dd 0
outputHandle dd 0
console_count dd 0

intro db "Enter a natural number greater than 1:", 0ah, 0h
prime_message db "The number is prime!", 0ah, 0h
not_prime_message db "The number is not prime!", 0ah, 0h
restart_confirmation db "Do you want to verify another number? [y/n]", 0ah, 0h
invalid_input db "Invalid input!", 0ah, 0h

input_number db 50 dup(0)

.code
start:
    invoke GetStdHandle, STD_INPUT_HANDLE
    mov inputHandle, eax
    invoke GetStdHandle, STD_OUTPUT_HANDLE
    mov outputHandle, eax

    invoke WriteConsole, outputHandle, addr intro, sizeof intro, addr console_count, NULL                     ;prints the initial menssage
    invoke ReadConsole, inputHandle, addr input_number, sizeof input_number, addr console_count, NULL         ;storages the input number
    
    call inputConverter
    invoke atodw, addr input_number            ;Converts the string to int 
    mov converted_input_number, eax

    cmp converted_input_number, 1              ;Handles invalid inputs
    jbe invalid

    push converted_input_number                ;Puts the converted input number in the stack
    call primeFunction                         ;Jumps to the primeFunction function
    
    ;Finally, the result of the function
    cmp eax, 1
    je printPrime
    invoke WriteConsole, outputHandle, addr not_prime_message, sizeof not_prime_message, addr console_count, NULL
    jmp restart
    printPrime:
        invoke WriteConsole, outputHandle, addr prime_message, sizeof prime_message, addr console_count, NULL

    ;Restart the program?
    restart:
        invoke WriteConsole, outputHandle, addr restart_confirmation, sizeof restart_confirmation, addr console_count, NULL
        invoke ReadConsole, inputHandle, addr restart_option, sizeof input_number, addr console_count, NULL
        cmp restart_option, 121              ;If the input is the 'y' char (ASCII = 127) the program restarts. Otherwise, it ends.
        je start
        invoke ExitProcess, 0

invalid:
    invoke WriteConsole, outputHandle, addr invalid_input, sizeof invalid_input, addr console_count, NULL
    invoke ExitProcess, 0

inputConverter:
    ;The following snippet of code deals with the masm32 atodw's error.
    ;Big thanks to Professor Ewerton R. Salvador for providing this snippet of code :).
    
    mov esi, offset input_number
    proximo:
        mov al, [esi]
        inc esi
        cmp al, 48
        jl terminar
        cmp al, 58
        jl proximo
    terminar:
        dec esi
        xor al, al
        mov [esi], al
        ret
    
primeFunction:     ;This function uses the Trial Division Algorithm. This method divides n by each integer from 2 up to n-1.
    push ebp
    mov ebp, esp
    
    mov ecx, 2
    loop1:
        mov eax, DWORD PTR [ebp+8]
        cmp ecx, eax
        je isPrime
        xor edx, edx
        div ecx
        cmp edx, 0
        je notPrime
        inc ecx
        jmp loop1
    isPrime:
        mov eax, 1
        jmp finishFunction
    notPrime:
        mov eax, 0
    finishFunction:
    
        mov esp, ebp
        pop ebp
        ret 4

end start