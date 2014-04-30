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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "g2_util.h"
#include "g2_physical_device.h"


/*
 *
 * Double to integer
 *
 */
int dtoi(double x)
{
    return (int)(x+0.5);
}



/*
 *
 * Transform user coord. in phyisical device coord (int)
 *
 */
void g2_uc2pdc_int(g2_physical_device *pd, double x, double y,
		   int *ix, int *iy)
{
    double vx, vy;
    
    vx=pd->x_mul*x+pd->x_origin;
    vy=pd->y_mul*y+pd->y_origin;
    
    *ix = dtoi(pd->a11*vx + pd->b1);
    *iy = dtoi(pd->a22*vy + pd->b2);
}


/*
 *
 * Transform user coord. in phyisical device coord (double)
 *
 */
void g2_uc2pdc_double(g2_physical_device *pd, double x, double y,
		      double *dx, double *dy)
{
    double vx, vy;
    
    vx=pd->x_mul*x+pd->x_origin;
    vy=pd->y_mul*y+pd->y_origin;
    
    *dx = pd->a11*vx + pd->b1;
    *dy = pd->a22*vy + pd->b2;
}


/*
 *
 * Transform user size in phyisical device size (int)
 *
 */
void g2_us2pds_int(g2_physical_device *pd, double x, double y,
		   int *ix, int *iy)
{
    if(ix!=NULL)
	*ix=dtoi(x*fabs(pd->x_mul*pd->a11));
    if(iy!=NULL)
	*iy=dtoi(y*fabs(pd->y_mul*pd->a22));
}


/*
 *
 * Transform user size in phyisical device size (double)
 *
 */
void g2_us2pds_double(g2_physical_device *pd, double x, double y,
		      double *dx, double *dy)
{
    if(dx!=NULL)
	*dx=x*fabs(pd->x_mul*pd->a11);
    if(dy!=NULL)
	*dy=y*fabs(pd->y_mul*pd->a22);
}


/*
 *  return a < b
 */
void g2_sort2_i(int *a, int *b)
{
    if(*a>*b) {
	int t=*a;
	*a=*b; *b=t;
    }
}

void g2_sort2_d(double *a, double *b)
{
    if(*a>*b) {
	double t=*a;
	*a=*b; *b=t;
    }
}



/*
 *
 * g2 malloc (with error message)
 *
 */
void *g2_malloc(size_t size)
{
    void *rv;

    if((rv=malloc(size))==NULL) {
	fprintf(stderr, "g2_malloc: Can not allocate memory\n");
	exit(-1);
    }

    return rv;
}


/*
 *
 * g2 realloc (with error message)
 *
 */
void *g2_realloc(void *p, size_t size)
{
    void *rv;
    if((rv=realloc(p, size))==NULL) {
	fprintf(stderr, "g2_realloc: Can not allocate memory\n");
	exit(-1);
    }
    return rv;
}



/*
 *
 * g2 free
 *
 */
void g2_free(void *p)
{
    if(p!=NULL)
	free(p);
}
