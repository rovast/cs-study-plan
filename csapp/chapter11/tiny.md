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

## parse_uri

解析 uri 参数到 filename 和 cgiargs。如果不存在则返回 404。


server编译和输出
```shell script
➜  chapter11 git:(main) ✗ gcc tiny.c csapp.c -g && ./a.out 21080

Accepted connection from (117.89.199.219, 21384)
GET /not HTTP/1.1
Host: www.2huo.xyz:21080
Accept-Encoding: deflate, gzip
Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7,zh-TW;q=0.6
Cookie: key=%24argon2i%24v%3D19%24m%3D4096%2Ct%3D3%2Cp%3D1%24Ou5VFbV6pHi0aweNtwh9tQ%24D7ylm7cfCTZYmggmym5AIwKztrbqUMRAEDt%2Fo%2B2ysk0
```


客户端
```shell script
➜  ~ curl 'http://www.2huo.xyz:21080/not' \
  -H 'Connection: keep-alive' \
  -H 'Upgrade-Insecure-Requests: 1' \
  -H 'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36' \
  -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' \
  -H 'Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7,zh-TW;q=0.6' \
  -H 'Cookie: key=%24argon2i%24v%3D19%24m%3D4096%2Ct%3D3%2Cp%3D1%24Ou5VFbV6pHi0aweNtwh9tQ%24D7ylm7cfCTZYmggmym5AIwKztrbqUMRAEDt%2Fo%2B2ysk0' \
  --compressed \
  --insecure
<html><title>Tiny Error</title><body bgcolor="ffffff">
404: Not found
<p>Tiny could't find the file.: ./not
<hr><em>The Tiny Web server</em>
```


## serve_static

静态页面处理

1. 判断 URI 是不是包含 cgi-bin，以此来区分是动态服务还是静态服务
2. 静态服务判断文件类型，用以设置 content-type
3. 使用 mmap 映射文件到虚拟内存，一次性输出到 clientfd

![image](https://user-images.githubusercontent.com/9459488/146711879-02dde80e-890d-47b9-aea9-7e7b28e396f7.png)


压测

```
➜  ~ hey -z 10s -c 20 -host "2huo.xyz" "http://www.2huo.xyz:21080/README.md"

Summary:
  Total:	11.6494 secs
  Slowest:	2.0216 secs
  Fastest:	0.0159 secs
  Average:	0.0253 secs
  Requests/sec:	692.1409

  Total data:	3104255 bytes
  Size/request:	385 bytes

Response time histogram:
  0.016 [1]	|
  0.217 [8012]	|■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
  0.417 [15]	|
  0.618 [0]	|
  0.818 [0]	|
  1.019 [5]	|
  1.219 [29]	|
  1.420 [0]	|
  1.620 [0]	|
  1.821 [0]	|
  2.022 [1]	|


Latency distribution:
  10% in 0.0182 secs
  25% in 0.0191 secs
  50% in 0.0201 secs
  75% in 0.0212 secs
  90% in 0.0223 secs
  95% in 0.0232 secs
  99% in 0.0489 secs

Details (average, fastest, slowest):
  DNS+dialup:	0.0146 secs, 0.0159 secs, 2.0216 secs
  DNS-lookup:	0.0005 secs, 0.0000 secs, 0.0031 secs
  req write:	0.0000 secs, 0.0000 secs, 0.0012 secs
  resp wait:	0.0102 secs, 0.0076 secs, 0.3077 secs
  resp read:	0.0005 secs, 0.0000 secs, 0.2291 secs

Status code distribution:
  [200]	8063 responses
```


## serve_dynamic

动态页面处理

1. 设置环境变量
2. 使用 Execve 加载指定的执行文件

adder 执行文件准备
```shell script
gcc adder.c csapp.c -o cgi-bin/adder
```

server
```shell script
gcc tiny.c csapp.c -g && ./a.out 21080
```


![image](https://user-images.githubusercontent.com/9459488/146715050-c80895dd-14bd-4da9-a27b-682ac5eb4d00.png)


压测，这个结果可以后面留着和并发编程时对比

```shell script
➜  ~ hey -z 10s -c 20 -host "2huo.xyz" "http://www.2huo.xyz:21080/cgi-bin/adder?1&2"

Summary:
  Total:	10.0228 secs
  Slowest:	1.0314 secs
  Fastest:	0.0165 secs
  Average:	0.0266 secs
  Requests/sec:	751.9850

  Total data:	791385 bytes
  Size/request:	105 bytes

Response time histogram:
  0.016 [1]	|
  0.118 [7518]	|■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
  0.219 [0]	|
  0.321 [4]	|
  0.422 [0]	|
  0.524 [0]	|
  0.625 [0]	|
  0.727 [0]	|
  0.828 [0]	|
  0.930 [0]	|
  1.031 [14]	|


Latency distribution:
  10% in 0.0208 secs
  25% in 0.0220 secs
  50% in 0.0237 secs
  75% in 0.0260 secs
  90% in 0.0288 secs
  95% in 0.0320 secs
  99% in 0.0446 secs

Details (average, fastest, slowest):
  DNS+dialup:	0.0120 secs, 0.0165 secs, 1.0314 secs
  DNS-lookup:	0.0005 secs, 0.0000 secs, 0.0022 secs
  req write:	0.0000 secs, 0.0000 secs, 0.0008 secs
  resp wait:	0.0136 secs, 0.0077 secs, 0.2885 secs
  resp read:	0.0009 secs, 0.0000 secs, 0.2441 secs

Status code distribution:
  [200]	7537 responses

```
