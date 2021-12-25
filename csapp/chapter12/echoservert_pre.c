// 预线程化的并发服务器
// 就是在程序启动时，就启动一些 worker 线程准备工作，这样就不需要在运行时再去开启新线程，从而减少开销
#include "csapp.h"
#include "sbuf.h"

#define NTHREADS 4
#define SUBFSIZE 16

void echo_cnt(int connfd);
void *thread(void *vargp);

sbuf_t sbuf;

int main(int argc, char **argv)
{
    int listenfd, i, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    sbuf_init(&sbuf, SUBFSIZE);
    for (i = 0; i < NTHREADS; i++)
        Pthread_create(&tid, NULL, thread, NULL); // 线程池开辟

    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        printf("--- main thread accept new connection, and connfd=%d\n", connfd);
        sbuf_insert(&sbuf, connfd);
    }
}

void *thread(void *vargp)
{
    Pthread_detach(pthread_self());
    while (1)
    {
        int connfd = sbuf_remove(&sbuf); // sbuf_remove 使用基于信号量的 生产者-消费者 模型，会阻塞等待
        printf("--- sbuf remove new connfd=%d\n", connfd);
        echo_cnt(connfd);
        Close(connfd);
    }
}
