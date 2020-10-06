global gdt_write

gdt_write:
	mov eax, [esp+4]
	lgdt [eax]
	ret
