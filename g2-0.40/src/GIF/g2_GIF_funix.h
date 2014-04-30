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
#ifndef _g2_GIF_TOKEN_FUN_H
#define _g2_GIF_TOKEN_FUN_H
		
	
#include "g2_virtual_device.h"
#include "g2_GIF_P.h"

const g2_funix_fun g2_GIF_funix[] = 
		{{g2_Delete,g2_GIF_Delete},
		{g2_Ink, g2_GIF_Ink},
		{g2_Pen,g2_GIF_Pen},
		{g2_SetBackground,g2_GIF_SetBackground},
		{g2_ClearPalette,g2_GIF_ClearPalette},	 
		{g2_SetLineWidth,g2_GIF_SetLineWidth},
		 /*	{g2_SetDash,g2_GIF_SetDash},	*/
	 	{g2_SetFontSize,g2_GIF_SetFontSize},
		{g2_Clear,g2_GIF_Clear},
		{g2_Flush,g2_GIF_Flush},
		{g2_Plot,g2_GIF_Plot},
		{g2_Line,g2_GIF_Line},
		 /*	{g2_PolyLine,g2_GIF_PolyLine}, */
		{g2_Rectangle,g2_GIF_Rectangle},
		{g2_FilledRectangle,g2_GIF_FilledRectangle},
		 /*	{g2_Polygon,g2_GIF_Polygon}, */
		{g2_FilledPolygon,g2_GIF_FilledPolygon},
		 /*	{g2_Circle,g2_GIF_Circle}, */
		 /*	{g2_FilledCircle,g2_GIF_FilledCircle}, */
		 /*	{g2_Ellipse,g2_GIF_Ellipse}, */
		 /*	{g2_FilledEllipse,g2_GIF_FilledEllipse}, */
		 /*     {g2_Arc,g2_GIF_Arc}, */
		{g2_FilledArc,g2_GIF_FilledArc},
		{g2_String,g2_GIF_DrawString},
		{g2_FUNIX_NULL, NULL}};


#endif /* _g2_GIF_TOKEN_FUN_H */
