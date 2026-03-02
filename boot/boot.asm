; Dragon OS Bootloader
; Designed & Developed by ABID MEHMOOD

BITS 32
section .multiboot
    align 4
    dd 0x1BADB002              ; Magic number
    dd 0x00                    ; Flags
    dd -(0x1BADB002 + 0x00)   ; Checksum

section .bss
    align 16
stack_bottom:
    resb 16384                 ; 16 KB stack
stack_top:

section .text
global _start
extern kernel_main
extern init_ui_engine
extern init_voice_module
extern init_security_module

_start:
    mov esp, stack_top         ; Set up stack
    
    ; Display boot message
    call display_boot_message
    
    ; Initialize Dragon OS
    push ebx                   ; Multiboot info
    call kernel_main
    
    ; Halt system
    cli
.hang:
    hlt
    jmp .hang

display_boot_message:
    mov edi, 0xB8000          ; VGA text buffer
    mov esi, boot_msg
    mov ah, 0x0F              ; White on black
.loop:
    lodsb
    test al, al
    jz .done
    stosw
    jmp .loop
.done:
    ret

section .data
boot_msg db '  DRAGON OS - Designed & Developed by ABID MEHMOOD  ', 0
