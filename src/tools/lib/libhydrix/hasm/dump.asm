global dump_rax
global dump_rbx
global dump_rcx
global dump_rdx
global dump_rsi
global dump_rdi
global dump_rbp
global dump_rsp
global dump_r8
global dump_r9
global dump_r10
global dump_r11
global dump_r12
global dump_r13
global dump_r14
global dump_r15

; dump_rax returns the value of the rax register
dump_rax:
    mov rax, rax
    ret

dump_rbx:
    mov rax, rbx
    ret

dump_rcx:
    mov rax, rcx
    ret

dump_rdx:
    mov rax, rdx
    ret

dump_rsi:
    mov rax, rsi
    ret

dump_rdi:
    mov rax, rdi
    ret

dump_rbp:
    mov rax, rbp
    ret

dump_rsp:
    mov rax, rsp
    ret

dump_r8:
    mov rax, r8
    ret

dump_r9:
    mov rax, r9
    ret

dump_r10:
    mov rax, r10
    ret

dump_r11:
    mov rax, r11
    ret

dump_r12:
    mov rax, r12
    ret

dump_r13:
    mov rax, r13
    ret

dump_r14:
    mov rax, r14
    ret

dump_r15:
    mov rax, r15
    ret

; Functions for C++: extern "C" unsigned long long dump_rax(); etc.