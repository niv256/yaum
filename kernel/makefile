include objects.mk

.PHONY: all clean

all: yaum.bin

yaum.bin: $(OBJECTS)
	$(LD) $^ -o $@ $(LD_FLAGS)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	$(shell rm -rf *.o yaum.bin)
