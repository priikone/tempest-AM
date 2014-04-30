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
#ifndef _G2_CONTROL_PD_H
#define _G2_CONTROL_PD_H

#include "g2_physical_device.h"

void g2_flush_pd(g2_physical_device *pd);
void g2_save_pd(g2_physical_device *pd);
void g2_clear_pd(g2_physical_device *pd);
void g2_pen_pd(g2_physical_device *pd, int color);
void g2_set_background_pd(g2_physical_device *pd, int color);
int  g2_ink_pd(g2_physical_device *pd, double red, double green, double blue);
void g2_clear_palette_pd(g2_physical_device *pd);
void g2_allocate_basic_colors_pd(g2_physical_device *pd);
void g2_set_font_size_pd(g2_physical_device *pd, double size);
void g2_set_line_width_pd(g2_physical_device *pd, double w);
void g2_set_dash_pd(g2_physical_device *pd, int N, double *dashes);

#endif /* _G2_CONTROL_PD_H */
