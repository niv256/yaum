INCLUDEDIR:=$(PWD)/include
export CC:=i686-elf-gcc
export LD:=i686-elf-ld
export ASM:=nasm
export CC_FLAGS:=-c -Wall -ffreestanding -I$(INCLUDEDIR)
export LD_FLAGS:=-T linker.ld
export ASM_FLAGS:=-f elf
export ASM_MODS_FLAGS:=-f bin

MAKE:=make

SUBDIRS:=kernel modules libc
CLEANDIRS:=$(SUBDIRS:%=clean-%)

.PHONY: subdirs $(SUBDIRS) clean $(CLEANDIRS)

all: subdirs

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean: $(CLEANDIRS)

$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean
