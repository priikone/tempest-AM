#include <g2.h>
#include <g2_PS.h>

int main()
{
    int d;
    d=g2_open_PS("simple.ps", g2_A4, g2_PS_port);
    g2_line(d, 10, 10, 90, 90);
    g2_close(d);
    return 0;
}

