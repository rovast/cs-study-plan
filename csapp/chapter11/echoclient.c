#include "csapp.h"

int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    // Rio_readinitb(&rio, clientfd); // Removed this line will still be ok?

    while (Fgets(buf, MAXLINE, stdin) != NULL)
    {
        Rio_writen(clientfd, buf, strlen(buf));
        // Rio_readlineb(&rio, buf, MAXLINE); // Removed this line will still be ok?
        Fputs(buf, stdout); // 输出到终端
    }

    Close(clientfd);
    exit(0);
}
