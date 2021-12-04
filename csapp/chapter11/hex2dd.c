#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 50

int main(int argc, char **argv)
{
    struct in_addr in_addr;
    u_int32_t addr;
    char buf[BUF_SIZE];

    if (argc != 2)
    {
        fprintf(stderr, "usage %s <hex number>\n", argv[0]);
        exit(0);
    }

    sscanf(argv[1], "%x", &addr);
    in_addr.s_addr = htonl(addr);

    if (!inet_ntop(AF_INET, &in_addr, buf, BUF_SIZE))
    {
        fprintf(stderr, "inet_ntop error!");
        exit(-1);
    }

    printf("%s\n", buf);

    exit(0);
}
