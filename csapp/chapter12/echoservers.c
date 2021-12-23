#include "csapp.h"

typedef struct
{
    int maxfd;                   // read_set 的最大描述符
    fd_set read_set;             // 所有监听的活动描述符
    fd_set ready_set;            // 准备好读的描述符列表
    int nready;                  // 当前准备好的文件描述符数量，通过这个值，我们可以知道需要处理的IO事件个数
    int maxi;                    // 当前使用的池子最高水位(最大index)
    int clientfd[FD_SETSIZE];    // 客户端链接池 client fd pool
    rio_t clientrio[FD_SETSIZE]; //
} pool;

void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);

int byte_cnt = 0;

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while (1)
    {
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &pool.ready_set))
        {
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        check_clients(&pool);
    }
}

void init_pool(int listenfd, pool *p)
{
    int i;
    p->maxfd = -1;
    for (i = 0; i < FD_SETSIZE; i++)
        p->clientfd[i] = -1;

    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

// 找到可用槽位，进行 connfd 的 select 事件监听
void add_client(int connfd, pool *p)
{
    int i;
    p->nready--; // ?

    for (i = 0; i < FD_SETSIZE; i++) // 寻找可用的 slot
        if (p->clientfd[i] < 0)      // 找到可用的槽位
        {
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            FD_SET(connfd, &p->read_set);

            if (connfd > p->maxfd)
                p->maxfd = connfd;

            if (i > p->maxi)
                p->maxi = i;

            break;
        }

    if (i == FD_SETSIZE)
        app_error("add_client error: Too many clients");
}

void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++)
    {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set)))
        {
            p->nready--;

            if ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
            {
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d\n",
                       n, byte_cnt, connfd);

                Rio_writen(connfd, buf, n);
            }
            else
            {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}
