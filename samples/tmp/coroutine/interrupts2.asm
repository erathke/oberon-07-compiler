IRQ_BASE = 0x20

;interruptnumber: rb 1

macro ISR_ERRCODE num {
	ISR_ERRCODE_#num:
		;cli ; disable interrupts? 
        ;mov [interruptnumber], dword num
        push 0x00
        push num
        jmp  int_common_stub    ; jump to the common handler
}

macro ISR_NOERRCODE num {
	ISR_NOERRCODE_#num:
		;cli ; disable interrupts? 
        ;mov [interruptnumber], dword num
        push num
        jmp  int_common_stub    ; jump to the common handler
}

macro IRQ num {
	IRQ_#num:
		;cli ; disable interrupts?
		push 0x00	
        push num + IRQ_BASE
        jmp  int_common_stub    ; jump to the common handler
}

; TODO: check if the exceptions are ok
; Exceptions
ISR_NOERRCODE 0x00
ISR_NOERRCODE 0x01
ISR_NOERRCODE 0x02
ISR_NOERRCODE 0x03
ISR_NOERRCODE 0x04
ISR_NOERRCODE 0x05
ISR_NOERRCODE 0x06
ISR_NOERRCODE 0x07
ISR_ERRCODE 0x08
ISR_NOERRCODE 0x09
ISR_ERRCODE 0x0A
ISR_ERRCODE 0x0B
ISR_ERRCODE 0x0C
ISR_ERRCODE 0x0D
ISR_ERRCODE 0x0E
ISR_NOERRCODE 0x0F
ISR_NOERRCODE 0x10
ISR_NOERRCODE 0x11
ISR_NOERRCODE 0x12
ISR_NOERRCODE 0x13
; Hardware interrupts
IRQ 0x00
IRQ 0x01
IRQ 0x02
IRQ 0x03
IRQ 0x04
IRQ 0x05
IRQ 0x06
IRQ 0x07
IRQ 0x08
IRQ 0x09
IRQ 0x0A
IRQ 0x0B
IRQ 0x0C
IRQ 0x0D
IRQ 0x0E
IRQ 0x0F
IRQ 0x31
; Syscalls
IRQ 0x80


int_common_stub:               ; the common parts of the generic interrupt handler
	; save the registers
	push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax
	
	push esp
	;push dword [interruptnumber]
	call kernelInterruptHandler
	;add esp, 0x8
	;push eax
	;push eax
	;call kernelPrintInt
	;pop eax
	;mov esp, eax ; assign new esp
	
	; restore the registers
	pop eax
	pop ebx
	pop ecx
	pop edx
	pop esi
	pop edi
	pop ebp
    ;ADD esp, 8
    ;STI
    iret


set_handlers:
	push ebp
	mov ebp, esp
	push eax
	
	mov eax, [ebp + 8]
	; exceptions offset = 0x00
	mov [eax + 0], dword ISR_NOERRCODE_0x00
	mov [eax + 4], dword ISR_NOERRCODE_0x01
	mov [eax + 8], dword ISR_NOERRCODE_0x02
	mov [eax + 12], dword ISR_NOERRCODE_0x03
	mov [eax + 16], dword ISR_NOERRCODE_0x04
	mov [eax + 20], dword ISR_NOERRCODE_0x05
	mov [eax + 24], dword ISR_NOERRCODE_0x06
	mov [eax + 28], dword ISR_NOERRCODE_0x07
	mov [eax + 32], dword ISR_ERRCODE_0x08
	mov [eax + 36], dword ISR_NOERRCODE_0x09
	mov [eax + 40], dword ISR_ERRCODE_0x0A
	mov [eax + 44], dword ISR_ERRCODE_0x0B
	mov [eax + 48], dword ISR_ERRCODE_0x0C
	mov [eax + 52], dword ISR_ERRCODE_0x0D
	mov [eax + 56], dword ISR_ERRCODE_0x0E
	mov [eax + 60], dword ISR_NOERRCODE_0x0F
	mov [eax + 64], dword ISR_NOERRCODE_0x10
	mov [eax + 68], dword ISR_NOERRCODE_0x11
	mov [eax + 72], dword ISR_NOERRCODE_0x12
	mov [eax + 76], dword ISR_NOERRCODE_0x13
	; hardware offset = 0x20
	mov eax, [ebp + 8]
	add eax, 0x20 * 4 ; offset * 4
	mov [eax + 0], dword  IRQ_0x00
	mov [eax + 4], dword  IRQ_0x01
	mov [eax + 8], dword  IRQ_0x02
	mov [eax + 12], dword IRQ_0x03
	mov [eax + 16], dword IRQ_0x04
	mov [eax + 20], dword IRQ_0x05
	mov [eax + 24], dword IRQ_0x06
	mov [eax + 28], dword IRQ_0x07
	mov [eax + 32], dword IRQ_0x08
	mov [eax + 36], dword IRQ_0x09
	mov [eax + 40], dword IRQ_0x0A
	mov [eax + 44], dword IRQ_0x0B
	mov [eax + 48], dword IRQ_0x0C
	mov [eax + 52], dword IRQ_0x0D
	mov [eax + 56], dword IRQ_0x0E
	mov [eax + 60], dword IRQ_0x0F
	mov [eax + 64], dword IRQ_0x31
	; syscall offset = 0x80
	mov eax, [ebp + 8]
	add eax, 0x80 * 4 ; offset * 4
	mov [eax + 0], dword IRQ_0x80
	
	pop eax
	pop ebp
	ret
