#include "csapp.h"

// 点分十进制转为 16进制
// 1. 把用户输入的点分十进制转为 network byte order
// 2. 把 network byte order 转为 host byte order
int main(int argc, char **argv)
{
    struct in_addr inaddr; // Network byte order
    u_int32_t addr;        // Host byte order

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <decimal ip address>\n", argv[0]);
        exit(0);
    }

    Inet_pton(AF_INET, argv[1], &inaddr);
    addr = ntohl(inaddr.s_addr);
    printf("%x\n", addr);
    exit(0);
}
