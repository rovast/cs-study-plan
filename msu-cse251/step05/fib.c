#include <stdio.h>

int main()
{
    int fn1 = 1; /* F(n-1) during the loop */
    int fn2 = 0; /* F(n-2) during the loop */
    int f;       // computed Fibonacci number
    int i;       // loop counter

    printf("F(0) = 0\n");
    printf("F(1) = 1\n");

    for (i = 0; i < 10; i++)
    {
        f = fn1 + fn2;
        printf("F(%d) = %d\n", i + 2, f);

        fn2 = fn1;
        fn1 = f;
    }

    return 0;
}
