/* strip.ld = configured for be compatilble with the strip command */
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386) 

ENTRY(_start)

PHDRS
{
	text PT_LOAD PHDRS ;
	data PT_LOAD FILEHDR ;
}

SECTIONS
{
	. = 0x8048000 + SIZEOF_HEADERS;
	.text : { *(.text .text.*) } :text
	. = . + 0x1000;
	.data : { *(.data) } :data 
	.bss  : { *(.bss) } :data 
	
	/DISCARD/       : { *(.note.* .comment .eh*) }  
}
