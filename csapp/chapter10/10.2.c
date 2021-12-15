#include "csapp.h"

int main()
{
    int fd1, fd2;
    char c;

    fd1 = Open("foo.txt", O_RDONLY, 0);
    fd2 = Open("foo.txt", O_RDONLY, 0);

    Read(fd1, &c, 1); // 两个描述符，所以各自读取的文件位置独立
    Read(fd2, &c, 1);

    printf("c = %c\n", c);
    exit(0);
}
