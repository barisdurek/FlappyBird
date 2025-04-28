ENTRY(kmain) 

SECTIONS
{
    . = 0x100000; 

    .text ALIGN(0x1000) : {
        *(.multiboot)   
        *(.text)         
    } :text

    .rodata ALIGN(0x1000) : {
        *(.rodata)       
    } :rodata

    .data ALIGN(0x1000) : {
        *(.data)         
    } :data

    .bss ALIGN(0x1000) : {
        *(COMMON)       
        *(.bss)         
    } :bss
}

PHDRS
{
    text   PT_LOAD FLAGS(5); /* R-X*/
    rodata PT_LOAD FLAGS(4); /* R--*/
    data   PT_LOAD FLAGS(6); /* RW*/
    bss    PT_LOAD FLAGS(6); /* RW*/
}