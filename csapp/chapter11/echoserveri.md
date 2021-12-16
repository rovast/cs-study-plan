```shell script
➜  chapter11 git:(main) ✗ gcc echoserveri.c csapp.c echo.c           │➜  chapter11 git:(main) ✗ telnet 127.0.0.1 1234
➜  chapter11 git:(main) ✗ ./a.out 1234                               │Trying 127.0.0.1...
Connected to (localhost, 37316)                                      │Connected to 127.0.0.1.
server received 7 bytes                                              │Escape character is '^]'.
server received 7 bytes                                              │hello
                                                                     │hello
                                                                     │12345
                                                                     │12345
```

实现服务端，使用 telnet 进行连接测试。
