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
        ; unsigned
        mov al, byte[a] ;al = a
        mul byte[a]     ; ax = a*a
        mov dx, 0       ; dx:ax = a*a
        div word[b]     ; ax = a*a/b
        mov bx, ax      ; bx = a*a/b
        mov ax, word[b] ; ax = b
        mul word[b]     ; dx:ax = b*b
        add ax, bx
        adc dx, 0       ; dx:ax = a*a/b+b*b
   
        mov cx, 2       ; cx = 2
        add cx, word[b] ; cx = 2+b
        div cx          ; ax = (a*a/b+b*b)/(2+b)
        mov ebx, 0
        mov bx, ax      ; ebx = (a*a/b+b*b)/(2+b)
        add ebx, dword[e]; ebx = (a*a/b+b*b)/(2+b)+e
        
        mov eax, dword[x]
        mov edx, dword[x+4] ; edx:eax = x
        sub ebx, eax 
        sbb edx, 0 ; edx:eax = (a*a/b+b*b)/(2+b)+e-x
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
