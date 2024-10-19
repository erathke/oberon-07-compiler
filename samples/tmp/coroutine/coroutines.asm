
public setjmp
setjmp:
	
	xor eax, eax ; return 0
	ret


public longjmp
longjmp:
	
	xor eax, eax
	inc eax
	ret
	
