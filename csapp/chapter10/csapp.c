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
    {
        unix_error("Open error");
    }

    return rc;
}

void Close(int fd)
{
    int rc;

    if ((rc = close(fd)) < 0)
    {
        unix_error("Close error");
    }
}
