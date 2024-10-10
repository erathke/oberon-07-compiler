IRQ_BASE = 0x20

interruptnumber: rb 1

macro HandleException num {
	HandleException#num:
		;cli ; disable interrupts? 
		push 0x00
        mov [interruptnumber], dword num
        jmp     common_interrupt_handler    ; jump to the common handler
}

macro HandleInterruptRequest num {
	HandleInterruptRequest#num:
		;cli ; disable interrupts?
        mov [interruptnumber], dword num + IRQ_BASE
        jmp     common_interrupt_handler    ; jump to the common handler
}

; TODO: check if the exceptions are ok
; Exceptions
HandleException 0x00
HandleException 0x01
HandleException 0x02
HandleException 0x03
HandleException 0x04
HandleException 0x05
HandleException 0x06
HandleException 0x07
HandleException 0x08
HandleException 0x09
HandleException 0x0A
HandleException 0x0B
HandleException 0x0C
HandleException 0x0D
HandleException 0x0E
HandleException 0x0F
HandleException 0x10
HandleException 0x11
HandleException 0x12
HandleException 0x13
; Hardware interrupts
HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31
; Syscalls
HandleInterruptRequest 0x80


common_interrupt_handler:               ; the common parts of the generic interrupt handler
	; save the registers
	push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax
	
	push esp
	push dword [interruptnumber]
	call kernelInterruptHandler
	mov esp, eax ; assign new esp
	
	; restore the registers
	pop eax
	pop ebx
	pop ecx
	pop edx
	pop esi
	pop edi
	pop ebp

InterruptIgnore:
	;sti ; enable interrupts?
	; return to the code that got interrupted
	;push 0x22
	;call kernelPrintInt
	iret


set_handlers:
	push ebp
	mov ebp, esp
	push eax
	
	mov eax, [ebp + 8]
	; exceptions offset = 0x00
	mov [eax + 0], dword HandleException0x00
	mov [eax + 4], dword HandleException0x01
	mov [eax + 8], dword HandleException0x02
	mov [eax + 12], dword HandleException0x03
	mov [eax + 16], dword HandleException0x04
	mov [eax + 20], dword HandleException0x05
	mov [eax + 24], dword HandleException0x06
	mov [eax + 28], dword HandleException0x07
	mov [eax + 32], dword HandleException0x08
	mov [eax + 36], dword HandleException0x09
	mov [eax + 40], dword HandleException0x0A
	mov [eax + 44], dword HandleException0x0B
	mov [eax + 48], dword HandleException0x0C
	mov [eax + 52], dword HandleException0x0D
	mov [eax + 56], dword HandleException0x0E
	mov [eax + 60], dword HandleException0x0F
	mov [eax + 64], dword HandleException0x10
	mov [eax + 68], dword HandleException0x11
	mov [eax + 72], dword HandleException0x12
	mov [eax + 76], dword HandleException0x13
	; hardware offset = 0x20
	mov eax, [ebp + 8]
	add eax, 0x20 * 4 ; offset * 4
	mov [eax + 0], dword HandleInterruptRequest0x00
	mov [eax + 4], dword HandleInterruptRequest0x01
	mov [eax + 8], dword HandleInterruptRequest0x02
	mov [eax + 12], dword HandleInterruptRequest0x03
	mov [eax + 16], dword HandleInterruptRequest0x04
	mov [eax + 20], dword HandleInterruptRequest0x05
	mov [eax + 24], dword HandleInterruptRequest0x06
	mov [eax + 28], dword HandleInterruptRequest0x07
	mov [eax + 32], dword HandleInterruptRequest0x08
	mov [eax + 36], dword HandleInterruptRequest0x09
	mov [eax + 40], dword HandleInterruptRequest0x0A
	mov [eax + 44], dword HandleInterruptRequest0x0B
	mov [eax + 48], dword HandleInterruptRequest0x0C
	mov [eax + 52], dword HandleInterruptRequest0x0D
	mov [eax + 56], dword HandleInterruptRequest0x0E
	mov [eax + 60], dword HandleInterruptRequest0x0F
	mov [eax + 64], dword HandleInterruptRequest0x31
	; syscall offset = 0x80
	mov eax, [ebp + 8]
	add eax, 0x80 * 4 ; offset * 4
	mov [eax + 0], dword HandleInterruptRequest0x80
	
	pop eax
	pop ebp
	ret
