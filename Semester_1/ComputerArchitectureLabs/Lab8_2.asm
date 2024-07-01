bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern fwrite, fopen, fclose
import fwrite msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll                     
                          

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    text db "a1b2 cd3e 45gh", 0    ; given text
    len_txt dd $-text
    output_file db "output.txt", 0
    mode_write db "w", 0            ; write mode for file
    file_handle dd -1               ; file descriptor used for function calls
    buffer db 0
    zero db '0'
    nine db '9'
    x db 'X'bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack


; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; A file name and a text (defined in the data segment) are given. 
        ; The text contains lowercase letters, digits and spaces. 
        ; Replace all the digits on odd positions with the character ‘X’. 
        ; Create the file with the given name and write the generated text to file.
        
        ; Open the file
        ; fopen(const char* filename, const char * access_mode)
        push dword mode_write ; push the parameters in reverse order
        push dword output_file ; for strings, we push the offset
        call [fopen]           
        add esp, 4*2           ; clear the stack
        
        mov [file_handle], eax ; save the file descriptor
        cmp eax, 0             ; eax = 0 if there is an error with the file
        je end
        
        cld                    ; parse the string left to right
        mov esi, text
        
        mov ebx, 0             ; ebx = counter for even or odd positions
        mov ecx, [len_txt]
        repeat:
            inc ebx ; by cdecl, ebx shouldn't be modified after function call
        
            lodsb              ; al = esi, inc esi
            
            cmp al, [zero]
            jnae copy          ; if the current character is not >= '0'
            cmp al, [nine]     
            jnbe copy          ; if the current character is not <= '9'
            
            test ebx, 1
            jz copy            ; if the position is even, we copy the the unmodified digit
            
            
            ; if it didn't jump, the current character is a digit on an odd position            
            mov al, byte[x]    ; replace with character 'X'
            
            copy:
            mov byte[buffer], al 
            ; ecx might be modified during call, so we save it on the stack
            push ecx
            
            ; fwrite(string ptr, integer size, integer n, FILE * handle) - writes n times size bytes from
            ; the string ptr into the file identified by handle.
            ; write to file
            push dword [file_handle]
            push dword 1
            push dword 1
            push dword buffer
            call [fwrite]
            add esp, 4*4
            
            ; get ecx from the stack
            pop ecx
    
        loop repeat
        
        ; fclose(FILE* handle)
        push dword [file_handle]
        call [fclose]
        add esp, 4*1
        
        end:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
