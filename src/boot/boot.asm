[BITS 16]
[ORG 0x7c00]

mov si,msg
call prints
jmp $

prints:
	mov ah, 0x0e
	printc:
		lodsb
		cmp al, 0
		jz return
		int 0x10
		jmp printc
	return:
		ret

msg db "Hello World!", 0

TIMES 510-($-$$) db 0
dw 0xaa55
