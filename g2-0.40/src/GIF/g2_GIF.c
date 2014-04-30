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
#include "g2_util.h"
#include "g2_config.h"

#include "g2_GIF_P.h"
#include "g2_GIF.h"

#define PDP ((struct g2_GIF_STRUCT *)pdp)

#include "g2_GIF_funix.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif /* PI */


int g2_GIF_Alloc_Basic(int pid, void *pdp)
	{
	int icol;
	for (icol=0;icol<32;icol++)
		gdImageColorAllocate(PDP->im,g2_Basic_Colors[icol][0]/256,g2_Basic_Colors[icol][1]/256,g2_Basic_Colors[icol][2]/256);
	PDP->NoOfInks = 32;
	return 0;
	}

int g2_GIF_Delete(int pid, void *pdp)
	{
	gdImageGif(PDP->im,PDP->f);
	fclose(PDP->f);
	gdImageDestroy(PDP->im);
	free(PDP);
	return 0;
    }

int g2_GIF_Clear(int pid, void *pdp)
	{
    gdImageFilledRectangle(PDP->im, 0, 0, PDP->width, PDP->height, PDP->BackCol);
	return 0;
    }

int g2_GIF_Save(int pid, void *pdp)
	{
	gdImageGif(PDP->im,PDP->f);
	fflush(PDP->f);
	rewind(PDP->f);
	return 0;
      }

int g2_GIF_Flush(int pid, void *pdp)
	{
	return 0;
    }

int g2_GIF_Pen(int pid, void *pdp, int color)
	{
	PDP->CurCol = color;
	return 0;
    }

int g2_GIF_Ink(int pid, void *pdp, double red, double green, double blue)
	{
	if(PDP->NoOfInks == 256)
		return -1;
	else
		PDP->NoOfInks++;
	return gdImageColorAllocate(PDP->im,(int)(255*red),(int)(255*green),(int)(255*blue));
	}

int g2_GIF_ClearPalette(int pid, void *pdp)
	{
	int i;
	for (i=0;i<PDP->NoOfInks;i++)
		gdImageColorDeallocate(PDP->im,i);
	PDP->NoOfInks = 0;
	return 0;
    }

int g2_GIF_ResetPalette(int pid, void *pdp)
	{
	g2_GIF_ClearPalette(pid,pdp);
	g2_GIF_Alloc_Basic(pid,pdp);
    return 0;
	}

int g2_GIF_SetBackground(int pid, void *pdp, int color)
	{
	PDP->BackCol = color;
	return 0;
    }

int g2_GIF_SetLineWidth(int pid, void *pdp, int w)
	{
	PDP->LineWidth = w;
	return 0;
        }
/*	  {
	  if (PDP->brush != NULL)
	    {
            gdImageDestroy(PDP->brush);
	    }
	  PDP->brush = gdImageCreate(w,w);
	  gdImageColorTransparent(PDP->brush,0);
	  gdImageColorAllocate(PDP->brush,0,0,0);
	  gdImageColorAllocate(PDP->brush,
			 gdImageRed(PDP->im,PDP->CurCol),
			 gdImageGreen(PDP->im,PDP->CurCol),
			 gdImageBlue(PDP->im,PDP->CurCol));
	  gdImageArc(PDP->brush, w/2, w/2, w/2,w/2, 0, 360, 1);
	  gdImageFill(PDP->brush,w/2,w/2,1);
          gdImageSetBrush(PDP->im, PDP->brush);
	  PDP->OldCol = PDP->CurCol;
	  PDP->CurCol = gdBrushed;
	  }
	else
	  {
	  PDP->CurCol = PDP->OldCol;
	  }
	return 0;
    }
*/
     
int g2_GIF_SetDash(int pid, void *pdp, int n, char *data)
	{
	return 0;
    }

int g2_GIF_SetDashX(int pid, void *pdp, int N, double *dashes)
	{
	return 0;
    }

int g2_GIF_SetFontSize(int pid, void *pdp, int size)
	{
	if (size <=10)
		PDP->FontSize = gdFontTiny;
	else if (size <=12) 
		PDP->FontSize = gdFontSmall;
	else if (size <=13) 
		PDP->FontSize = gdFontMediumBold;
	else if (size <=15) 
		PDP->FontSize = gdFontLarge;
	else  
		PDP->FontSize = gdFontGiant;
	return 0;
    }

int g2_GIF_Plot(int pid, void *pdp, int x, int y)
	{
	gdImageSetPixel(PDP->im, x, y, PDP->CurCol);
	return 0;
    }

int g2_GIF_Line(int pid, void *pdp, int x1, int y1, int x2, int y2)
	{
	if (PDP->LineWidth <= 1)
	  gdImageLine(PDP->im, x1, y1, x2, y2, PDP->CurCol);
	else
	  {
	  float dx,dy,l;
	  gdPoint points[4];
	  dx=-(y2-y1);
	  dy=x2-x1;
	  l = PDP->LineWidth/sqrt(dy*dy+dx*dx)/2.;
	  dx = dx*l;
	  dy = dy*l;
	  points[0].x = x1+dx;
          points[0].y = y1+dy;
          points[1].x = x1-dx;
          points[1].y = y1-dy;
          points[2].x = x2-dx;
          points[2].y = y2-dy;
          points[3].x = x2+dx;
          points[3].y = y2+dy;
	  gdImageFilledPolygon(PDP->im,points,4,PDP->CurCol);
	  }
	return 0;
    }

int g2_GIF_PolyLine(int pid, void *pdp, int N, int *points)
	{
	return 0;
    }

int g2_GIF_Triangle(int pid, void *pdp, int x1, int y1,
		 int x2, int y2,
		 int x3, int y3)
	{
	return 0;
    }

int g2_GIF_FilledTriangle(int pid, void *pdp, int x1, int y1,
		       int x2, int y2,
		       int x3, int y3)
	{
	return 0;
    }

int g2_GIF_Rectangle(int pid, void *pdp, int x, int y, int x2, int y2)
	{
    gdImageRectangle(PDP->im, x, y, x2, y2, PDP->CurCol);
	return 0;
    }

int g2_GIF_FilledRectangle(int pid, void *pdp, int x, int y, int x2, int y2)
	{
    gdImageFilledRectangle(PDP->im, x, y, x2, y2, PDP->CurCol);
	return 0;
	}

int g2_GIF_Polygon(int pid, void *pdp, int N, int *points)
	{
	return 0;
    }

int g2_GIF_FilledPolygon(int pid, void *pdp, int N, int *points)
	{
	gdPoint *GIFPolygon;
	int i;
	GIFPolygon = (gdPoint *)malloc(N*sizeof(gdPoint));
	for (i=0;i<N;i++)
		{
		GIFPolygon[i].x = points[2*i];
		GIFPolygon[i].y = points[2*i+1];
		}
	gdImageFilledPolygon(PDP->im,GIFPolygon,N,PDP->CurCol);
	free(GIFPolygon);
	return 0;
    }

int g2_GIF_Circle(int pid, void *pdp, int x, int y, int r)
	{
	gdImageArc(PDP->im, (int)x, (int)y, (int)r, (int)r, 0, 360, PDP->CurCol);
	return 0;
    }

int g2_GIF_FilledCircle(int pid, void *pdp, int x, int y, int r)
	{
	return 0;
    }

int g2_GIF_Ellipse(int pid, void *pdp, int x, int y, int r1, int r2)
	{
	return 0;
    }

int g2_GIF_FilledEllipse(int pid, void *pdp, int x, int y, int r1, int r2)
	{
	return 0;
    }

int g2_GIF_Arc(int pid, void *pdp, int x, int y, int r1, int r2, double a1, double a2)
	{
	gdImageArc(PDP->im,x,y,2*r1,2*r2,dtoi(a1),dtoi(a2),PDP->CurCol);
	return 0;
    }

int g2_GIF_FilledArc(int pid, void *pdp, int x, int y,
		  int r1, int r2,
		  double a1, double a2)
	{
	double  a, da;			  /* emulate filled arc */
	int pts[6];
	int N, i;
	pts[0] = dtoi(x);
	pts[1] = dtoi(y);
	N=(int)fabs(a2-a1)+8;
	while (a2 < a1) a2+=360;
	a=a1*2.*PI/360.;
	da=(a2-a1)*2.*PI/360./(N-1);
	pts[2] = dtoi(x+r1*cos(a));
	pts[3] = dtoi(y+r2*sin(a));
	for(i=1;i<N;i++) {
		pts[4] = dtoi(x+r1*cos(a+i*da));
		pts[5] = dtoi(y-r2*sin(a+i*da));
		if ((pts[4] != pts[2]) || (pts[5] != pts[3])) /* skip identical points */
			{
			g2_GIF_FilledPolygon(pid,pdp,3,pts);
			}
		pts[2] = pts[4];
		pts[3] = pts[5];
		}
	return 0;
    }

int g2_GIF_DrawString(int pid, void *pdp, int x, int y, char *text)
	{
	
	gdImageString(PDP->im,PDP->FontSize,x,y+2-PDP->FontSize->h,(unsigned char *)text,PDP->CurCol);
	return 0;
	}

int  g2_open_GIF(const char *filename, int width, int height)
	{
	int pid=-1;
	g2_GIF_STRUCT *pdp;

	pdp = (g2_GIF_STRUCT *)malloc(sizeof(g2_GIF_STRUCT));

	pdp->width = width;
	pdp->height = height;
	pdp->im = gdImageCreate(width,height);
	pdp->f = fopen(filename,"wb");
	pdp->NoOfInks = 0;
	pdp->BackCol = 0;
	g2_GIF_Clear(pid,pdp);

    pid = g2_register_physical_device(pid, pdp,
				      g2_IntCoor, g2_GIF_funix,
				      1.0, -1.0,
				      0.0, height-1);

	g2_set_font_size(pid, 12.0);
    g2_allocate_basic_colors(pid);
    g2_pen(pid, 1);
    	
	return pid;
	}
