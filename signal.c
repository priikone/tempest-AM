/*
 * signal.c
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
 * 1999-08-21:  By Pekka Riikonen <priikone@poseidon.pspt.fi>
 *		- much improved AM signal calculation
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "signal.h"

/*
 * Generates the AM signal.
 */
double *generate_am_signal(Signal *ps)
{
	unsigned int x, y, i;
	double fc, ft, fp, A;
	double pi2, m, t, tmp1, tmp2;
	double *signal;

	/* 
	 * Monitor frequency's. 
	 * 
	 * Example line from XF86Config:
	 *
	 * Modeline "1152x864"  135 
	 * 			1152 1464 1592 1776
	 * 			 864  864  876  908
	 * fp = 135
	 * ft = tone frequency to be broadcasted
	 * fc = carrier frequency 
	 */
	fp = ps->o_fp * 1e6;		/* Mhz */
	ft = ps->o_tone;		/* Tone (Hz) */
	fc = ps->o_carr;		/* Carrier (Hz) */

	/* Settings and pre-calculations */
	A = 255 / 4.0;			/* amplitude */
	m = 1.0;			/* amplitude */
	pi2 = (2 * M_PI);		/* 2 * pi */

	/*
	 * Pre-calculate the AM signal.
	 */
	signal = (double *)malloc(sizeof(double) * 
				  (ps->o_res_x * ps->o_res_y));
	i = 0;
	t = 0;
	for (y = 0; y < ps->o_res_y; y++) {
	    tmp1 = cos(pi2 * t * ft / fp + M_PI);
	    if (ps->o_square)
		tmp1 = (tmp1 < 0) ? -1 : 1;
 	    for (x = 0; x < ps->o_res_x; x++) {
		tmp2 = cos(pi2 * t * fc / fp);
		signal[i++] = A * tmp2 * (m + tmp1);
		t++;
 	    }
	    t += ps->o_fh - ps->o_res_x;
 	}

	return signal;
}

/*
 * Generates the FM signal.
 */
double *generate_fm_signal(Signal *ps)
{

	return 0;
}
