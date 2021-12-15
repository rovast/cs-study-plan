#include "csapp.h"

// 把输入的 16进制地址格式转换为 点分十进制 表示方式
// 分为如下阶段
//   1. host 转 internet
//   2. internet 转 点分十进制
int main(int argc, char **argv)
{
    struct in_addr inaddr; // Address in Network byte order
    u_int32_t addr;        // Address in host byte order
    char buf[MAXBUF];      // Buffer for dotted-decimal string

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <hex number>\n", argv[0]);
        exit(0);
    }

    sscanf(argv[1], "%x", &addr);
    inaddr.s_addr = htonl(addr);

    if (!inet_ntop(AF_INET, &inaddr, buf, MAXBUF))
        unix_error("inet_ntop error");

    printf("%s\n", buf);
    exit(0);
}
