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
// close
#include <unistd.h>

int Open(const char *pathname, int flags, mode_t mode);
void Close(int fd);
