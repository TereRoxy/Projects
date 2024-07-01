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
    a db 1
    b dw 3
    e dd 15
    x dq 17

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;(a*a/b+b*b)/(2+b)+e-x; a-byte; b-word; e-doubleword; x-qword
        ; signed
        mov al, byte[a] ; al=a
        imul byte[a]    ; ax = a*a
        cwd             ; dx:ax = dword[a*a]
        idiv word[b]    ; ax = a*a/b
        mov cx, ax      ; cx = a*a/b
        mov ax, word[b] ; ax = b
        imul word[b]    ; dx:ax = b*b
        push dx
        push ax
        pop ebx         ; ebx = b*b
        mov ax, cx      ; ax = a*a/b
        cwde             ; eax = a*a/b
               
        add eax, ebx    ; eax = a*a/b+b*b
        mov cx, 2       ; cx = 2
        add cx, word[b]       ; cx = 2+b
        push eax
        pop ax
        pop dx          ; dx:ax = a*a/b+b*b
        idiv cx         ; ax = (a*a/b+b*b)/(2+b)
        cwde             ; dx:ax = (a*a/b+b*b)/(2+b)
        add eax, dword[e]; eax = (a*a/b+b*b)/(2+b)+e
        cdq              ; edx:eax = (a*a/b+b*b)/(2+b)+e
        sub eax, dword[x]; from lower part of edx:eax we subtract lower part of x
        sbb edx, dword[x+4]; from higher part of edx:eax we subract (with borrow) the higher part of x
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
