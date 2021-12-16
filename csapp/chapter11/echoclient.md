```shell script
➜  chapter11 git:(main) ✗                                    │➜  chapter11 git:(main) ✗ gcc echoserveri.c csapp.c echo.c -o server
➜  chapter11 git:(main) ✗ gcc echoclient.c csapp.c -o client │➜  chapter11 git:(main) ✗ ./server 1234
➜  chapter11 git:(main) ✗ ./client 127.0.0.1 1234            │Connected to (localhost, 37586)
hello                                                        │server received 6 bytes
hello                                                        │server received 6 bytes
world                                                        │
world                                                        │
                                                             │
                                                             │
                                                             │
                                                             │
```
