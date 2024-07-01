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
    a db 9
    b db 11
    c db 13
    d dw 100

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;a,b,c - byte, d - word
        ; d-[3*(a+b+2)-5*(c+2)]
        mov BL, byte[a]   ; BL = a
        add BL, byte[b]   ; BL = a+b
        add BL, 2   ; BL = a+b+2
        mov AL, 3   ; AL = 3
        mul BL      ; AX = 3*(a+b+2)
        mov BX, AX  ; BX = 3*(a+b+2)
        mov AL, 5   ; AL = 5
        
        mov CL, byte[c]   ; CL = c
        add CL, 2   ; CL = c+2
        mul CL      ; AX = 5*(c+2)
        sub BX, AX  ; BX = 3*(a+b+2)-5*(c+2)
        sub word[d], BX   
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
