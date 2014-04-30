/*
 * tempest_am_X11.c
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
 * 1999-08-15:	By Patrice Lacroix <tootix@writeme.com>
 * 		- image drawing 2 times faster (lot of room to improve 
 *                further!)
 * 		- image no more inverted vertically
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
#include "g2-0.40/include/g2.h"
#include "g2-0.40/include/g2_X11.h"

#include "signal.h"
#include "common.h"

void usage();
void draw_signal();
int init_screen();

static int greyscale[256 + 1];

/* default command line options. */
static int o_fp = 135;
static int o_fh = 1776;
static int o_fv = 908;
static double o_tone = 1000;
static double o_carr = 12e6;
static int o_res_x = 1024;
static int o_res_y = 768;
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
			|| !o_res_x || !o_res_y)
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
void usage()
{
	fprintf(stderr, "Usage: tempest_am_X11 [-rhvtcsV]\n");
	fprintf(stderr, "  -r <clock>   Resolution clock rate (from XF86Config)\n");
	fprintf(stderr, "  -h <htotal>  Resolution horizontal total timing (from XF86Config)\n");
	fprintf(stderr, "  -v <vtotal>  Resolution vertical total timing (from XF86Config)\n");
	fprintf(stderr, "  -t <tone>   Tone frequency to broadcast (Hz)\n");
	fprintf(stderr, "  -c <carrier> Carrier frequency to broadcast (Hz)\n");
	fprintf(stderr, "  -s <w h>     Window size (eg. 1152 864) (default: 1024x768)\n");
	fprintf(stderr, "  -q           Use square waves\n");
	fprintf(stderr, "  -p           Generate PGM picture of the signal\n");
	fprintf(stderr, "  -V           This message\n");
	fprintf(stderr, "Version 1.0, (c) 1999 - 2001 priikone@poseidon.pspt.fi\n");
	exit(0);
}

/*
 * Generates and shows the AM signal on screen.
 */
void draw_signal()
{
	int i, sc;
	double R;
	Signal ns;
	double *signal;
	int *image, *p;

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
	sc = init_screen();

	srand((unsigned int)time(0));
	i = 0;
	image = malloc((o_res_x * o_res_y) * sizeof(int));
	p = image;
	for (i = 0; i < o_res_y * o_res_x; i++, p++) {
		R = 1 + (double) (1.0 * rand() / (RAND_MAX + 1.0)) - 1;
		*p = greyscale[(int)(127.5 + signal[i] + R)];
	}
	g2_image(sc, 0, 0, o_res_x, o_res_y, image);

	getchar();

	free(image);
	if (signal)
		free(signal);
}

/*
 * Initialises the screen.
 */
int init_screen()
{
	int sc, i, color;
	double c = 0.0;

	sc = g2_open_X11(o_res_x, o_res_y);

	/* init greyscale palette */
	for (i = 0; i < 255; i++) {
	    color = g2_ink(sc, c, c, c);
	    greyscale[i] = color;
	    c += 1.0 / 255;
	}

	return sc;
}
