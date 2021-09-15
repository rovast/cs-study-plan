#include <stdio.h>
#include <stdlib.h>

int main()
{
    int f = 3, tmp = 0; // Number we compute the factorial of
    int fac = 1;

    printf("Number to compute the factorial of: ");
    if (!scanf("%d", &f) || f < 0)
    {
        printf("Invalid input.\n");
        exit(1);
    }

    tmp = f;

    while (tmp > 0)
    {
        fac = fac * tmp;
        tmp--;
    }

    printf("%d! = %d\n", f, fac);

    return 0;
}
