#include <stdio.h>
#include <stdlib.h>

int main()
{
    double income, deduction, taxableIncome, tax; // 年收入、扣除费用、应纳税所得、实际纳税
    int status, children = 0, dependents = 1;     // 申报状态、孩子数量、家属总数

    printf("Enter your annual income: ");
    if (!scanf("%lf", &income) || income < 0)
    {
        printf("Invalid input.\n");
        exit(1);
    }

    printf("What is your filing status?\n \
1) single\n \
2) married filing jointly\n \
3) married filing separately\n \
Please enter a number: ");
    if (!scanf("%d", &status) || status < 1 || status > 3)
    {
        printf("Invalid input.\n");
        exit(1);
    }

    // 如果是合并申报，家庭成员需要加上小孩儿的数量
    if (status == 2)
    {
        printf("How many children do you have? ");
        if (!scanf("%d", &children) || children < 0)
        {
            printf("Invalid input.\n");
            exit(1);
        }
        dependents = 2 + children;
    }

    // 计算扣除费用
    deduction = (status == 2 ? 11400 : 5700) + 3650 * dependents;
    taxableIncome = income - deduction;

    // 根据不同的档位，进行税收的申报
    if (taxableIncome <= 16750)
    {
        tax = 0 + taxableIncome * 0.1;
    }
    else if (taxableIncome <= 68000)
    {
        tax = 1675 + (taxableIncome - 16750) * 0.15;
    }
    else if (taxableIncome <= 137300)
    {
        tax = 9362.50 + (taxableIncome - 68000) * 0.25;
    }
    else
    {
        tax = 26687.5 + (taxableIncome - 137300) * 0.28;
    }

    printf("%.2f\n", tax);

    return 0;
}
