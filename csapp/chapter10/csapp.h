// fprintf stderr
#include <stdio.h>
// exit
#include <stdlib.h>
// errno
#include <errno.h>
// strerror
#include <string.h>

// open
#include <fcntl.h>
// ssize
#include <sys/types.h>
#include <sys/stat.h>
// close
#include <unistd.h>

/* Persistent state for the robust I/O (Rio) package */
/* $begin rio_t */
#define RIO_BUFSIZE 8192 // RIO BUF大小
typedef struct
{
    int rio_fd;                /* Descriptor for this internal buf */
    int rio_cnt;               /* Unread bytes in internal buf */
    char *rio_bufptr;          /* Next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE]; /* Internal buffer */
} rio_t;
/* $end rio_t */

/**
 * Wrappers for IO
 */
int Open(const char *pathname, int flags, mode_t mode);
ssize_t Read(int fd, void *buf, size_t n);
ssize_t Write(int fd, const void *buf, size_t n);
void Close(int fd);

// RIO 无换成你输入输出函数至多传送 n 字节到内存位置 usrbuf。如果被应用信号处理程序中断，每个函数会手动重启
ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);

// RIO 带缓冲的输入函数，先预读一部分内容至缓冲区
void rio_readinitb(rio_t *rp, int fd);
// read_line with buff
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
// rio_readn with buff
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
