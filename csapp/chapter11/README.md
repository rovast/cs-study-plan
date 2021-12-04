1. `hex2dd` 将输入的十六进制地址参数转换为点分十进制的字符串

核心是两个函数
- `htonl` 即 host -> network，将主机字节顺序转换为网络字节顺序（大端序）
- `inet_ntop` 即 network -> presentation，将二进制网络字节顺序转换为点分十进制字符串

```shell script
gcc hex2dd.c

./a.out 0x7f000001

#output 127.0.0.1
```
