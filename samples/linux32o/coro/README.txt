Coroutine implementation.
This implementation uses a mix of Assembly and Oberon for assymetric coroutines.
It also implements a trap mechanism, which was added to "API_sys" module.

Requirements:
- Oberon-07 compiler with linux32o support (compilerX)
- ld linker
- make
- fasm (https://flatassembler.net/)
- cc compiler (optional)

Building:
- Use "make all" for building all examples.
