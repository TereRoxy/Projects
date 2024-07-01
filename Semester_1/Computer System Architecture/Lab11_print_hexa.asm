bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global print_hexa        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                        
extern printf
import printf msvcrt.dll                        

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    print_format db "%x", 0

; our code starts here
segment code use32 class=code
    print_hexa:
        ; ...
        ; eax = the number to be printed
        push dword print_format
        push dword [eax]
        call [printf]
        add esp, 4*2
        
