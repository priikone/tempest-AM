#include <stdio.h>
#include <g2.h>
#include <g2_X11.h>

int main()
{
	int d;
	int i;

	d=g2_open_X11(1024, 768);

	for (i = 0; i < 255; i++) {
		g2_pen(d, g2_ink(d, i/255., i/255., i/255.));
		g2_plot(d, 0 + i, 600);
		g2_plot(d, 0 + i, 601);
		g2_plot(d, 0 + i, 602);
	}
	getchar();
}

