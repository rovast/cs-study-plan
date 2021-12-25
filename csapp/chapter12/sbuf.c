#include "sbuf.h"

void sbuf_init(sbuf_t *sp, int n)
{
    sp->buf = Calloc(n, sizeof(int)); // calloc 申请了 n 个  sizeof(int) 的连续控件，且返回指向分配控件的指针
    sp->n = n;                        // 容量
    sp->front = sp->rear = 0;         // 头尾指针为0
    Sem_init(&sp->mutex, 0, 1);       // 初始化互斥信号（为了安全访问buf）
    Sem_init(&sp->slots, 0, n);       // 初始化可用槽位
    Sem_init(&sp->items, 0, 0);       // 初始化已用元素
}

void sbuf_deinit(sbuf_t *sp)
{
    Free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item)
{
    P(&sp->slots);                          // 可用槽位 -1
    P(&sp->mutex);                          // 安全操作 buf
    sp->buf[(++sp->rear) % (sp->n)] = item; // 加入元素到 buf
    V(&sp->mutex);                          // 解锁 buf 访问
    V(&sp->items);                          // 已有元素 +1
}

int sbuf_remove(sbuf_t *sp)
{
    int item;
    P(&sp->items);                           // 元素个数-1
    P(&sp->mutex);                           // 加互斥锁
    item = sp->buf[(++sp->front) % (sp->n)]; //取出第一个元素（头部元素）
    V(&sp->mutex);                           // 解互斥锁
    V(&sp->slots);                           // 槽位+1
    return item;                             // 返回移除的元素
}
