#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>

#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug
#endif

//see Rotations/Reflections in man Xrandr
#define normal 1
#define left 1<<1
#define inverted 1<<2
#define right 1<<3


struct _XHead {
	Display *display;
	Window root;
	int screen;
};

struct _XRR {
	XRRScreenConfiguration *screen_config;
	SizeID size;
	Rotation rotation;
};

struct _options {
	unsigned int verbose:1; //currently not used
	unsigned int force:1;
};


typedef struct _XHead XHead;
typedef struct _XRR XRR;
typedef struct _options options;

void help() {
	printf("pivot: switching between two alternating  screen rotations\n");
	printf("usage: pivot [options] [ rotation_1 [ rotation_2 ]]\n");
	printf("  -h, --help     prints help\n");
	printf("  -d, --display  display\n");
	printf("  -f, --force    force switching\n");
	printf("\n");
	printf("rotations: left, right, normal, inverted\n");
	printf("  default: left, normal\n");
	printf("\n");
	printf("examples:\n");
	printf("  pivot -d :1 right\n");
	printf("  pivot left normal\n");
	printf("\n");
}

int main(int argc, char **argv) {
	XHead xhead;
	XRR xrr;
	char *disp_name = NULL;
	Rotation rotations = 0;
	int i;
	options opts;
	opts.force   = 0;
	int r_opts  = 2;


	for (i=1; i < argc; i++) {
		if ( !strcmp(argv[i],"-h") || !strcmp(argv[i],"--help") ) {
			help();
			return 0;
		}
		if ( (!strcmp(argv[i],"-d") || !strcmp(argv[i],"--display")) && (++i < argc)) {
			disp_name = argv[i];
			continue;
		}
		if ( !strcmp(argv[i],"-f") || !strcmp(argv[i],"--force") ) {
			opts.force = 1;
			continue;
		}
		if (r_opts > 0) {
			if (!strcmp(argv[i],"normal"))   { rotations |= normal;   r_opts--;}
			if (!strcmp(argv[i],"left"))     { rotations |= left;     r_opts--;}
			if (!strcmp(argv[i],"inverted")) { rotations |= inverted; r_opts--;}
			if (!strcmp(argv[i],"right"))    { rotations |= right;    r_opts--;}
		}
	}
	//setting default rotations
	for (; r_opts > 0; r_opts--) {
		rotations |= 1<<(r_opts-1);
	}

	xhead.display = XOpenDisplay(disp_name);
	xhead.screen  = DefaultScreen(xhead.display);
	xhead.root    = RootWindow(xhead.display,xhead.screen);

	xrr.screen_config = XRRGetScreenInfo(xhead.display,xhead.root);
	xrr.size = XRRConfigCurrentConfiguration(xrr.screen_config,&xrr.rotation);

	if ( !(xrr.rotation & rotations & 0xff) ) { //current orientation sucks :)
		if (opts.force) {
			for (i = 4; i >= 0; i--) 
				if ( 0xff & (xrr.rotation = rotations & (1<<i)) ) break;
		}
		else {
			fprintf(stderr, "current display rotation is not in given rotations\n");
			fprintf(stderr, "use -f option, if you want to force switching\n");
			return 1;
		}
	}

	//switching rotation
	xrr.rotation ^= rotations;

	if( !XRRSetScreenConfig(xhead.display,xrr.screen_config,xhead.root,
							  xrr.size, xrr.rotation,CurrentTime)
		) return 0;
	else {
		fprintf(stderr,"Failure setting screen rotation\n");
		return 2;
	}
	

}

