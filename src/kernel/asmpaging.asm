global set_paging

set_paging:
  ; page directory address
  mov eax, [esp+4]
  mov cr3, eax

  ; cr0 32th bit
  mov eax, cr0
  or eax, 1<<32
  mov cr0, eax

  ret

