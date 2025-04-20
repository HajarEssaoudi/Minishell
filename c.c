#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
  int index = 0;
  while (envp[index])
  {
    printf("%s\n", envp[index++]);
  }
}