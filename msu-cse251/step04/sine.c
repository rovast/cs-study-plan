#include <stdio.h>
#include <math.h>

int main()
{
    double angle;
    int numSteps = 40;
    double maxAngle = M_PI * 2;
    int i;
    double sinVal;
    int numSpaces;

    for (i = 0; i <= numSteps; i++)
    {
        angle = (double)i / (double)numSteps * maxAngle;
        sinVal = sin(angle);
        printf("%3d: %5.2f %6.3f", i, angle, sinVal);
        numSpaces = (int)(30 * (1 + sinVal));
        while (numSpaces > 0)
        {
            printf(" ");
            numSpaces--;
        }
        printf("*\n");
    }
}
