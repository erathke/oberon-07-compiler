format ELF

include 'ccall.inc'

section '.text' executable

public _start
extrn kernel_main
extrn kernel_config

SYS_write = 4
STDOUT = 1
MEM_SIZE = 64

_start:
	
	; initial message
	push stmsg_size
	push stmsg
	call print

	; calling kernel_config(mem, MEM_SIZE)
	push MEM_SIZE
	push mem
	call kernel_config
	
	; calling kernel_main()
	call kernel_main ; long jump
	
	ret ; should not be executed

print:
	push ebp
	mov ebp, esp
	mov eax, SYS_write
	mov ebx, STDOUT
	mov ecx, [ebp+8]
	mov edx, [ebp+12]
	int 80h
	pop ebp
	ret 8 ; poping 8 bytes from stack


section '.data' writeable
stmsg db "Booting OS...", 10
stmsg_size = $ - stmsg


section '.bss' writeable
mem rb MEM_SIZE


section '.note.GNU-stack'
