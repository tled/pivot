
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>

static Display *display;
static Window root_win;
static int screen = -1;


int main(int argc, char **argv) {

	short current_rate;
	Rotation current_rotation;
	int size = -1;
	XRRScreenConfiguration *screen_config;

	char *display_name = NULL;

	display = XOpenDisplay(display_name);
	screen = DefaultScreen(display);
	root_win = RootWindow(display,screen);
	screen_config = XRRGetScreenInfo(display,root_win);

	current_rate = XRRConfigCurrentRate(screen_config);
	size = XRRConfigCurrentConfiguration(screen_config,&current_rotation);

	printf("Rotation: %d\n",current_rotation);
	printf("Size: %d\n",size);
	printf("Rate: %d\n",current_rate);


}

