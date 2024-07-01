bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global _is_prime        

; declare external functions needed by our program

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    _is_prime:
        ; Input:  eax - the number to check for primality
    ; Output: eax - 1 if the number is prime, 0 otherwise

    cmp eax, 1          ; 1 is not a prime number
    jbe not_prime

    mov ecx, 2          ; Start dividing by 2

    check_divisor:
        cmp ecx, eax        ; Check if we have reached the number itself
        jae is_prime_done   ; If yes, the number is prime

        mov edx, 0          ; Clear the remainder
        div ecx             ; Divide the number by the current divisor

        cmp edx, 0          ; Check if the remainder is zero
        je not_prime        ; If yes, the number is not prime

        inc ecx             ; Move to the next divisor
        jmp check_divisor   ; Repeat the process

    not_prime:
        mov eax, 0          ; Set result to 0 (false)
        ret

    is_prime_done:
        mov eax, 1          ; Set result to 1 (true)
        ret
    
        
