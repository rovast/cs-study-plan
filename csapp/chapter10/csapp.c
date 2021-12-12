#include "csapp.h"

/**
 * *********** 错误处理函数 *********************
 */

/**
 * Unix 风格的错误处理函
 * 
 * 早期的 unix 函数遇到错误时，返回 -1，同时会设置全局的 errorno
 */
void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

/**
 * Posix 风格错误处理函数
 * 
 * 较新的 POSIX 函数，用返回值0表示成功，非0则表示错误码。返回的有用结果会放在参数中
 */
void posix_error(int code, char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

/**
 * getaddrinfo(GAI) 各 getnameinfo 函数成功时返回零，失败时返回非0
 */
void gai_error(int code, char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

/**
 * 抛出应用级别错误
 */
void app_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}

/**
 * *********** UNIX IO 包装 *********************
 */
int Open(const char *pathname, int flags, mode_t mode)
{
    int rc;

    if ((rc = open(pathname, flags, mode)) < 0)
        unix_error("Open error");

    return rc;
}

ssize_t Read(int fd, void *buf, size_t count)
{
    ssize_t rc;

    if ((rc = read(fd, buf, count)) < 0)
        unix_error("Read error");

    return rc;
}

ssize_t Write(int fd, const void *buf, size_t count)
{
    ssize_t rc;

    if ((rc = write(fd, buf, count)) < 0)
        unix_error("Write error");

    return rc;
}

void Close(int fd)
{
    int rc;

    if ((rc = close(fd)) < 0)
        unix_error("Close error");
}

/****************************************
 * The Rio package - Robust I/O functions
 ****************************************/

/*
 * rio_readn - Robustly read n bytes (unbuffered)
 * 从 fd 中读取 n 字节到 usrbuf
 * 在遇到应用程序信号中断时，会自动重启 read
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;    // 剩余未读的梳理
    ssize_t nread;       // 已读取的
    char *bufp = usrbuf; // 每次读取的缓存区

    while (nleft > 0) // 如果还剩余未读的，就一直读下去
    {
        if ((nread = read(fd, bufp, nleft)) < 0) // 读取异常啦？可能两种原因：1、中断 2、异常
        {
            if (errno == EINTR) // 1、中断，那么重新读取吧
                nread = 0;
            else // 2、其他异常，直接抛出错误码
                return -1;
        }
        else if (nread == 0) // 遇到 EOF 了
        {
            break;
        }

        nleft -= nread; // 每次读取 nread 大小
        bufp += nread;  // usrbuf 指针操作，这样可以一直填充 usrbuf
    }

    return (n - nleft); // 返回已经读取的字节数
}

/*
 * rio_writen - Robustly write n bytes (unbuffered)
 * 从 usrbuf 中传递 n 字节到 fd 中
 */
ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    ssize_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while (nleft > 0)
    {
        if ((nwritten = write(fd, usrbuf, nleft)) <= 0)
        {
            if (errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }

        nleft -= nwritten;
        bufp += nwritten;
    }

    return n;
}

void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;

    while (rp->rio_cnt <= 0)
    {
        // 一次读取最大 buf 到内存，留着以后慢慢消费
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));

        if (rp->rio_cnt < 0)
        {
            if (errno != EINTR)
                return -1;
        }
        else if (rp->rio_cnt == 0)
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf;
    }

    cnt = n;
    if (rp->rio_cnt < 0)
        cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c, *bufp = usrbuf;

    for (n = 1; n < maxlen; n++)
    {
        if ((rc = rio_read(rp, &c, 1)) == 1) // 这里虽然每次只读取一个字节，但是是带缓存的
        {
            *bufp++ = c;
            if (c == '\n')
            {
                n++;
                break;
            }
        }
        else if (rc == 0)
        {
            if (n == 1)
                return 0; // EOF no data read
            else
                break; // EOF some data was read
        }
        else
            return -1;
    }
    *bufp = 0;
    return n - 1;
}

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0)
    {
        if ((nread = rio_read(rp, bufp, nleft)) < 0) // 读取字节到 usrbuf，其中 rio_read 函数会自动设置指针来填充 usrbuf
            return -1;
        else if (nread == 0)
            break; // EOF
        nleft -= nread;
        bufp += nread;
    }

    return (n - nleft);
}
