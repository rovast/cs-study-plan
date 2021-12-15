#include "csapp.h"

int main(int argc, char **argv)
{
    DIR *streamp;
    struct dirent *dep;

    streamp = Opendir(argv[1]);

    while ((dep = Readdir(streamp)) != NULL)
    {
        printf("Fond file: %s\n", dep->d_name);
    }

    Closedir(streamp);
    exit(0);
}