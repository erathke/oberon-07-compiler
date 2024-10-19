ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
	. = 0x0100000 + SIZEOF_HEADERS;

	.text : { *(.multiboot) *(.text*) }
	.data : { *(.data) }
	.bss  : { *(.bss) } :bss

	/DISCARD/ : { *(.comment) }
}

PHDRS 
{
	bss PT_LOAD FLAGS(6);
}
