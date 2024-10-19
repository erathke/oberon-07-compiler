Embeding Lua example.
This example embeds the Lua scripting language (https://lua.org/) into Oberon-07.

Requirements:
- Oberon-07 compiler with linux32o support (compilerX).
- cc compiler.

Building:
- Use "make all".
	- "make hello" and "make userdata" for separated builds.

Usage:
- hello: ./bin/HelloLua hello.lua
- userdata: ./bin/Userdata udata.lua
