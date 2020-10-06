global enable_a20
global set_pmode

enable_a20:
  in al, 0x92
  or al, 2
  out 0x92, al
  ret

set_pmode:
  mov eax, cr0
  or eax, 1
  mov cr0, eax

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
