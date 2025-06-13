#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int status;
    int pid = fork();
    if (pid == 0)
    {
        char *arg[] = {"ls", NULL};
        if(execve("/usr/bin/ls", arg, NULL) == -1)
            perror("execve");
        printf("Hello\n");
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
    }
}