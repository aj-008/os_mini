; Defined in isr.c
[extern isr_handler]



global isr_stub_table
isr_stub_table:
    dd isr0
    dd isr1
    dd isr2
    dd isr3
    dd isr4
    dd isr5
    dd isr6
    dd isr7
    dd isr8
    dd isr9
    dd isr10
    dd isr11   
    dd isr12
    dd isr13
    dd isr14
    dd isr15
    dd isr16
    dd isr17
    dd isr18
    dd isr19
    dd isr20
    dd isr21
    dd isr22
    dd isr23
    dd isr24
    dd isr25
    dd isr26
    dd isr27
    dd isr28
    dd isr29
    dd isr30
    dd isr31
   
; Common ISR code
isr_common_stub:
	pusha
	mov ax, ds ; Lower 16-bits of eax = ds.
	push eax ; save the data segment descriptor
	mov ax, 0x10  ; kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	call isr_handler
	
	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8
	sti
	iret


%macro ISR_NOERR 1
global isr%1
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR 8
ISR_NOERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

