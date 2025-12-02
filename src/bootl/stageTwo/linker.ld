ENTRY(stageTwo)
OUTPUT_FORMAT("binary")
OUTPUT("build/temp/bootl/stagetwo")
SECTIONS
{
    . = 0x7E00;
    .text : {
        *(.text)
    }
    .rodata : {
        *(.rodata)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
        *(COMMON)
    }
}