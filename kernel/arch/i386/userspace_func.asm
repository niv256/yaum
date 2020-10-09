[BITS 32]

global userspace_func

userspace_func:
  mov eax, 0xdeadbeef
  int 0x80
  jmp $
  ret ; never gets here
