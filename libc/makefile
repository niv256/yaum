include objects.mk

BUILD:=libc.a
BUILD_OBJS:=$(LIBC_OBJS)

.PHONY: all $(BUILD) clean

all: $(BUILD)

install: $(BUILD)

$(BUILD): $(BUILD_OBJS)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	$(shell rm -rf $(BUILD) $(BUILD_OBJS))
