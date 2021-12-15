```
➜  chapter11 git:(main) ✗ gcc hostinfo.c csapp.c

➜  chapter11 git:(main) ✗ ./a.out 
Usage: ./a.out <domain name>

➜  chapter11 git:(main) ✗ ./a.out www.baidu.com
112.80.248.76
112.80.248.75
```

要想获得域名和 IP 之间的映射关系，需要进行如下步骤

1. 通过 getaddrinfo 获取到对应的 addrinfo 链表
2. 遍历链表，逐个输出地址信息
