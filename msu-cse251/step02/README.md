## step2

```bash
➜  step02 git:(main) ✗ gcc -o step2 step2.c -lm && ./step2 
The cylinder has a radius of 7.880000 and a height of 12.231000
The cylinder has a radius of  7.88 and a height of     12.2
MSU had an 11-2 season in 2010!
```

There are two levels of libraries in C. 
- There are those that are already available, like the standard input/output library, 
- and those that have to be linked to your program. 

The math library is like that. 

Some simple things, 
- like M_PI are available always, 
- but the functions need to be made available. 

We do that by adding the -lm switch (add library libm, the math library) to the command to compile our programs.


## rlc

```bash
➜  step02 git:(main) ✗ gcc -o rlc rlc.c -lm
➜  step02 git:(main) ✗ ./rlc               
Input Capacitance (microfarads): 30
Input Inductance (millihenrys): 30
Resonant Frequency is 167.764
```
