# Notes

## 库

There are two levels of libraries in C. 
- There are those that are already available, like the standard input/output library, 
- and those that have to be linked to your program. 

The math library is like that. 

Some simple things, 
- like M_PI are available always, 
- but the functions need to be made available. 

We do that by adding the -lm switch (add library libm, the math library) to the command to compile our programs.


## 分号

Note that there is not a semicolon after the `if` expression, only at the end of the statement.

所以我们看到， `#define` 后也没分号。


## `scanf` 安全性

通过检查值来确保输入安全

```c
#include <stdio.h>
#include <stdlib.h>

if (!scanf("%lf", &income) || income < 0)
{
    printf("Invalid input.\n");
    exit(1);
}
```


## 除法问题

下面的代码，如果不强制转成浮点。那么 `i/numSteps` 会丢失精度，在值较小的情况下，就一直为0。

见 [step04/sine.c](./step04/sine.c)

```c
// i 和 numSteps 是整形
angle = (double)i / (double)numSteps * maxAngle;
```
