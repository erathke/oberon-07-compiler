format ELF

include 'ccall.inc'

section '.text' executable

public _start
extrn kernel_main
extrn kernel_config

SYS_write = 4
STDOUT = 1
MEM_SIZE = 10

_start:
	push mem
	call kernel_config
	call print
	call kernel_main
	ret
print:
	mov eax, SYS_write
	mov ebx, STDOUT
	mov ecx, mem
	mov edx, MEM_SIZE
	int 80h
	ret

section '.data' writeable

section '.bss' writeable
mem rb MEM_SIZE

section '.note.GNU-stack'
