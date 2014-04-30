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

#include "g2_device.h"
#include "g2_graphic_pd.h"
#include "g2_util.h"

/*
 *
 * Move graphic cursor
 *
 */
void g2_move(int dev, double x, double y)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_move: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;					  /* set graph. cursor */
    devp->y=y;

    switch(devp->t) {
      case g2_PD:
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_move(devp->d.vd->dix[i], x, y);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    __g2_last_device=dev;
}



/*
 *
 * Move graphic cursor relative to gc
 *
 */
void g2_move_r(int dev, double dx, double dy)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_move_r: No such device: %d\n", dev);
	return;
    }

    devp->x+=dx;				  /* set graph. cursor */
    devp->y+=dy;
    
    switch(devp->t) {
      case g2_PD:
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_move_r(devp->d.vd->dix[i], dx, dy);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    __g2_last_device=dev;
}



/*
 *
 * Plot
 *
 */
void g2_plot(int dev, double x, double y)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_plot: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;					  /* set graph. cursor */
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_plot_pd(devp->d.pd, x, y);    
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_plot(devp->d.vd->dix[i], x, y);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);
    
    __g2_last_device=dev;
}



/*
 *
 * Plot relative
 *
 */
void g2_plot_r(int dev, double rx, double ry)
{
    g2_device *devp;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_plot_r: No such device: %d\n", dev);
	return;
    }
    
    g2_plot(dev, devp->x+rx, devp->y+ry);
    
    __g2_last_device=dev;
}



/*
 *
 * Draw line
 *
 */
void g2_line(int dev, double x1, double y1, double x2, double y2)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_line: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x2;
    devp->y=y2;

    switch(devp->t) {
      case g2_PD:
	g2_line_pd(devp->d.pd, x1, y1, x2, y2);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_line(devp->d.vd->dix[i], x1, y1, x2, y2);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);
    
    __g2_last_device=dev;
}



/*
 *
 * Draw line relative to gc
 *
 */
void g2_line_r(int dev, double dx, double dy)
{
    g2_device *devp;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_line_r: No such device: %d\n", dev);
	return;
    }
    g2_line(dev, devp->x, devp->y, devp->x+dx, devp->y+dy);

    __g2_last_device=dev;
}



/*
 *
 * Draw line till point
 *
 */
void g2_line_to(int dev, double x, double y)
{
    g2_device *devp;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_line_to: No such device: %d\n", dev);
	return;
    }
    g2_line(dev, devp->x, devp->y, x, y);

    __g2_last_device=dev;
}



/*
 *
 * Draw poly line
 *
 */
void g2_poly_line(int dev, int N_pt, double *points)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_poly_line: No such device: %d\n", dev);
	return;
    }
    
    devp->x=points[2*(N_pt-1)+0];
    devp->y=points[2*(N_pt-1)+1];
    
    switch(devp->t) {
      case g2_PD:
	g2_poly_line_pd(devp->d.pd, N_pt, points);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_poly_line(devp->d.vd->dix[i], N_pt, points);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Triangle
 *
 */
void g2_triangle(int dev,
		 double x1, double y1,
		 double x2, double y2,
		 double x3, double y3)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_triangle: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x3;
    devp->y=y3;
    
    switch(devp->t) {
      case g2_PD:
	g2_triangle_pd(devp->d.pd,
		       x1, y1,
		       x2, y2,
		       x3, y3);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_triangle(devp->d.vd->dix[i], x1, y1, x2, y2, x3, y3);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Filled triangle
 *
 */
void g2_filled_triangle(int dev,
			double x1, double y1,
			double x2, double y2,
			double x3, double y3)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_filled_triangle: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x3;
    devp->y=y3;
    
    switch(devp->t) {
      case g2_PD:
	g2_filled_triangle_pd(devp->d.pd,
			      x1, y1,
			      x2, y2,
			      x3, y3);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_filled_triangle(devp->d.vd->dix[i], x1, y1, x2, y2, x3, y3);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Rectangle
 *
 */
void g2_rectangle(int dev, double x1, double y1, double x2, double y2)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_rectangle: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x2;
    devp->y=y2;

    switch(devp->t) {
      case g2_PD:
	g2_rectangle_pd(devp->d.pd, x1, y1, x2, y2);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_rectangle(devp->d.vd->dix[i], x1, y1, x2, y2);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Filled rectangle
 *
 */
void g2_filled_rectangle(int dev, double x1, double y1, double x2, double y2)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_filled_rectangle: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x2;
    devp->y=y2;

    switch(devp->t) {
      case g2_PD:
	g2_filled_rectangle_pd(devp->d.pd, x1, y1, x2, y2);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_filled_rectangle(devp->d.vd->dix[i], x1, y1, x2, y2);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Polygon
 *
 */
void g2_polygon(int dev, int N_pt, double *points)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_polygon: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_polygon_pd(devp->d.pd, N_pt, points);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_polygon(devp->d.vd->dix[i], N_pt, points);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Filled polygon
 *
 */
void g2_filled_polygon(int dev, int N_pt, double *points)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_filled_polygon: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_filled_polygon_pd(devp->d.pd, N_pt, points);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_filled_polygon(devp->d.vd->dix[i], N_pt, points);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Ellipse
 *
 */
void g2_ellipse(int dev, double x, double y, double r1, double r2)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_ellipse: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_ellipse_pd(devp->d.pd, x, y, r1, r2);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_ellipse(devp->d.vd->dix[i], x, y, r1, r2);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }

	
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Filled ellipse
 *
 */
void g2_filled_ellipse(int dev, double x, double y, double r1, double r2)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_filled_ellipse: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_filled_ellipse_pd(devp->d.pd, x, y, r1, r2);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_filled_ellipse(devp->d.vd->dix[i], x, y, r1, r2);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }

	
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Circle
 *
 */
void g2_circle(int dev, double x, double y, double r)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_circle: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_circle_pd(devp->d.pd, x, y, r);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_circle(devp->d.vd->dix[i], x, y, r);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }

	
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Filled circle
 *
 */
void g2_filled_circle(int dev, double x, double y, double r)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_filled_circle: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_filled_circle_pd(devp->d.pd, x, y, r);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_filled_circle(devp->d.vd->dix[i], x, y, r);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }

    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Arc
 *
 */
void g2_arc(int dev,
	    double x, double y,
	    double r1, double r2,
	    double a1, double a2)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_arc: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_arc_pd(devp->d.pd, x, y, r1, r2, a1, a2);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_arc(devp->d.vd->dix[i], x, y, r1, r2, a1, a2);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
	
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Filled arc
 *
 */
void g2_filled_arc(int dev,
		   double x, double y,
		   double r1, double r2,
		   double a1, double a2)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_filled_arc: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_filled_arc_pd(devp->d.pd, x, y, r1, r2, a1, a2);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_filled_arc(devp->d.vd->dix[i], x, y, r1, r2, a1, a2);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
	
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Draw string
 *
 */
void g2_string(int dev, double x, double y, char *text)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_string: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_string_pd(devp->d.pd, x, y, text);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_string(devp->d.vd->dix[i], x, y, text);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
	
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}

/*
 *
 * Draw a pen image
 *
 */
void g2_image(int dev, double x, double y, int x_size, int y_size, int *pens)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_image: No such device: %d\n", dev);
	return;
    }
    
    devp->x=x;
    devp->y=y;
    
    switch(devp->t) {
      case g2_PD:
	g2_image_pd(devp->d.pd, x, y, x_size, y_size, pens);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_image(devp->d.vd->dix[i], x, y, x_size, y_size, pens);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
	
    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}



/*
 *
 * Quasi Pixel fake
 *
 */
void g2_plot_QP(int dev, double x, double y)
{
    g2_device *devp;
    double d;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_plot_QP: No such device: %d\n", dev);
	return;
    }
    
    x=dtoi(x);
    y=dtoi(y);
    d=devp->QPd;
    switch(devp->QPshape) {
      case QPrect:
	g2_filled_rectangle(dev, x*d-d/2, y*d-d/2, x*d+d/2, y*d+d/2);
	break;
      case QPcirc:
	g2_filled_circle(dev, x*d, y*d, d/2.0);
	break;
      default:
	fprintf(stderr, "g2: QP: unknown shape\n");
	break;
    }
    if(devp->auto_flush)
        g2_flush(dev);

    __g2_last_device=dev;
}






