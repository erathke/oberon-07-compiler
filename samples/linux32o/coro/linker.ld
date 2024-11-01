/* linker.ld = configured for minimum executable size */
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386) 

ENTRY(_start)

PHDRS
{
	text PT_LOAD FILEHDR PHDRS ;
	data PT_LOAD FILEHDR PHDRS ;
	bss PT_LOAD FILEHDR PHDRS ;
}

SECTIONS
{
	. = 0x8048000 + SIZEOF_HEADERS;
	.text : { *(.text .text.*) } :text
	.data : { *(.data) } :data 
	.bss  : { *(.bss) } :bss 
	
	/DISCARD/       : { *(.note.* .comment .eh*) } 
}
