An application for setting screen backlight brightness.

Requirements:
- Oberon-07 compiler with linux32o support (compilerX)
- cc compiler
- make
- X11 and dockapp libraries (-lX11 -ldockapp)
- udevd configuration:
	- add user to video group
	- configure udevd rules (./conf/90-backlight.rules)

Building:
- Use "make exe"

Usage:
- Find the device name: 
	- On Debian: ls /sys/class/backlight
- Execute the application specifying the device:
	- ./bin/wmbacklight -d acpi_video0
- Use mouse scroll button to adjust the brightness
