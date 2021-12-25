```shell
➜  chapter12 git:(main) ✗ gcc -pthread  badcnt.c csapp.c

➜  chapter12 git:(main) ✗ ./a.out 
Usage ./a.out <niters>

➜  chapter12 git:(main) ✗ ./a.out 1000000
BOOM! cnt=1224283

➜  chapter12 git:(main) ✗ ./a.out 1000000
OK cnt=2000000

➜  chapter12 git:(main) ✗ ./a.out 1000000
BOOM! cnt=1948725
```
