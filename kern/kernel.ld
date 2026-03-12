ENTRY(_start)

SECTIONS
{
    /* Link in the high half for x86_64 kernel code model */
    . = 0xffffffff80100000;

    .text : AT(0x100000) {
        *(.text .stub .text.* .gnu.linkonce.t.*)
    }

    PROVIDE(etext = .);

    .rodata : {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    }

    . = ALIGN(0x1000);

    .data : {
        *(.data)
    }

    .bss : {
        PROVIDE(edata = .);
        *(.bss)
        PROVIDE(end = .);
    }

    .stab : {
        PROVIDE(__STAB_BEGIN__ = .);
        *(.stab)
        PROVIDE(__STAB_END__ = .);
    }

    .stabstr : {
        PROVIDE(__STABSTR_BEGIN__ = .);
        *(.stabstr)
        PROVIDE(__STABSTR_END__ = .);
    }
}
