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

#include "g2.h"
#include "g2_device.h"
#include "g2_control_pd.h"


/*
 *
 * Flush output
 *
 */
void g2_flush(int dev)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_flush: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_flush_pd(devp->d.pd);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_flush(devp->d.vd->dix[i]);
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
 * Save output
 *
 */
void g2_save(int dev)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_save: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_save_pd(devp->d.pd);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_save(devp->d.vd->dix[i]);
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
 * Clear device
 *
 */
void g2_clear(int dev)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_clear: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_clear_pd(devp->d.pd);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_clear(devp->d.vd->dix[i]);
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
 * Set pen
 *
 */
void g2_pen(int dev, int color)
{
    g2_device *devp;
    int i;

    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_pen: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_pen_pd(devp->d.pd, color);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_pen(devp->d.vd->dix[i], color);
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
 * Set background color
 *
 */
void g2_set_background(int dev, int color)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_set_background: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_set_background_pd(devp->d.pd, color);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_set_background(devp->d.vd->dix[i], color);
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
 * Set ink
 *
 */
int g2_ink(int pd_dev, double red, double green, double blue)
{
    g2_device *devp;
    int rv=-1;

    if((devp=g2_get_device_pointer(pd_dev))==NULL) {
	fprintf(stderr, "g2_ink: No such device: %d\n", pd_dev);
	return -1;
    }

    if(red   < 0.0) red=0.0;
    if(green < 0.0) green=0.0;
    if(blue  < 0.0) blue=0.0;
    if(red   > 1.0) red=1.0;
    if(green > 1.0) green=1.0;
    if(blue  > 1.0) blue=1.0;
    
    switch(devp->t) {
      case g2_PD:
	rv=g2_ink_pd(devp->d.pd, red, green, blue);
	break;
      case g2_VD:
	fprintf(stderr, "g2_ink: g2_ink is enabled only for phys. devices\n");
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    __g2_last_device=pd_dev;
    return rv;
}



/*
 *
 * Reset palette
 *
 */
void g2_reset_palette(int dev)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_reset_palette: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_clear_palette(dev);
	g2_allocate_basic_colors(dev);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_reset_palette(devp->d.vd->dix[i]);
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
 * Clear palette
 *
 */
void g2_clear_palette(int dev)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_clear_palette: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_clear_palette_pd(devp->d.pd);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_clear_palette(devp->d.vd->dix[i]);
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
 * Allocate basic colors
 *
 */
void g2_allocate_basic_colors(int dev)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_allocate_basic_colors: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_allocate_basic_colors_pd(devp->d.pd);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_allocate_basic_colors(devp->d.vd->dix[i]);
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
 * Set font size
 *
 */
void g2_set_font_size(int dev, double size)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_set_font_size: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_set_font_size_pd(devp->d.pd, size);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_set_font_size(devp->d.vd->dix[i], size);
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
 * Set line width
 *
 */
void g2_set_line_width(int dev, double w)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_set_line_width: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_set_line_width_pd(devp->d.pd, w);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_set_line_width(devp->d.vd->dix[i], w);
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
 * Set dash
 *
 */
void g2_set_dash(int dev, int N, double *dashes)
{
    g2_device *devp;
    int i;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_set_dash: No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	g2_set_dash_pd(devp->d.pd, N, dashes);
	break;
	
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_set_dash(devp->d.vd->dix[i], N, dashes);
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
 * Set QP size and shape
 *
 */
void g2_set_QP(int dev, double d, enum QPshape shape)
{
    g2_device *devp;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_set_QP: No such device: %d\n", dev);
	return;
    }
    
    devp->QPd=d;
    devp->QPshape=shape;
    
    __g2_last_device=dev;
}

