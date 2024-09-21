OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386) 

ENTRY(_start)
SECTIONS
{
#	. = 1000H + SIZEOF_HEADERS;
#	.text     : { *(.text) } :text
#	. = 0x8048000;
#	.data : { *(.data) }
#	.bss : { *(.bss) }
#	/DISCARD/       : { *(.note.*) }
#	.all     : { *(.text .text.* .data .bss) } :all
#
/* Define an output section ".text". */
  . = 0x8048000 + SIZEOF_HEADERS;
  .text : {
    /* Pull in all symbols in input sections named .text */
    *(.text)
    /* Do the same for sections starting with .text.,
       such as .text.foo */
    *(.text.*)
  } :text 

  /* Do the same for ".bss", ".rodata", and ".data". */
  .data : { *(.data); *(.data.*) } :data
  .bss : { *(.bss); *(.bss.*) } :bss

}
PHDRS
{
	text PT_LOAD FILEHDR PHDRS;
	data PT_LOAD FILEHDR PHDRS;
	bss PT_LOAD FILEHDR PHDRS;
}
