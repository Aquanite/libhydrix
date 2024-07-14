bits 64
section .text

extern hydrix_main
global _start

;; This function tries to enable SSE extensions without checking
;; if it actually exists in the CPUID tables.
explicit_enable_sse:
    ; https://wiki.osdev.org/SSE
    mov rax, cr0
    and ax, 0xfffb
    or ax, 0x2
    mov cr0, rax
    
    mov rax, cr4
    or ax, 3 << 9
    mov cr4, rax
    
    ret


_start:
    cld                         ; Clear the direction flag as the C declaration mandates.
    and rsp, 0xfffffffffffffff0 ; Align stack to 16 bytes.
    ;Check if SSE
    call hydrix_main            ; Call the lib hydrix initialization function.