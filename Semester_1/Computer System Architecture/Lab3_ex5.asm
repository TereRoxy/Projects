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
    a db 5
    b db 7
    c db 11
    d db 4
    e dw 2
    f dw 23
    g dw 3
    h dw 27
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;a,b,c,d-byte, e,f,g,h-word
        ;(f*g-a*b*e)/(h+c*d)
        mov AX, word[f]     ; AX = f
        mul word[g]         ; DX:AX = f*g
        push DX             ; convert DX:AX to an extended register -> push to the stack
        push AX
        pop EBX             ; EBX = f*g
        mov AL, byte[a]     ; AL = a
        mul byte[b]         ; AX = a*b
        mul word[e]         ; DX:AX = a*b*e
        push DX             ; convert DX:AX to an extended register -> push to the stack
        push AX
        pop ECX             ; ECX = a*b*e
        sub EBX, ECX        ; EBX = f*g-a*b*e
        mov AL, byte[c]     ; AL = c
        mul byte[d]         ; AX = c*d
        add word[h], AX     ; h = h + c*d
        mov EAX, EBX        ; EAX = f*g-a*b*e
        push EAX
        pop AX
        pop DX
        div word[h]         ; AX = (f*g-a*b*e)/(h+c*d)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
