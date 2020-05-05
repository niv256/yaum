global gdt_write

; loading the gdt to the process
gdt_write:
	mov eax, [esp+4]
	lgdt [eax]
	; reload cs register
	jmp 0x08:r_segment


; reload segment registers
r_segment:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
