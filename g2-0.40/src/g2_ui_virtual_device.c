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
#include "g2_device.h"
#include "g2_virtual_device.h"
#include "g2_util.h"


/*
 *
 */
int g2_open_vd(void)
{
    int dix;
    dix=g2_register_virtual_device();
    __g2_last_device=dix;
    return dix;
}


/*
 *
 */
void g2_attach(int vd_dev, int dev)
{
    g2_device *vd_devp, *devp;

    if((vd_devp=g2_get_device_pointer(vd_dev))==NULL) {
	fprintf(stderr, "g2_attach: No such device: %d\n", vd_dev);
	return;
    }

    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_attach: No such device: %d\n", dev);
	return;
    }

    if(vd_devp->t!=g2_VD) {
	fprintf(stderr, "g2_attach: Device %d is not virtual.\n", vd_dev);
	return;
    }

    if(devp->t==g2_VD)				  /* if virtual device */
	if(g2_is_attached(dev, vd_dev)) {	  /* check recurency */
	    fprintf(stderr,
		    "g2_attach: Device %d is already attached to %d.\n",
		    dev, vd_dev);
	    return;
	}

    vd_devp->d.vd->N++;
    vd_devp->d.vd->dix=g2_realloc(vd_devp->d.vd->dix,
				  vd_devp->d.vd->N*sizeof(int));

    vd_devp->d.vd->dix[vd_devp->d.vd->N-1]=dev;

    __g2_last_device=vd_dev;
}


/*
 *
 */
void g2_detach(int vd_dev, int dev)
{
    g2_device *vd_devp;
    int i;

    if((vd_devp=g2_get_device_pointer(vd_dev))==NULL) {
	fprintf(stderr, "g2_detach: No such device: %d\n", vd_dev);
	return;
    }

    if(vd_devp->t!=g2_VD) {
	fprintf(stderr, "g2_detach: Device %d is not virtual.\n", vd_dev);
	return;
    }

    for(i=0;i<vd_devp->d.vd->N;i++)
	if(vd_devp->d.vd->dix[i]==dev) {
	    if(vd_devp->d.vd->N>1)
		vd_devp->d.vd->dix[i]=vd_devp->d.vd->dix[vd_devp->d.vd->N-1];
	    vd_devp->d.vd->N--;
	    if(vd_devp->d.vd->N!=0)
		vd_devp->d.vd->dix=g2_realloc(vd_devp->d.vd->dix,
					      vd_devp->d.vd->N*sizeof(int));
	    return;
	}

    __g2_last_device=vd_dev;
}

