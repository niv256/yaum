# yaum
### yet another untitled mrhfla

## Build a i686 elf gcc Cross Compiler:

In order to run the project, follow the following guides:
1. https://github.com/rm-hull/barebones-toolchain
2. http://crosstool-ng.github.io/docs/install/#clone
3. http://crosstool-ng.github.io/docs/install/#install-method

When you do `ct-ng menuconfig` make sure you select the option:
Target options -> Target architecture (x86) -> x86

## Build and Run the kernel:

# Build and Run:
1. Make sure you have qemu installed, and run `run.sh` to build and run the kernel in qemu.

# Build Only:
1. Run `build.sh`.

# Debug with gdb:
1. Run `gdb.sh` in terminal 1.
2. Run `debug.sh` in terminal 2, and execute the printed commands in gdb.
3. Continue debugging with gdb as you wish.
