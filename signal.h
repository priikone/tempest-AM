/*
 * signal.h
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

#ifndef _SIGNAL_H
#define _SIGNAL_H

typedef struct {
	int o_fp;
	int o_fh;
	int o_fv;
	double o_tone;
	double o_carr;
	int o_res_x;
	int o_res_y;
	int o_square;
} Signal;

double *generate_am_signal(Signal *ps);
double *generate_fm_signal(Signal *ps);

#endif
