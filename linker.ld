OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

PHDRS
{
    text   PT_LOAD FLAGS(5);
    rodata PT_LOAD FLAGS(4);
    data   PT_LOAD FLAGS(6);
}

SECTIONS
{
    . = 0xffffffff80000000;

    .text : ALIGN(0x1000)
    {
        *(.text .text.*)
    } :text

    . = ALIGN(0x1000);

    .rodata :
    {
        *(.rodata .rodata.*)
        *(.eh_frame*)
        *(.note*)
    } :rodata

    . = ALIGN(0x1000);

    .data :
    {
        *(.data .data.*)
    } :data

    .bss :
    {
        *(.bss .bss.*)
        *(COMMON)
    } :data
}