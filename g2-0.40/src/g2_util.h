/*****************************************************************************
**  This is part of the g2 library
**  Copyright (C) 1998  Ljubomir Milanovic & Horst Wagner
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License (version 2) as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/
#ifndef _G2_UTIL_H
#define _G2_UTIL_H

#include <stdlib.h>
#include "g2_physical_device.h"

int  dtoi(double x);

void g2_uc2pdc_int(g2_physical_device *pd, double x, double y,
		   int *ix, int *iy);
void g2_uc2pdc_double(g2_physical_device *pd, double x, double y,
		      double *dx, double *dy);
void g2_us2pds_int(g2_physical_device *pd, double x, double y,
		   int *ix, int *iy);
void g2_us2pds_double(g2_physical_device *pd, double x, double y,
		      double *dx, double *dy);
void g2_sort2_i(int *a, int *b);
void g2_sort2_d(double *a, double *b);
void *g2_malloc(size_t size);
void *g2_realloc(void *p, size_t size);
void g2_free(void *p);


#endif /* _G2_UTIL_H */
