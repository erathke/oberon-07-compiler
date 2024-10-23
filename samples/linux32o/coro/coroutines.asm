format ELF

section '.text' executable

public getcontext
getcontext: ; ctx1
	; ebx, esi, edi, ebp, ecx, esp, eip
	mov eax, [esp + 4]		;mov 4(%esp), %eax
	mov [eax +  0], ebx			;mov    %ebx, (%eax)
	mov [eax +  4], esi		;mov    %esi, 4(%eax)
	mov [eax +  8], edi		;mov    %edi, 8(%eax)
	mov [eax + 12], ebp		;mov    %ebp, 12(%eax)
	lea ecx, [esp + 4]		;lea 4(%esp), %ecx
	mov [eax + 16], ecx		;mov    %ecx, 16(%eax)
	mov ecx, [esp]			;mov  (%esp), %ecx
	mov [eax + 20], ecx		;mov    %ecx, 20(%eax)
	ret


public swapcontext
swapcontext: ; ctx1, ctx2
	; ebx, esi, edi, ebp, ecx, esp, eip
	mov eax, [esp + 4]		;movl 4(%esp), %eax
	mov edx, [esp + 8]		;movl 8(%esp), %edx
	mov [eax +  0], ebx		;movl %ebx, (%eax)
	mov [eax +  4], esi		;movl %esi, 4(%eax)
	mov [eax +  8], edi		;movl %edi, 8(%eax)
	mov [eax + 12], ebp		;movl %ebp, 12(%eax)
	mov [ecx + 16], ecx		;movl %ecx, 16(%eax)
	mov [eax + 20], esp		;movl %esp, 20(%eax)
	mov esp, [edx + 20]		;movl 20(%edx), %esp
	mov ecx, [edx + 16]		;movl 16(%edx), %ecx
	mov ebp, [edx + 12]		;movl 12(%edx), %ebp
	mov edi, [edx +  8]		;movl 8(%edx), %edi
	mov esi, [edx +  4];	movl 4(%edx), %esp
	mov ebx, [edx +  0];	movl 4(%edx), %esp
	jmp dword [edx + 24]
	;ret


section '.note.GNU-stack'
