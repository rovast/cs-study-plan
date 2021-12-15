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
// stat
#include <sys/stat.h>
// close dup2
#include <unistd.h>
// opendir
#include <dirent.h>
// wait
#include <sys/wait.h>
// internet
#include <arpa/inet.h>
// socket
#include <sys/socket.h>
// addrinfo
#include <netdb.h>

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

/* Misc constants */
#define MAXLINE 8192 /* Max text line length */
#define MAXBUF 8192  /* Max I/O buffer size */
#define LISTENQ 1024 /* Second argument to listen() */

/* Our own error-handling functions */
void unix_error(char *msg);
void posix_error(int code, char *msg);
void dns_error(char *msg);
void gai_error(int code, char *msg);
void app_error(char *msg);

/*********************************************
 * Wrappers for Unix process control functions
 ********************************************/
pid_t Fork(void);
pid_t Wait(int *status);

/********************************
 * Wrappers for Unix I/O routines
 ********************************/
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

int Stat(const char *filename, struct stat *buf);
int Fstat(int fd, struct stat *buf);

// 目录相关操作
DIR *Opendir(const char *name);
struct dirent *Readdir(DIR *dirp);
int Closedir(DIR *dirp);

// IO重定向
int Dup2(int oldfd, int newfd);

/****************************
 * Sockets interface wrappers
 ****************************/
int Socket(int domain, int type, int protocol);
void Setsockopt(int s, int level, int optname, const void *optval, int optlen);
void Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
void Listen(int s, int backlog);
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

/* Protocol independent wrappers 协议无关的一些包装处理，比如 ipv4 ipv6 */
void Getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags);
void Freeaddrinfo(struct addrinfo *res);
void Inet_ntop(int af, const void *src, char *dst, socklen_t size);
void Inet_pton(int af, const char *src, void *dst);
