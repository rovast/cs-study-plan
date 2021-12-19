## client error

当前 tiny server 只实现了 GET 方法请求，其他的需要给出不支持的提示

```shell script
# server output
➜  chapter11 git:(main) ✗ gcc tiny.c csapp.c && ./a.out 21080
Accepted connection from (localhost, 57784)
POST / HTTP/1.0

# client request
➜  cs-study-plan git:(main) ✗ telnet 127.0.0.1 21080
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
POST / HTTP/1.0
HTTP/1.0 501 Not implemented
Content-type: text/html
Content-length: 158

<html><title>Tiny Error</title><body bgcolor="ffffff">
501: Not implemented
<p>Tiny does not implement this method: POST
<hr><em>The Tiny Web server</em>
Connection closed by foreign host.
```
