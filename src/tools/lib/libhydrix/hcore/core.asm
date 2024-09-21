bits 64
section .text

extern hydrix_main
global _start

;; Check if SSE is supported by querying CPUID
check_sse_support:
    mov eax, 1         ; CPUID function 1
    cpuid              ; Execute CPUID
    test edx, 0x2000000 ; Check SSE bit in EDX
    jz no_sse_support  ; Jump if SSE is not supported
    ret

;; Enable SSE if supported
enable_sse:
    mov rax, cr0
    and rax, ~0x60000  ; Clear EM and TS bits
    or rax, 0x2        ; Set MP bit
    mov cr0, rax

    mov rax, cr4
    or rax, 0x600      ; Set OSFXSR and OSXMMEXCPT bits
    mov cr4, rax

    ret

no_sse_support:
    ; Handle the case where SSE is not supported
    ; For now, just halt the system
    cli
    hlt
    ret

enable_cpu_caching:
    xor rax,rax
	mov rax,cr0
	and eax,9fffffffh
	mov cr0,rax
    ret

_start:
    cld
    and rsp, 0xfffffffffffffff0
    call check_sse_support
    call enable_sse
    call enable_cpu_caching
    call hydrix_main
