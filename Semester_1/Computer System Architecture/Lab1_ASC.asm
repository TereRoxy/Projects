bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern printf
import printf msvcrt.dll
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mesaj db "Numar: %d", 0
    numar dd 44
    numar2 dd 59
    rez dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        ;printf(mesaj, rez)
        
        mov eax, [numar]
        mov ebx, [numar2]
        add eax, ebx
        
        mov [rez], eax
        
        push dword [rez]
        push mesaj
        call [printf]
        add esp, 4*2
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
