section .text
    global BlendAlpha_ASM
BlendAlpha_ASM:
    movzx rax, dl
    mov r8, 255
    sub r8, rax
    mov r9, rdi
    and r9, 0x00FFFFFF
    mov r10, rsi
    and r10, 0x00FFFFFF
    imul r9, r8
    shr r9, 8
    imul r10, rax
    shr r10, 8
    add r9, r10
    mov r10, rdi
    and r10, 0xFF000000
    mov r11, rsi
    and r11, 0xFF000000
    imul r10, r8
    shr r10, 8
    imul r11, rax
    shr r11, 8
    add r10, r11
    or r9, r10
    mov rax, r9
    ret
