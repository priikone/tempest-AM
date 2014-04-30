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
#ifndef _G2_VIRTUAL_DEVICE_H
#define _G2_VIRTUAL_DEVICE_H

typedef struct _g2_virtual_device {
    int  N;		             /* number of attached devices */
    int  *dix;			     /* index of attached devices */
} g2_virtual_device;


g2_virtual_device *g2_create_virtual_device();
void g2_destroy_virtual_device(g2_virtual_device *vd);
int g2_is_attached(int vd, int dev);

#endif /* _G2_VIRTUAL_DEVICE_H */
