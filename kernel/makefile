include ../libc/objects.mk

LIBC_OBJS_KERNEL=$(addsuffix -kernel,$(addprefix ../libc/,$(LIBC_OBJS)))
BUILD:=yaum.bin

include objects.mk

.PHONY: all clean

all: $(BUILD)

$(BUILD): $(OBJECTS) $(LIBC_OBJS_KERNEL)
	$(LD) $^ -o $@ $(LD_FLAGS)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

%.o-kernel: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	$(shell rm -rf $(OBJECTS) $(LIBC_OBJS_KERNEL) $(BUILD))
