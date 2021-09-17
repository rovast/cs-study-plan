#include <stdio.h>

int main()
{
    printf("Playing Computer\n");

    /* Section 1 */
    // int i = 1;
    // int sum = 0;

    // while (i < 5)
    // {
    //     sum += i;
    //     i++;
    // }

    // /* sum=10 */
    // printf("sum=%d\n", sum); //1+0=1, 2+1=3, 3+3=6, 4+6=10

    /* section 2 */
    // double q = 1;
    // int i;

    // for (i = 1; i <= 5; i++)
    // {
    //     // i=1,q= 1 +  1*1/2 = 1.5
    //     // i=2,q= 1.5 + 2*2/2 = 3.5
    //     // i=3,q= 3.5 + 3*3/2 = 8
    //     // i=4,q= 8 + 4*4/2 = 16
    //     // i=5,q= 16 + 5*5/2 = 28.5
    //     q += i * i / 2.0;

    //     printf("i=%d, q=%4.1lf\n", i, q);
    // }

    // // 28.5
    // printf("q=%f\n", q);

    /* section 3 */
    // double q = 1;

    // do
    // {
    //     q = q * 2;
    // } while (q < 0);

    // printf("q=%f\n", q); // 2.0

    /* section 4 */
    int i;
    int j;

    for (i = 0; i < 11; i++)
    {
        if (i < 5)
        {
            for (j = 0; j <= i; j++)
                printf("+");
        }
        else
        {
            for (j = 0; j <= (10 - i); j++)
                printf("+");
        }

        printf("\n");
    }

    printf("---\n");

    return 0;
}
