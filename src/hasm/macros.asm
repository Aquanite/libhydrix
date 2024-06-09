; MACROS.ASM (macros.asm) - Assembly macros for the x86_64 architecture

; Push all general purpose registers to the stack
%macro pusha 0
    push rax
    push rcx
    push rdx
    push rbx
    push rsp
    push rbp
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

; Pop all general purpose registers from the stack
%macro popa 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rsp
    pop rbx
    pop rdx
    pop rcx
    pop rax
%endmacro

; Prepare stack for a function call
%macro psfc 0
    push rbp ; Save the base pointer
    mov rbp, rsp
%endmacro

; Prepare stack for a function call with local variables
%macro psfc 1
    push rbp ; Save the base pointer
    mov rbp, rsp
    sub rsp, %1
%endmacro
