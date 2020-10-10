[BITS 32]

extern userspace_func

SELECTOR_SHIFT_AMOUNT equ 3
USER_CODE_INDEX       equ 3
USER_DATA_INDEX       equ 4
DPL3                  equ 3
IF_FLAG               equ 0x200

USER_CODE equ ((USER_CODE_INDEX << SELECTOR_SHIFT_AMOUNT) |  DPL3)
USER_DATA equ ((USER_DATA_INDEX << SELECTOR_SHIFT_AMOUNT) |  DPL3)

global jump_usermode

jump_usermode:
  mov ecx, [esp+4]

  mov ax, USER_DATA
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  push eax

  push esp

  pushf
  pop eax
  or eax, IF_FLAG
  push eax

  push USER_CODE

  push ecx

  iret
