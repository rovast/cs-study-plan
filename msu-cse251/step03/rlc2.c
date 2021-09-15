#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    double w, c, l, f;
    bool valid = true;

    printf("Input Capacitance (microfarads): ");
    scanf("%lf", &c);
    printf("Input Inductance (millihenrys): ");
    scanf("%lf", &l);

    // check l
    if (l < 0)
    {
        printf("You moron, you entered a negative inductance!\n");
        valid = false;
    }
    else if (l == 0)
    {
        printf("You are really dumb, you entered zero.\n");
        valid = false;
    }

    if (valid)
    {
        w = 1 / sqrt(l / 1000 * c / 1000000); // w = 1 / sqrt(lc)
        f = w / (2 * M_PI);                   // f = w / 2pi

        printf("Resonant Frequency is %.3lf\n", f);
    }

    return 0;
}
