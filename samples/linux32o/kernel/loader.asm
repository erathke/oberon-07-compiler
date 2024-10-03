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
	public set_handlers
	;extrn kernelInit
	extrn kernelMain
	extrn kernelPrint
	extrn kernelPrintInt
	extrn kernelInterruptHandler

loader:
	mov esp, kernel_stack ; stack pointer offset
	
	mov eax, [ebp + 8]
	lidt [eax]
  
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

set_handlers:
	push ebp
	mov ebp, esp
	push eax
	
	mov eax, [ebp + 8]
	; exceptions offset = 0x00
	mov [eax + 0], dword HandleException0x00
	mov [eax + 4], dword HandleException0x01
	mov [eax + 8], dword HandleException0x02
	mov [eax + 12], dword HandleException0x03
	mov [eax + 16], dword HandleException0x04
	mov [eax + 20], dword HandleException0x05
	mov [eax + 24], dword HandleException0x06
	mov [eax + 28], dword HandleException0x07
	mov [eax + 32], dword HandleException0x08
	mov [eax + 36], dword HandleException0x09
	mov [eax + 40], dword HandleException0x0A
	mov [eax + 44], dword HandleException0x0B
	mov [eax + 48], dword HandleException0x0C
	mov [eax + 52], dword HandleException0x0D
	mov [eax + 56], dword HandleException0x0E
	mov [eax + 60], dword HandleException0x0F
	mov [eax + 64], dword HandleException0x10
	mov [eax + 68], dword HandleException0x11
	mov [eax + 72], dword HandleException0x12
	mov [eax + 76], dword HandleException0x13
	; hardware offset = 0x20
	mov eax, [ebp + 8]
	add eax, 0x20 * 4 ; offset * 4
	mov [eax + 0], dword HandleInterruptRequest0x00
	mov [eax + 4], dword HandleInterruptRequest0x01
	mov [eax + 8], dword HandleInterruptRequest0x02
	mov [eax + 12], dword HandleInterruptRequest0x03
	mov [eax + 16], dword HandleInterruptRequest0x04
	mov [eax + 20], dword HandleInterruptRequest0x05
	mov [eax + 24], dword HandleInterruptRequest0x06
	mov [eax + 28], dword HandleInterruptRequest0x07
	mov [eax + 32], dword HandleInterruptRequest0x08
	mov [eax + 36], dword HandleInterruptRequest0x09
	mov [eax + 40], dword HandleInterruptRequest0x0A
	mov [eax + 44], dword HandleInterruptRequest0x0B
	mov [eax + 48], dword HandleInterruptRequest0x0C
	mov [eax + 52], dword HandleInterruptRequest0x0D
	mov [eax + 56], dword HandleInterruptRequest0x0E
	mov [eax + 60], dword HandleInterruptRequest0x0F
	mov [eax + 64], dword HandleInterruptRequest0x31
	; syscall offset = 0x80
	mov eax, [ebp + 8]
	add eax, 0x80 * 4 ; offset * 4
	mov [eax + 0], dword HandleInterruptRequest0x80
	
	pop eax
	pop ebp
	ret


section '.data'
bye db 'Bye!',0
interruptnumber: rb 1

section '.bss' writeable
.space rb 128*1024; # 128k
kernel_stack:

section '.note.GNU-stack'
