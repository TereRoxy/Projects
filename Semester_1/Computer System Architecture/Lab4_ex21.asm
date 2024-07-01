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
    A dw 10h
    B dw 9h
    C dd 0

; our code starts here
segment code use32 class=code
    start:
        ; 21
        ; Given the words A and B, compute the doubleword C as follows:
        ; the bits 0-3 of C are the same as the bits 5-8 of B 
        ; the bits 4-10 of C are the invert of the bits 0-6 of B
        ; the bits 11-18 of C have the value 1
        ; the bits 19-31 of C are the same as the bits 3-15 of B
        mov ecx, dword[C]
        
        mov ax, word[B]
        mov bx, 001Eh ; 0000 0001 1110 0000
        and ax, bx  ; extract bits 5-8
        shr ax, 5      ; bits 5-8 to 0-3
        or cx, ax      ; copy bits 0-3
        
        mov ax, word[B]
        not ax          ; invert all the bits
        mov bx, 003Fh  ; 0000 0000 0011 1111
        and ax, bx     ; select the bits
        shl ax, 4     ; shift left to the desired position
        or cx, ax     ; copy bits 4-10
        
        ; set bits 11-18 to 1
        or ecx,  0003f800h ; 0000 0000 0000 0011  1111 1000 0000 0000
        
        mov eax, 0
        mov ax, word[B]
        mov bx, 0fff8h      ; 1111 1111 1111 1000
        and ax, bx         ; select the bits 3-15
        shl eax, 16        ; shift left
        or ecx, eax        ; copy bits 19-31
        
        mov dword[C], ecx

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
