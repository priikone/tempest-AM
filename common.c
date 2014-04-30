/*
 * common.c
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "signal.h"
#include "common.h"

/*
 * Generates Portable Bitmap picture file (type P5 PGM).
 */
void generate_pgm(int o_fp, int o_fh, int o_fv, double o_tone, 
		double o_carr, int o_res_x, int o_res_y, int o_square)
{
	int i, x, y;
	double p, R;
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

	fprintf(stdout, "P5\n");
	fprintf(stdout, "%d %d 255\n", o_res_x, o_res_y);

        srand((unsigned int)time(0));
        i = 0;
        for (y = 0; y < o_res_y; y++) {
                for (x = 0; x < o_res_x; x++) {
                        R = 1+(double) (1.0*rand() / (RAND_MAX+1.0)) - 1;
                        p = ((double)127.5 + signal[i++]) + R;
			if (p < 0)
				p = 0;
			if (p > 255)
				p = 255;
			putchar((int)p);
                }
        }

	fflush(stdout);

	if (signal)
		free(signal);
}
