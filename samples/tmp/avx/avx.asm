format ELF

section 'text' executable
public testAVX

testAVX:
	push ebp
    mov ebp, esp
    
	mov eax, 1
	cpuid
	xor eax, eax
	bt ecx, 28 ; sets the carrier bit to value 28 of ecx 
	adc eax, eax ; add carrier bit to eax, 1 or 0 = true or false
	
	mov esp, ebp
	pop ebp
	ret

section '.note.GNU-stack'
