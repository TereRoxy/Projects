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
    ; max decimal number on a word can be 65535 -> 5 digits --> we need to reserve 5 bytes of memory for each word
    sir DW 12345, 20778, 4596   ; 3039h, 512Ah, 11F4h --> 39h 30h 2Ah 51h F4h 11h
    lens equ ($-sir)/2  ; number of words in the string
    nbytes equ lens*5+1     ; number of bytes needed = number of words * 5 (+1 so we have an even number of bytes)
    result resb nbytes
    reverse resb nbytes
    ten dw 10     ; variable used for determining the digits in base 10 of a number by successive divisions to 10

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; Being given a string of words, obtain the string (of bytes) of the digits in base 10 of each word from this string
        ; Solution idea: we parse through the string word by word from right to left to obtain the base 10 digits in a string 
        ; --> the resulting string will contain the reverse of our desired result
        ; We reverse the string
        ; If we parse the words left to right, we need to reverse the resulting string of each word and concatenate it to the previous 
        ; bc the remainder of the division by 10 gives us the last digit of the word
        mov esi, sir + 2*(lens - 1) ; set the starting offset (end of sir) as source in esi
        mov edi, reverse    ; set the starting offset as destination in edi
        
        mov ecx, lens
        jecxz end
        
        iterate:
            ;mov ax, word[esi]  ; ax = content of the current word
            ;sub esi, 2       ; decrement esi by 2 bytes (1 word)
            std 
            lodsw
            jmp get_digits
            next:
        loop iterate
        
        dec edi ; we correct edi so it points at the last element in the reversed string
        jmp reverse_string

        get_digits:
            ; we do the division by 10 on dx:ax to prevent overflow
            mov dx, 0         ; clear dx     
            div word[ten]     ; ax = sir[i]/10, dx = sir[i]%10 , i is the current word
            jmp store_digits

        store_digits:
            mov ebx, 0    ;
            mov bl, dl
            mov [edi], ebx   ; store the remainder of the division by 10 in edi
            inc edi             ; increment edi by 1 byte --> we move to the next position in the string !!! at the end, edi will point beyond the actual string of bytes
            cmp ax, 0        ; if ax = 0, we have no more digits to get
            jne get_digits   ; else we get the next digit
            jmp next     ; we jump to the next word

        reverse_string:
            mov esi, edi    ; set the starting offset (end of reverse) as source in esi
            
            mov ecx, edi    ; ecx = the ending offset of the reverse string
            sub ecx, reverse-1    ; ecx = length of the string of digits         
            jecxz end
            
            mov edi, result ; set the starting offset as destination in edi
            
            reverse_loop:
                std ; DF = 1 --> we iterate right to left in the reverse string
                lodsb
                cld ; DF = 0 --> we iterate left to right in the result string
                stosb
            loop reverse_loop
            
        end:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
