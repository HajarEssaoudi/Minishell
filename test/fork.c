#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        printf("hello from the child process\n");
    }
    else
    {
        printf("Hello from the parent process where pid = %d\n", pid);
    }
}