#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{int fd= open("ma", O_RDWR | O_CREAT | O_APPEND, 0644);
    int fd2= open("mar", O_RDWR | O_CREAT | O_APPEND, 0644);
    int fd1 = dup(fd);
    dup2(fd1, fd2);
    printf("%d\n", fd);
    printf("%d\n", fd1);
write(fd2, "55555\n", 6);
}