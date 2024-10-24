;***************************************************************************
; Source: https://github.com/spc476/C-Coroutines

format ELF

section '.text' executable

L_co = -4
L_fun =	-8
C_param	= -12

start_it_up:
	push eax
	push dword [ebp + L_co]
	call dword [ebp + L_fun]

do_it_again:
	mov	[ebp + C_param],eax
	call coroutine_yield32
	jmp	 do_it_again

;===========================================================================

P_stack = 12
P_fun = 8
P_co = 4

public coroutine_init32
coroutine_init32:
	mov edx,[esp + P_co]
	mov eax,[esp + P_stack]	; stack to switch to

	;------------------------------------------------------------
	; Create the stack for resuming to start_it_up().  The stack
	; is set up as:
	;
	;       EAX ->
	;		+--------------------------+
	;		| L_co                     |
	;		+--------------------------+
	;		| L_fun                    |
	;		+--------------------------+
	;		| start_it_up              |
	;		+--------------------------+
	;     co EBP -> | EBP of start_it_up (EAX) |
	;		+--------------------------+
	;		| "saved" EBX (0)          |
	;		+--------------------------+
	;		| "saved" ESI (0)          |
	;		+--------------------------+
	;     co ESP -> | "saved" EDI (0)          |
	;		+--------------------------+
	;
	; The code in coroutine.resume() will pop the three registers off
	; the stack, then restore EBP/ESP and "return" to start_it_up.
	;------------------------------------------------------------

	lea	ecx,[eax - 28]
	mov	[ecx + 12],eax		; EBP of coroutine
	mov	[ecx + 24],edx		; L_co
	mov	eax,[esp + P_fun]	; L_fun
	mov	[ecx + 20],eax
	mov	dword [ecx + 16],start_it_up
	xor	eax,eax
	mov	[ecx + 8],eax		; "saved" EBX
	mov	[ecx + 4],eax		; "saved" ESI
	mov	[ecx + 0],eax		; "saved" EDI
	mov	[edx],ecx		
	ret

;===========================================================================

P_param = 8 + 16
P_co = 4 + 16

public coroutine_yield32
coroutine_yield32:
	push ebp			; save callee saved registers
	push ebx
	push esi
	push edi

	mov eax,[esp + P_param]	; return parameter
	mov edx,[esp + P_co]	; get stack to yield to
	xchg esp,[edx]		; YIELD!

	pop	edi			; retore registers
	pop	esi
	pop	ebx
	pop	ebp
	ret

;***************************************************************************

section '.note.GNU-stack'
