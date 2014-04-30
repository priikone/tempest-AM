#include <g2.h>
#include <g2_GIF.h>

int main()
{
    int d;
    d=g2_open_GIF("simple.gif", 100, 100);
    g2_line(d, 10, 10, 90, 90);
    g2_close(d);
    return 0;
}

