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
    ; a - byte, b - word, c - double word, d - qword - Unsigned representation
    a db 3
    b dw 10
    c dd 13
    d dq 17

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;(c-a) + (b - d) + d
        mov EAX, dword[c]   ; EAX = c
        mov EBX, 0
        add BL, byte[a] ; BL = a
        sub EAX, EBX    ; EAX = c-a
        push EAX        ; save (c-a) to stack
        mov EBX, 0
        add BX, word[b]    ; EBX = b
        mov ECX, 0
        mov EAX, dword[d]
        mov EDX, dword[d+4] ; EDX:EAX = d
        sub EBX, EAX
        sbb ECX, EDX        ; ECX:EBX = b-d
        pop EAX             ; EAX = c-a
        mov EDX, 0
        add EAX, EBX
        adc EDX, ECX        ; EDX:EAX = (c-a) + (b - d)
        mov EBX, dword[d]
        mov ECX, dword[d+4] ; ECX:EBX = d
        sub EAX, EBX        
        sbb EDX, ECX        ; EDX:EAX = (c-a) + (b - d) + d
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
