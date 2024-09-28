#include <stdio.h>
#include <libdockapp/dockapp.h>

extern Display *DADisplay;
extern Window DAWindow;
extern GC DAGC;

void setWindowAndDisplay(Window *window, Display **display) {
	*window = DAWindow;
	*display = DADisplay;
}

void setGC(GC *gc) {
	*gc = DAGC;
}
