IRQ_BASE = 0x20

macro HandleException num {
	public HandleException#num
	
	HandleException#num:
        ;push    dword 0                     ; push 0 as error code
        ;push    dword num                   ; push the interrupt number
        mov eax, num
        mov [interruptnumber], eax
        jmp     common_interrupt_handler    ; jump to the common handler
}

macro HandleInterruptRequest num {
	public HandleInterruptRequest#num
	
	HandleInterruptRequest#num:
        ;push    dword 0                     ; push 0 as error code
        ;push    dword num + IRQ_BASE       ; push the interrupt number
        mov eax, num + IRQ_BASE
        mov [interruptnumber], eax
        jmp     common_interrupt_handler    ; jump to the common handler
}


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
	
	;call    kernelInterruptHandler
	push 0x00
	push dword [interruptnumber]
	call kernelInterruptHandler
	;call CKernelInterruptHandler
	
	; restore the registers
	pop eax
	pop ebx
	pop ecx
	pop edx
	pop esi
	pop edi
	pop ebp
	

	; restore the esp
	;add     esp, 8

public InterruptIgnore
InterruptIgnore:
	; return to the code that got interrupted
	iret

