format ELF

section '.text' executable

public getcontext
getcontext: ; ctx1
	; eip, esp, ebp, ebx, ecx, edi, esi
	mov eax, [esp + 4]
	mov [eax +  4], esp ; esp
	mov [eax +  8], ebp ; ebp
	mov [eax + 12], ebx ; ebx
	mov [eax + 16], ecx	; ecx
	mov [eax + 20], edi ; edi
	mov [eax + 24], esi ; esi
	
	;mov eax, [esp + 4]
	;mov ecx, [esp]
	;mov [eax +  4], ecx ; esp
	;mov [eax +  8], ebp ; ebp
	;mov [eax + 12], ebx ; ebx
	;lea ecx, [esp + 4]
	;mov [eax + 16], ecx	; ecx
	;mov [eax + 20], edi ; edi
	;mov [eax + 24], esi ; esi
	ret


public swapcontext
swapcontext: ; ctx1, ctx2
	; eip, esp, ebp, ebx, ecx, edi, esi
	mov eax, [esp + 4]
	mov edx, [esp + 8]
	mov [eax +  4], esp
	mov [eax +  8], ebp
	mov [eax + 12], ebx
	mov [eax + 16], ecx
	mov [eax + 20], edi
	mov [eax + 24], esi
	mov esi, [edx + 24]
	mov edi, [edx + 20]
	mov ecx, [edx + 16]
	mov ebx, [edx + 12]
	mov ebp, [edx +  8]
	mov esp, [edx +  4]
	jmp dword [edx]
	ret


section '.note.GNU-stack'
