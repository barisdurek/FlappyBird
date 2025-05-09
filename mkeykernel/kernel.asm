bits 32
section .text
    align 4
    dd 0x1BADB002           
    dd 0x00                  
    dd - (0x1BADB002 + 0x00) 

global start
global keyboard_handler
global read_port
global write_port
global load_idt

extern kmain                
extern keyboard_handler_main 

read_port:
    mov edx, [esp + 4]      
    in al, dx               
    ret

write_port:
    mov edx, [esp + 4]      
    mov al, [esp + 8]      
    out dx, al          
    ret

load_idt:
    mov edx, [esp + 4]    
    lidt [edx]             
    sti                  
    ret

keyboard_handler:
    pusha                 
    mov ax, 0               
    mov ds, ax
    mov es, ax
    call keyboard_handler_main 
    popa                    
    iret                  

start:
    cli                    
    mov esp, stack_space   
    call kmain              
    hlt                     

section .bss
    resb 8192              
stack_space:               

section .note.GNU-stack noalloc noexec nowrite progbits