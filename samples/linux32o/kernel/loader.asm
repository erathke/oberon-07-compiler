;
	MAGIC_NUMBER = 0x1BADB002     ; define the magic number constant
	FLAGS        = 0x1            ; multiboot flags
	CHECKSUM     = -MAGIC_NUMBER -FLAGS  ; calculate the checksum
                                    ; (magic number + checksum + flags should equal 0)

struc db [data]
     {
       common
        . db data
        .size = $ - .
     }


format ELF

section '.multiboot'
	align 4                         ; the code must be 4 byte aligned
	dd MAGIC_NUMBER             	; write the magic number to the machine code,
	dd FLAGS                    	; the flags,
	dd CHECKSUM

section '.text' executable
	public loader                    ; the entry symbol for ELF
	public reload_segs
	;extrn kernelInit
	extrn kernelMain
	extrn kernelPrint
	extrn kernelPrintInt
	extrn kernelInterruptHandler
	extrn CKernelInterruptHandler

loader:
	mov esp, kernel_stack ; stack pointer offset
  
	cli
	sti
  
    push eax ; multiboot_magic
    push ebx ; multiboot_structure
    call kernelMain
    
    push bye.size
    push bye
    call kernelPrint

_stop:
    cli
    hlt
    jmp _stop


reload_segs:
	mov ax, 0x10
	mov ds, ax ; 0x10 - an offset into GDT for the third (kernel data segment) record.
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	jmp 0x08:flush_cs

flush_cs:
	ret

include 'interrupts.asm'

section '.data'
bye db 'Bye!',0
interruptnumber: rb 1

section '.bss' writeable
.space rb 128*1024; # 128k
kernel_stack:

section '.note.GNU-stack'
