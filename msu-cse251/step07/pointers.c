#include <stdio.h>

int main()
{
    int a = 0;
    int b = 5;
    int c = 0x2251;
    int *pA = &a;
    int *pB = &b;
    int *p;

    // printf("%d, %x\n", a, a);
    // printf("%d, %x\n", b, b);
    // printf("%d, %x\n", c, c);

    // printf("%p\n", (void *)&a);

    a = 47;
    printf("a=%d, pA=%p, *pA=%d\n", a, (void *)pA, *pA);
    *pA = 99;
    printf("a=%d, pA=%p, *pA=%d\n", a, (void *)pA, *pA);
    // a=47, pA=0x7ffe9f937cbc, *pA=47
    // a=99, pA=0x7ffe9f937cbc, *pA=99

    printf("Next experiment:\n");
    p = pA;
    *p = 22;
    p = pB;
    *p = 18;
    p = &b;
    *p = 108;
    p = pA;
    *p = 2;
    printf("a=%d, pA=%p, *pA=%d\n", a, (void *)pA, *pA);
    printf("b=%d, pB=%p, *pB=%d\n", b, (void *)pB, *pB);
    printf("p=%p, *p=%d\n", (void *)p, *p);
}
