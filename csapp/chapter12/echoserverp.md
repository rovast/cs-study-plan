## 基于进程的并发服务器


Server

```
➜  chapter12 git:(main) ✗ gcc echoserverp.c csapp.c echo.c -g && ./a.out 1234

server received 4 bytes
server received 4 bytes
server received 4 bytes
```

Client

```
 telnet 127.0.0.1 1234
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
12
12
```

使用 Fork 的方式派生出子进程来处理客户端请求。
同时，由于服务器可能长期运行，所以捕获 SIGCHLD 信号进行处理，回收僵尸进程。

需要注意的是，SIGCHLD 信号是阻塞的，而 Linux 信号是不排队的，所以我们需要在 SIGCHLD 处理
程序中准备好回收多个僵尸子进程的资源。


# 查看子进程

```shell
# server
gcc echoserverp.c csapp.c echo.c -g -o echoserverp
echoserverp 21080

# client
telnet www.2huo.xyz:21080
telnet www.2huo.xyz:21080
telnet www.2huo.xyz:21080
```


![image](https://user-images.githubusercontent.com/9459488/147008186-70502fad-d6fe-49f7-a5f1-a56dd8c6b099.png)
