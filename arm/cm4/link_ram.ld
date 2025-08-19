/* link_ram.ld */
MEMORY
{
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

_estack = ORIGIN(RAM) + LENGTH(RAM); /* スタックトップ */

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > RAM

    .text :
    {
        *(.text*)
        *(.rodata*)
    } > RAM

    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM

    .bss (NOLOAD) :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        __stack_start__ = .;
        . += 2K;   /* スタック2KB */
        __stack_end__ = .;
    } > RAM

    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        __heap_start__ = .;
        . += 2K;   /* ヒープ2KB */
        __heap_end__ = .;
    } > RAM
}
