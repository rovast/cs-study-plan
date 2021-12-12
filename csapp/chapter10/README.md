## execrise10.1.c

```shell script
gcc execrise10.1.c csapp.c && ./a.out
```

output
```
fd1=3
fd2=3
```

进程开始时，有三个描述符被占用了
- `stdin` 0
- `stdout` 1
- `stderr` 2

所以对于上述进程，描述符就分配到了 3，在 Close 函数之后，描述符被释放掉。
