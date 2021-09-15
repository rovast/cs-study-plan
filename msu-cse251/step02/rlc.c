#include <stdio.h>
#include <math.h>

int main()
{
    double w, c, l, f;

    printf("Input Capacitance (microfarads): ");
    scanf("%lf", &c);
    printf("Input Inductance (millihenrys): ");
    scanf("%lf", &l);

    w = 1 / sqrt(l / 1000 * c / 1000000); // w = 1 / sqrt(lc)
    f = w / (2 * M_PI);                   // f = w / 2pi

    printf("Resonant Frequency is %.3lf\n", f);

    return 0;
}
