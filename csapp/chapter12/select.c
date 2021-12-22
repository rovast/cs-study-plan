#include "csapp.h"

void echo(int connfd);
void command(void);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]);

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);

    while (1)
    {
        ready_set = read_set;
        Select(listenfd + 1, &ready_set, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &ready_set))
        {
            char *msg = "Emit input event\n";
            Rio_writen(STDOUT_FILENO, msg, strlen(msg));

            command();
        }
        else if (FD_ISSET(listenfd, &ready_set))
        {
            char *msg = "Emit socket event\n";
            Rio_writen(STDOUT_FILENO, msg, strlen(msg));

            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            echo(connfd);
            Close(connfd);
        }
    }
}

void command(void)
{
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
        exit(0);

    printf("%s", buf);
}
