;***************************************************************************
; Original source: https://github.com/spc476/C-Coroutines

format ELF

section '.bss' writeable

CORO_DEAD: rw 1

;***************************************************************************

section '.text' executable

public coroutine_setup
public coroutine_init32
public coroutine_yield32

;===========================================================================

P_dead = 4

coroutine_setup:
	mov eax, [esp + P_dead]
	mov [CORO_DEAD], eax
	ret

;===========================================================================

L_co = -4
L_fun =	-8
C_param	= -12

start_coro:
	push eax
	push dword [ebp + L_co]
	call dword [ebp + L_fun]

finish_coro:
	mov eax, [CORO_DEAD]
	mov	[ebp + C_param], eax
	call coroutine_yield32
	jmp	 finish_coro


P_stack = 12
P_fun = 8
P_co = 4

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
	mov	dword [ecx + 16],start_coro
	xor	eax,eax
	mov	[ecx + 8],eax		; "saved" EBX
	mov	[ecx + 4],eax		; "saved" ESI
	mov	[ecx + 0],eax		; "saved" EDI
	mov	[edx],ecx		
	ret

;===========================================================================

P_status = 8 + 16
P_co = 4 + 16

coroutine_yield32:
	push ebp			; save callee saved registers
	push ebx
	push esi
	push edi

	mov eax,[esp + P_status]	; return parameter
	mov edx,[esp + P_co]		; get stack to yield to
	xchg esp,[edx]				; YIELD!

	pop	edi			; retore registers
	pop	esi
	pop	ebx
	pop	ebp
	ret

;***************************************************************************

section '.note.GNU-stack'
