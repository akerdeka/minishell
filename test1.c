#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "includes/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int     pfd[2];
    int     ret;
    char    *buffer;
    char    **argv;    
    argv = malloc(sizeof(char **) * 3);
    argv[1] = NULL;
    buffer = malloc(sizeof(char *) * 10000);
    pipe(pfd);
    argv[0] = "testing";
    close(pfd[0]);
    dup2(pfd[1], 1);
    execve("/bin/ls", argv, NULL);
    dup2(pfd[0], 0);
    argv[0] = "testing";
    close(pfd[1]);
    execve("/bin/cat", argv, NULL);
    dup2(1, pfd[1]);
    printf("salut à vous");
}