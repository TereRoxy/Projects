bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    ; a - byte, b - word, c - double word, d - qword - Signed representation
    a db 12
    b dw 13
    c dd 9
    d dq 17

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; d-a+(b+a-c)
        mov AL, byte[a] ; AL = byte[a]
        CBW             ; AX = word[a]
        CWDE            ; EAX = dword[a]
        mov EBX, EAX    ; EBX = dword[a]
        mov AX, word[b] ; AX = word[b]
        CWDE            ; EAX = dword[b]
        mov ECX, EAX    ; ECX = dword[b]
        add ECX, EBX    ; ECX = b+a
        sub ECX, dword[c]; ECX = b+a-c
        mov EAX, dword[d]
        mov EDX, dword[d+4] ; EDX:EAX = d
        
        
        sub EAX, EBX
        sbb EDX, 0      ; EDX:EAX = d-a
        add EAX, ECX
        adc EDX, 0      ; EDX:EAX = d-a+(b+a-c)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
