format ELF

section '.text' executable

public setjmp
public longjmp


setjmp:
	mov eax, [esp + 4]
	mov [eax +  0], ebx
	mov [eax +  4], esi
	mov [eax +  8], edi
	mov [eax + 12], ebp
	lea ecx, [esp + 4]
	mov [eax + 16], ecx
	mov ecx, [esp]
	mov [eax + 20], ecx
	xor eax, eax
	ret


longjmp:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	cmp eax, 1
	adc al, 0
	mov ebx, [edx +  0]
	mov esi, [edx +  4]
	mov edi, [edx +  8]
	mov ebp, [edx + 12]
	mov esp, [edx + 16]
	jmp dword [edx + 20]
;	ret

section '.note.GNU-stack'
