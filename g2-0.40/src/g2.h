/*****************************************************************************
**  Copyright (C) 1998  Ljubomir Milanovic & Horst Wagner
**  This file is part of the g2 library
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
#ifndef _G2_H
#define _G2_H

#define G2_VERSION "0.40"

#define G2LD g2_ld()

enum QPshape {
    QPrect,
    QPcirc
};

/* compatibility with old versions */
#define g2_draw_string(dev, x, y, text) g2_string((dev), (x), (y), (text))



int  g2_open_vd(void);
void g2_attach(int vd_dev, int dev);
void g2_detach(int vd_dev, int dev);

void g2_close(int dev);
void g2_set_auto_flush(int dev, int on_off);
void g2_flush(int dev);
void g2_save(int dev);
void g2_set_coordinate_system(int dev, double x_origin, double y_origin,
			      double x_mul,    double y_mul);

int  g2_ld();
void g2_set_ld(int dev);

int  g2_ink(int pd_dev, double red, double green, double blue);
void g2_pen(int dev, int color);
void g2_set_dash(int dev, int N, double *dashes);
void g2_set_font_size(int dev, double size);
void g2_set_line_width(int dev, double w);
void g2_clear_palette(int dev);
void g2_reset_palette(int dev);
void g2_allocate_basic_colors(int dev);

void g2_clear(int dev);
void g2_set_background(int dev, int color);

void g2_move(int dev, double x, double y);
void g2_move_r(int dev, double dx, double dy);

void g2_plot(int dev, double x, double y);
void g2_plot_r(int dev, double dx, double dy);
void g2_line(int dev, double x1, double y1, double x2, double y2);
void g2_line_r(int dev, double dx, double dy);
void g2_line_to(int dev, double x, double y);
void g2_poly_line(int dev, int N_pt, double *points);
void g2_triangle(int dev, double x1, double y1,
		 double x2, double y2,
		 double x3, double y3);
void g2_filled_triangle(int dev, double x1, double y1,
			double x2, double y2,
			double x3, double y3);
void g2_rectangle(int dev, double x1, double y1, double x2, double y2);
void g2_filled_rectangle(int dev, double x1, double y1, double x2, double y2);
void g2_polygon(int dev, int N_pt, double *points);
void g2_filled_polygon(int dev, int N_pt, double *points);
void g2_circle(int dev, double x, double y, double r);
void g2_filled_circle(int dev, double x, double y, double r);
void g2_ellipse(int dev, double x, double y, double r1, double r2);
void g2_filled_ellipse(int dev, double x, double y, double r1, double r2);
void g2_arc(int dev,
	    double x, double y,
	    double r1, double r2,
	    double a1, double a2);
void g2_filled_arc(int dev, double x, double y,
		   double r1, double r2,
		   double a1, double a2);
void g2_string(int dev, double x, double y, char *text);
void g2_image(int dev, double x, double y, int x_size, int y_size, int *pens);

void g2_set_QP(int dev, double d, enum QPshape shape);
void g2_plot_QP(int dev, double x, double y);


/** Actualy private function, but... **/
int g2_device_exist(int dix);

#endif /* _G2_H */
