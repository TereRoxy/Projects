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
    a db 2, 1, -3, 3, -4, 2, 6
    lena equ $-a    ; length of a
    b db 4, 5, 7, 6, 2, 1
    lenb equ $-b    ; length of b
    r resb lena + lenb  ; maximum length of r

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; Two byte strings A and B are given. Obtain the string R by concatenating the elements of B in reverse order and the negative elements of A.
        mov esi, b ; set the starting offset of the source string b in ESI 
        mov edi, r + lenb - 1 ; set the starting offset of the destination string r (which we will parse in reverse order)
        
        mov ecx, lenb   ; we use the length of b to iterate through the string
        jecxz part2    ; jump if there is nothing in b
        reverse_b:  ; copy the reverse of b in r
            cld ; DF = 0 --> we iterate through b from left to right
            lodsb   ; mov al, [esi] and inc esi (load string of bytes)
            std ; DF = 1 --> right to left
            stosb ; mov [edi], al and dec edi
            
            loop reverse_b  ; if ecx>0 and dec ecx
        
        part2:
        mov esi, a ; set the starting offset of the source string a in esi
        mov edi, r + lenb  ; set the starting offset of the destination string r (the end of reverse b)
        mov ecx, lena  ; length of a to iterate through the string
        jecxz end    ; jump if there is nothing in a
        
        cld     ; DF = 0 --> we iterate through a left to right
        copy_a: ; copy the negative numbers from a
            cmp byte[esi], 0    ; check if the current number is positive or negative
            jge positive    ; jump if greater or equal to 0 (the number is positive)
            
            ; copy the negative number at the current position in r
            lodsb  ; mov al, [esi] and inc esi
            stosb  ; mov [edi], al and inc edi
            jmp negative
            
            positive:   ; move to the next byte
                inc esi
            negative:
            loop copy_a
        
        end:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
