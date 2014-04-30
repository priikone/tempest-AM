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
#ifndef _G2_X11_P_H
#define _G2_X11_P_H

#include <X11/Xlib.h>

typedef struct {
    Display     *display;
    Window      window;
    Window      root;
    Colormap    colormap;
    GC          gc;
    
    unsigned long  *inks;			  /* allocated colors*/
    int            NofInks;			  /* N of allocated colors */
    int            width;			  /* window dimensions */
    int            height;
} g2_X11_device;


int g2_X11_init_X11X(int pid, int width, int height,
		     int xposition, int yposition,
		     char *window_name, char *icon_name,
		     char *icon_data,
		     unsigned int icon_width, unsigned int icon_height);
int g2_X11_delete(int pid, void *pdp);
int g2_X11_clear(int pid, void *pdp);
int g2_X11_flush(int pid, void *pdp);
int g2_X11_ink(int pid, void *pdp,
	       double red, double green, double blue);
int g2_X11_clear_palette(int pid, void *pdp);
int g2_X11_reset_palette(int pid, void *pdp);
int g2_X11_set_background(int pid, void *pdp, int color);
int g2_X11_pen(int pid, void *pdp, int color);
int g2_X11_paper(int pid, void *pdp, int color);
int g2_X11_set_line_width(int pid, void *pdp, int w);
int g2_X11_set_dash(int pid, void *pdp, int n, int *data);
int g2_X11_set_font_size(int pid, void *pdp, int size);
int g2_X11_plot(int pid, void *pdp, int x, int y);
int g2_X11_line(int pid, void *pdp, int x1, int y1, int x2, int y2);
int g2_X11_poly_line(int pid, void *pdp, int N, int *p);
int g2_X11_polygon(int pid, void *pdp, int N, int *p);
int g2_X11_filled_polygon(int pid, void *pdp, int N, int *p);
int g2_X11_triangle(int pid, void *pdp,
		    int x1, int y1,
		    int x2, int y2,
		    int x3, int y3);
int g2_X11_filled_triangle(int pid, void *pdp, int x1, int y1,
			   int x2, int y2,
			   int x3, int y3);
int g2_X11_rectangle(int pid, void *pdp, int x1, int y1, int x2, int y2);
int g2_X11_filled_rectangle(int pid, void *pdp,
			    int x1, int y1, int x2, int y2);
int g2_X11_arc(int pid, void *pdp, int x, int y,
	       int r1, int r2, double a1, double a2);
int g2_X11_filled_arc(int pid, void *pdp, int x, int y,
		      int r1, int r2, double a1, double a2);
int g2_X11_ellipse(int pid, void *pdp, int x, int y, int r1, int r2);
int g2_X11_filled_ellipse(int pid, void *pdp, int x, int y, int r1, int r2);
int g2_X11_draw_string(int pid, void *pdp, int x, int y, char *text);
int g2_X11_image(int pid, int x, int y, int width, int height, int *pen_array);

#endif /* _G2_X11_P_H */





