include modules.mk

MODULES_DIR:='/modules/'
MODULES:=$(EXEC) $(TEXT)

.PHONY: all $(MODULES) clean progtest

all: $(MODULES) progtest
	$(shell cp ../isodir/boot/grub/menu.lst.clean ../isodir/boot/grub/menu.lst)
	$(shell cat modules >> ../isodir/boot/grub/menu.lst)

# assuming EXEC are asm files
$(EXEC): clean
	$(ASM) $(ASM_MODS_FLAGS) -o ../isodir/modules/$@ $@.asm
	$(call write_to_modules,$@)

$(TEXT): clean
	$(shell cp $@ ../isodir/modules/$@)
	$(call write_to_modules,$@)

clean:
	$(shell truncate --size 0 modules)
	$(shell rm ../isodir/boot/grub/menu.lst)

define write_to_modules
	echo -n 'module ' >> modules
	echo -n $(MODULES_DIR) >> modules
	echo $@ >> modules
endef
