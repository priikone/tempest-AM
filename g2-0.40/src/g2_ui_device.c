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

#include "g2.h"
#include "g2_funix.h"
#include "g2_device.h"


/*
 *
 * Close and delete device
 *
 */
void g2_close(int dev)
{
    g2_device *devp;

    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_close: Warning! No such device: %d\n", dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	devp->d.pd->ff[g2_Delete].fun(devp->d.pd->pid,
				      devp->d.pd->pdp);
	break;
      case g2_VD:
	while(devp->d.vd->N>0)			  /* close all devices */
	    g2_close(devp->d.vd->dix[devp->d.vd->N-1]);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    g2_destroy_device(dev);			  /* destroy device */
}


/*
 *
 * Set auto flush mode
 *
 */
void g2_set_auto_flush(int dev, int on_off)
{
    g2_device *devp;
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr,
		"g2_set_auto_flush: Warning! No such device: %d\n", dev);
	return;
    }
    
    devp->auto_flush=on_off;
    __g2_last_device=dev;
}


/*
 *
 * Set user coordinate system
 *
 */
void g2_set_coordinate_system(int dev,
			      double x_origin, double y_origin,
			      double x_mul,    double y_mul)
{
    g2_device *devp;
    int i;
    
    if(x_mul==0.0 || y_mul==0.0) {
	fprintf(stderr,
	     "g2_set_coordinate_system: Error! Multiplicator can not be 0.0");
	return;
    }
    
    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr,
		"g2_set_coordinate_system: Warning! No such device: %d\n",
		dev);
	return;
    }
    
    switch(devp->t) {
      case g2_PD:
	devp->d.pd->x_origin=x_origin;
	devp->d.pd->y_origin=y_origin;
	devp->d.pd->x_mul=x_mul;
	devp->d.pd->y_mul=y_mul;
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_set_coordinate_system(devp->d.vd->dix[i],
				     x_origin, y_origin,
				     x_mul, y_mul);
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
 * Get last accessed device (lsd)
 *
 */
int g2_ld(void)
{
    return __g2_last_device;
}



/*
 *
 * Set last accessed device (lsd)
 *
 */
void g2_set_ld(int dev)
{
    if(!g2_device_exist(dev)) {
	fprintf(stderr, "g2_set_lsd: Warning! No such device: %d\n", dev);
	return;
    }
    __g2_last_device=dev;
}
