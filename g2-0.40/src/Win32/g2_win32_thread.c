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

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "g2_win32_P.h"

#include "resource.h"



int WINAPI About(HWND hDlg,UINT message, WPARAM wParam,LPARAM lParam)
{
	switch (message){
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (wParam == IDOK)
			EndDialog(hDlg,wParam);
		break;
	}

	return FALSE;
}



LRESULT CALLBACK g2_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT Rect;
	struct 	g2_win32_STRUCT *pdp;

	pdp = (struct g2_win32_STRUCT *)GetWindowLong(hWnd, GWL_USERDATA);
	switch (message) { 

		case WM_PAINT:
			if (pdp == NULL) break;
			if (pdp->hBitmap == NULL) break;

//			printf("Received WM_PAINT\n");

			hDC = BeginPaint (hWnd, &ps);
			GetClientRect(hWnd,&Rect);
			BitBlt( hDC, Rect.left, Rect.top, Rect.right - Rect.left, 
			Rect.bottom - Rect.top, pdp->hMemDC, 0, 0, SRCCOPY );
			EndPaint (hWnd, &ps);


			return 0;
		case WM_DESTROY:

//			printf("Received WM_DESTROY\n");
			g2_win32_Cleanup(0,pdp);
			ExitThread(0);
		
		case WM_COMMAND:
			switch(LOWORD(wParam)){
			
			case ID_FILE_COPY:
				if (OpenClipboard(hWnd))
                   {
                    HBITMAP     hBitmap;
                   
                    EmptyClipboard();

                    if (pdp->hBitmap)
                        {
                        if (hBitmap = CopyImage(pdp->hBitmap,IMAGE_BITMAP,
												0,0,LR_COPYRETURNORG));
                            SetClipboardData(CF_BITMAP, hBitmap);
                        }
					CloseClipboard();
                    }
            return 0L;

			case ID_FILE_ABOUT:
				if(DialogBox(g2res_DLL,"ABOUTBOX",hWnd,(DLGPROC)About) == -1)
					errhandler("Failed to create Dialogbox",NULL);
				return 0L;

			case ID_FILE_CLOS:
				g2_win32_Delete(0,pdp);
				return 0L;

			default:
				return (DefWindowProc(hWnd, message, wParam, lParam));
			}

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
}

long g2_StartThread(struct g2_win32_STRUCT *pdp)
{
RECT	Rect;
HWND hWnd;
MSG msg;
HDC hDC;
int py,px;
HMENU hmenu;

hmenu = NULL;
if (g2res_DLL != NULL)
	{
	hmenu = LoadMenu(g2res_DLL,"G2WIN32");
	if (hmenu == NULL) errhandler("Load menu failed",NULL);
	}

// enlarge window for border and menu
py = pdp->nHeight + GetSystemMetrics(SM_CYMENU) +
				  2 * GetSystemMetrics(SM_CYBORDER)+
				  GetSystemMetrics(SM_CYSMCAPTION)+3;
px = pdp->nWidth + 2 * GetSystemMetrics(SM_CXBORDER)+3;

/* Save the instance handle in static variable, which will be used in  */
/* many subsequence calls from this application to Windows.            */

  /* Create a main window for this application instance.  */
  pdp->hinst = GetModuleHandle(NULL);

  hWnd = CreateWindow(
	 "g2Window",           // See RegisterClass() call.
	 pdp->title,		 // Text for window title bar.
	 WS_POPUPWINDOW | WS_CAPTION |WS_OVERLAPPED | WS_MINIMIZEBOX,
	 pdp->x, pdp->y,
	 px, py,
	 NULL,                  // Overlapped windows have no parent.
	 hmenu,                  // Use the window class menu.
	 0,                     // This instance owns this window.
	 NULL                   // Pointer not needed.
  );
 
  // If window could not be created, return "failure" 
 
  if (!hWnd)
	 {
	 errhandler("CreateWindow",NULL);
	 return (FALSE);   // return failure :((
	 }

#define WIDTH(x)	(x.right-x.left+1)	// Macro to get rect width
#define HEIGHT(x)	(x.bottom-x.top+1)	// Macro to get rect height

// How big is the window?
GetClientRect( hWnd, &Rect );

// Need a DC
hDC = GetDC( hWnd );
SetBkColor(hDC,RGB(255,255,255));
// Create a bitmap big enough to hold the window's image
pdp->hBitmap = CreateCompatibleBitmap( hDC, WIDTH(Rect), HEIGHT(Rect) );
// printf("memdc size: %d %d\n",WIDTH(Rect),HEIGHT(Rect));
// Create MemDC
pdp->hMemDC = CreateCompatibleDC(hDC);
SelectObject( pdp->hMemDC, pdp->hBitmap );
// clean up
ReleaseDC( hWnd, hDC );
#undef WIDTH
#undef HEIGHT



SetWindowLong(hWnd, GWL_USERDATA, (long)pdp); 
 
 pdp->hwndThreadWindow = hWnd;
 // Make the window visible; update its client area; and return "success" 
 ShowWindow(hWnd, SW_SHOWDEFAULT); // Show the window
 UpdateWindow(hWnd);     // Sends WM_PAINT message
 //printf("pdp->messageloop ->= 1;\n");
 pdp->messageloop = 1;
 //printf("pdp->messageloop = 1;\n");
 
 while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
		DispatchMessage(&msg);
    }

 
 return (TRUE);        // Returns success  :)
}



