#include "csapp.h"

void *thread(void *vargp);

int main()
{
    pthread_t tid;
    Pthread_create(&tid, NULL, thread, NULL);
    printf("-- Before pthread_join --\n");
    Pthread_join(tid, NULL);
    printf("-- After pthread_join --\n");
    exit(0);
}

void *thread(void *vargp)
{
    printf("Hello world!\n");
    return NULL;
}
