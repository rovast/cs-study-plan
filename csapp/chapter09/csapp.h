#ifndef __CSAPP_H__
#define __CSAPP_H__

#include <sys/mman.h>

void *Mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

int Open(const char *pathname, int flags);

int fstat(int fd, struct stat *buf);

#endif
