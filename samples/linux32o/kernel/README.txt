An multiboot compliant kernel example.
This is an example for building bare metal applications.

Requirements:
- Oberon-07 compiler with linux32o support (compilerX)
- ld linker
- make
- fasm (https://flatassembler.net/)
- qemu
- ISO build:
	grub-mkrescue and xorriso

Building:
- Use "make kernel" for running on qemu.
- Optionally, you can build an ISO using "make iso".

Usage:
- Use "make run" for running on qemu.
- Or use the generated ISO to boot on real hardware/qemu.
