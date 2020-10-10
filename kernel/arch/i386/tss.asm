global tss_write

TSS_INDEX             equ 5
SELECTOR_SHIFT_AMOUNT equ 3

tss_write:
  mov ax, TSS_INDEX << SELECTOR_SHIFT_AMOUNT
  ltr ax
  ret

