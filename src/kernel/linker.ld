ENTRY(kernel_entry)
OUTPUT_FORMAT("elf64-x86-64")
OUTPUT("build/temp/kernel/kernel.elf")
SECTIONS
{
    . = 0xC0000000;
    .text : AT(ADDR(.text) - 0xC0000000){
        *(.text)
    }
    .rodata : AT(ADDR(.rodata) - 0xC0000000) {
        *(.rodata)
    }
    .data : AT(ADDR(.data) - 0xC0000000) {
        *(.data)
    }
    .bss : AT(ADDR(.bss) - 0xC0000000) {
        *(.bss)
        *(COMMON)
    }
}