bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern scanf
import scanf msvcrt.dll                          
                          
extern printf
import printf msvcrt.dll                          

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 0  ; first number 
    b dw 0  ; second number
    format db "%u%u", 0 ; unsigned decimal
    c dd 0
    pformat db "%x"     ; hexadecimal
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        ; Read two words a and b in base 10 from the keyboard. Determine the doubleword c such 
        ; that the low word of c is given by the sum of the a and b and the high 
        ; word of c is given by the difference between a and b. Display the result in base 16 
        ; Example:
        ; a = 574, b = 136
        ; c = 01B602C6h
        
        ; scanf(format, a, b)
        ; push parameters from right to left
        
        push dword b
        push dword a
        push dword format
        call [scanf]    ; call the function
        add esp, 4*3    ; take parameters out of the stack
        
        mov eax, 0      ; clear eax
        mov ax, word[a] ; ax = a
        add ax, word[b] ; ax = a + b
        
        mov bx, word[a] ; bx = a 
        sub bx, word[b] ; bx = a - b
        shl ebx, 16      ; shift the low word of ebx to the high word of ebx
        
        add eax, ebx    ; construct the number c
        mov [c], eax      ; update c
        
        ;  printf(pformat, c)
        
        push dword [c]  ; !!! value of c
        push dword pformat
        call [printf]
        add esp, 4*2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
