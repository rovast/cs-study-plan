#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void unix_error(char *msg)
{
    fprintf(stderr, "%s: %d\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork()
{
    pid_t pid;
    if ((pid = fork()) < 0)
        unix_error("fork error");

    return pid;
}

int main()
{
    Fork();
    Fork();
    printf("Hello.\n");
}
