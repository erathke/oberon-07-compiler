format ELF

section '.text' executable

public update
update: ; ctx1
	;push ebp
	;mov ebp, esp
	mov edx, [esp + 4]
	;lea edx, [esp + 4]
	mov dword [edx], 22
	mov dword [edx + 4], 2000
	mov dword [edx + 8], 3333
	;pop ebp
	ret

section '.note.GNU-stack'
