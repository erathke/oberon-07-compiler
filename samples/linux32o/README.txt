This branch is a extended version of the compiler with the "linux32o" option.
This option generates ELF relocatable files that can be linked with another applications.
The motivations/usage are:
- Implement in Oberon parts of an application;
- Create static Oberon applications;
- Testing Oberon as a replacement for C/C++.

This directory contains some examples:
- assert: Example of a static application using Linux Syscalls instead of libc calls;
- dockapp: An application for testing X11 development;
- kernel: Simple multiboot compliant kernel mixing Assembly and Oberon;
- lua: Embeding an scripting language in Oberon;
- microui: UI example.


Known issues:
- Extern procedures cannot be assigned or passed as parameters;
- For the sake of simplicity, the "-rtl" option was created in the compiler.
A better option can be search for module replacement in the application root folder.
- When "-entry" option is defined, it also includes an implicit API._exit at the end of the entry.
I'm not sure if it is the correct behaviour.
- The implementation was quite conservative, avoiding to replace/change existent code.
When possible, the code was duplicated with new functionality.
