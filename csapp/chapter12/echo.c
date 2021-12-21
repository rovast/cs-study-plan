#include "csapp.h"

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    char msg[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        Rio_writen(connfd, buf, n);

        // $start output msg
        buf[n] = '\0';
        sprintf(msg, "Recv:(%4d bytes) %s\n", (int)n, buf);
        Rio_writen(STDOUT_FILENO, msg, strlen(msg));
        // $end output msg
    }
}
