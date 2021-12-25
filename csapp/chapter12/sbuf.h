#ifndef __SBUF__H__
#define __SBUF__H__

#include "csapp.h"

typedef struct
{
    int *buf;    // 缓冲数组
    int n;       // 槽位最大值
    int front;   // 头部
    int rear;    // 后部
    sem_t mutex; // 安全访问 buf
    sem_t slots; // 可用槽位
    sem_t items; // 可用 items
} sbuf_t;

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);

#endif
