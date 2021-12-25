使用预线程的并发服务器（预热线程池，避免切换开销）

```shell script
➜  chapter12 git:(main) ✗ gcc -Og -pthread echoservert_pre.c echo_cnt.c csapp.c sbuf.c && ./a.out 21080
--- main thread accept new connection, and connfd=4
--- sbuf remove new connfd=4
Server received 14 (14 total) bytes on fd 4
--- main thread accept new connection, and connfd=5
--- sbuf remove new connfd=5
Server received 15 (29 total) bytes on fd 5
```

有趣的知识点

1. 新的客户端链接 fd 一定是从 4 开始的。因为 0,1,2 被 stdin, stdout, stderr 占用了。3号被 listenfd 占用了
2. 由于使用的是信号量做的队列，所以阻塞和激活是自动的
