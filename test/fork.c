#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        printf("hello from the child process my pid = %d\n", getpid());
    }
    else
    {
        printf("Hello from the parent process where pid = %d\n", getpid());
    }
}