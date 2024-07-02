section .text
global fastmath_abs
global fastmath_sqrt
global retable_fastmath_abs
global retable_fastmath_sqrt
; C func: extern void fastmath_abs(int* x);
fastmath_abs:
    mov rdi, [rsp+8]   ; Load pointer to x into rdi
    mov eax, [rdi]     ; Load the value at x into eax
    cdq                ; Sign-extend eax into edx:eax
    xor eax, edx       ; Compute the absolute value
    sub eax, edx       ; by (eax XOR edx) - edx
    mov [rdi], eax     ; Store the result back into x
    ret
fastmath_sqrt:
    mov rdi, [rsp+8]   ; Load pointer to x into rdi
    mov eax, [rdi]     ; Load the value at x into eax
    test eax, eax      ; Test if x is zero
    jz .done           ; If x is zero, jump to done
    mov ecx, eax       ; Copy the value of x to ecx
    shr ecx, 1         ; Initial guess: x / 2
    or ecx, 1          ; Make sure the guess is not zero
    .loop:
        mov edx, eax       ; Copy x to edx
        div ecx            ; eax = x / guess
        add ecx, eax       ; ecx = (guess + x / guess)
        shr ecx, 1         ; ecx = (guess + x / guess) / 2
        cmp ecx, eax       ; Compare new guess with previous
        jne .loop          ; If not equal, continue the loop
        mov eax, ecx       ; Move the result to eax
    .done:
        mov [rdi], eax     ; Store the result back into x
        ret

;RETURNABLES
; C func:  extern "C" int retable_fastmath_abs(int x);
retable_fastmath_abs:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov [rbp-8], rdi
    mov rdi, [rbp-8]
    call fastmath_abs
    mov eax, [rdi]
    add rsp, 16
    pop rbp
    ret

; C func:  extern "C" int retable_fastmath_sqrt(int x);
retable_fastmath_sqrt:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov [rbp-8], rdi
    mov rdi, [rbp-8]
    call fastmath_sqrt
    mov eax, [rdi]
    add rsp, 16
    pop rbp
    ret