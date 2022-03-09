#include "kernel/types.h"
#include "user/user.h"

/**
 *           p1[1] |----[pipe1]------> p1[0]
 * Parent process                            Child process
 *           p2[0] <----[pipe2]-------| p2[1]
 */

int main(int argc, char *argv[])
{
    // pipe 管道是单向流
    int p1[2];  // 父进程通过 p1 发送数据给子进程
    int p2[2];  // 子进程 -- p2 --> 父进程
    int buf[1]; // 发送的字节

    // 创建 pipe
    pipe(p1);
    pipe(p2);
    if (fork() > 0) // 父进程
    {
        close(p1[0]); // 通过 p1 发送，所以不需要 p1 的接收端
        close(p2[1]); // 通过 p2 接收，所以不需要 p2 的发送端

        write(p1[1], " ", 1); // 通过 p1 发送数据给子进程

        read(p2[0], buf, 1); // 通过 p2 读取子进程是数据
        printf("%d: received pong\n", getpid());

        exit(1);
    }
    else
    {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], buf, 1);
        printf("%d: received ping\n", getpid());

        write(p2[1], " ", 1);

        exit(0);
    }
}
