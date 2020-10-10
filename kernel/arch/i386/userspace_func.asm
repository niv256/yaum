[BITS 32]

global userspace_func

userspace_func:
  mov eax, 0 ; very important syscall
  int 0x80
  jmp $
  ret ; never gets here
