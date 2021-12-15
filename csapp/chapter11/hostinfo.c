#include "csapp.h"

int main(int argc, char **argv)
{
    struct addrinfo *p, *listp, hints;
    char buf[MAXBUF];
    int rc, flags;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    // 获取 addrinfo 记录链表数据
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // ipv4 only
    hints.ai_socktype = SOCK_STREAM; // connection only TCP
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    // 遍历结果进行输出
    flags = NI_NUMERICHOST; // 输出 adress 而不是 domain
    for (p = listp; p; p = p->ai_next)
    {
        Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }

    Freeaddrinfo(listp);

    exit(0);
}
