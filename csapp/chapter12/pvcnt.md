```shell
➜  chapter12 git:(main) ✗ gcc -pthread pvcnt.c csapp.c 

➜  chapter12 git:(main) ✗ ./a.out 
Usage ./a.out <niters>

➜  chapter12 git:(main) ✗ ./a.out 1000000
OK cnt=2000000

➜  chapter12 git:(main) ✗ ./a.out 1000000
OK cnt=2000000
```

使用互斥信号来避免竞争。

```c
int sem_init(sem_t *sem, int pshared, unsigned int value);
```

 If pshared has the value 0, then the semaphore is shared between
the threads of a process, and should be located at some address
that is visible to all threads (e.g., a global variable, or a
variable allocated dynamically on the heap).

其中第二个参数为0，表示在线程间共享信号量(semaphore)。
