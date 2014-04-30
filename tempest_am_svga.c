/*
 * tempest_am_svga.c
 * 
 * Copyright (c) 1999 Pekka Riikonen, priikone@poseidon.pspt.fi.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * 1999-08-18:  By Pekka Riikonen <priikone@poseidon.pspt.fi>
 *		- moved all the signal calculation to signal.c
 *		- other minor code change and regrouping
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <vga.h>
#include <vgagl.h>

#include "signal.h"
#include "common.h"

static void usage();
static void draw_signal();
static void init_screen();
static void supported_resos();

/* default command line options. These works
for me but may not work for you. */
static int o_fp = 135;
static int o_fh = 1776;
static int o_fv = 908;
static double o_tone = 1000;
static double o_carr = 12000000;
static int o_res_x = 1024;
static int o_res_y = 768;
static int o_res = 12;
static int o_pgm = 0;
static int o_square = 0;

int main(int argc, char **argv)
{
	int i;

	if (argc > 1) {
		for (i = 0; i < argc; i++) {
			if (!strcmp(argv[i], "-r")) {
				o_fp = atoi(argv[++i]);
				continue;
			}
			if (!strcmp(argv[i], "-h")) {
				o_fh = atoi(argv[++i]);
				continue;
			}
			if (!strcmp(argv[i], "-v")) {
				o_fv = atoi(argv[++i]);
				continue;
			}
			if (!strcmp(argv[i], "-t")) {
				o_tone = atof(argv[++i]);
				continue;
			}
			if (!strcmp(argv[i], "-c")) {
				o_carr = atof(argv[++i]);
				continue;
			}
			if (!strcmp(argv[i], "-s")) {
				o_res_x = atoi(argv[++i]);
				o_res_y = atoi(argv[++i]);
				continue;
			}
			if (!strcmp(argv[i], "-n")) {
				o_res = atoi(argv[++i]);
				continue;
			}
			if (!strcmp(argv[i], "-q")) {
				o_square = 1;
				continue;
			}
			if (!strcmp(argv[i], "-p")) {
				o_pgm = 1;
				continue;
			}
			if (!strcmp(argv[1], "-V"))
				usage();
		}

		if (!o_fp || !o_fh || !o_fv || !o_tone || !o_carr 
			|| !o_res_x || !o_res_y || !o_res)
				usage();
	}

	fprintf(stderr, "Carrier frequency: %.4f MHz\n", (double)o_carr / 1e6);
	fprintf(stderr, "   Tone frequency: %.2f Hz\n", (double)o_tone);

	if (o_pgm)
		generate_pgm(o_fp, o_fh, o_fv, o_tone, 
				o_carr, o_res_x, o_res_y, o_square);
	else
		draw_signal();

	return 0;
}

/*
 * Displays usage.
 */
static void usage()
{
	fprintf(stderr, "Usage: tempest_am_svga [-rhvtcsnV]\n");
	fprintf(stderr, "  -r <clock>      Resolution clock rate (from XF86Config)\n");
	fprintf(stderr, "  -h <htotal>     Resolution horizontal total timing (from XF86Config)\n");
	fprintf(stderr, "  -v <vtotal>     Resolution vertical total timing (from XF86Config)\n");
	fprintf(stderr, "  -t <tone>       Tone frequency to broadcast (Hz)\n");
	fprintf(stderr, "  -c <carrier>    Carrier frequency to broadcast (Hz)\n");
	fprintf(stderr, "  -s <w h>        Window size (eg. 1152 864) (default: 1024x768)\n");
	fprintf(stderr, "  -n <resolution> SVGA library resolution number (see below) (default: 12)\n");
	fprintf(stderr, "  -q              Use square waves\n");
	fprintf(stderr, "  -p              Generate PGM picture of the signal\n");
	fprintf(stderr, "  -V              This message\n");
	fprintf(stderr, "Version 1.0, (c) 1999 - 2001 priikone@poseidon.pspt.fi\n");
	fprintf(stderr, "\nNOTE: Monitor may not transmit the signal on low resolutions!\n");
	supported_resos();
	exit(0);
}

/*
 * Generates and shows the AM signal on screen.
 */
static void draw_signal()
{
	int i, x, y;
	double R, p;
	Signal ns;
	double *signal;

	ns.o_fp = o_fp;
	ns.o_fh = o_fh;
	ns.o_fv = o_fv;
	ns.o_tone = o_tone;
	ns.o_carr = o_carr;
	ns.o_res_x = o_res_x;
	ns.o_res_y = o_res_y;
	ns.o_square = o_square;

	signal = (double *)NULL;
	signal = generate_am_signal(&ns);

	/* Init the screen */
	init_screen();

	srand((unsigned int)time(0));
	i = 0;
	for (y = 0; y < o_res_y; y++) {
		for (x = 0; x < o_res_x; x++) {
			R = 1+(double) (1.0*rand() / (RAND_MAX+1.0)) - 1;
			p = ((double)127.5 + signal[i++]) + R;
			gl_setpixelrgb(x, y, (int)p, (int)p, (int)p);
		}
	}

	getchar();

	if (signal)
		free(signal);
}

/*
 * Initialises the screen.
 */
static void init_screen()
{
	int i;
	vga_modeinfo *modeinfo;

	vga_init();

	if (!vga_hasmode(o_res)) {
            fprintf(stderr, "Video mode not supported by driver\n");
            exit(1);
	}

	vga_setmodeX();
	vga_setmode(o_res);
	modeinfo = vga_getmodeinfo(o_res);

	printf("Width: %d  Height: %d  Colors: %d\n",
           modeinfo->width,
           modeinfo->height,
           modeinfo->colors);
	printf("DisplayStartRange: %xh  Maxpixels: %d  Blit: %s\n",
           modeinfo->startaddressrange,
           modeinfo->maxpixels,
           modeinfo->haveblit ? "YES" : "NO");

	gl_setcontextvga(o_res);
	vga_ext_set(VGA_CLUT8);

	for (i = 0; i < 255; i++)
	    vga_setpalette(i + 1, i, i, i);
}

/*
 * Displays supported resolutions by video card.
 */
static void supported_resos()
{
	int i;
	vga_modeinfo *modeinfo;

	for (i = 0; i < vga_lastmodenumber(); i++) {
		if (vga_hasmode(i)) {
			modeinfo = vga_getmodeinfo(i);
			
			if (modeinfo->colors == 256) 
				fprintf(stderr, "%5d: %dx%dx%d\n", 
				i, modeinfo->width, modeinfo->height,
				modeinfo->colors);
		}
	}
}
