
#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "includes/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

//NE PAS SUPPRIMER TEST POUR PARSING

int main(void)
{
    int     pfd[2];
    int     ret;
    char    *buffer; 
    buffer = malloc(sizeof(char *) * 10000);
    pipe(pfd);
    int i = 0;
    int pid;
    char    *argv[6];
    argv[0] = "/bin/ls";
    argv[1] = "/bin/ls";
    int fd;
    //hello world
    fd = open("./main.c", O_RDONLY); // pour trouver le bon executable utiliser open sans oublier de close
    printf("%d\n", fd);
    char    *argv1[3][5];
    argv1[0][0] = "ls";
    argv1[0][1] = NULL;
    argv1[1][0] = "ls";
    argv1[1][4] = "-i";
    argv1[1][2] = "/home/user42/42/minish/test.c";
    argv1[1][1] = NULL;
    //while(i < 2)
    //{
       // pid = fork();
       // //dprintf(1, "actual ID = %d\n", pid);
       // if (pid == 0)
       // {
       //     //dprintf(1, "%s\n",argv1[i][0]);
       //     if (i + 1 < 2)
       //     {
       //         dup2(pfd[1], 1);
       //     }
       //     else
       //         dup2(pfd[0], 0);
            execve(argv[1], argv1[1], NULL);
       // }
       //else
       //{
       //        close(pfd[1]);
       //     while ((ret = read(pfd[0], buffer, 1023)) > 0)
       //     {
       //         buffer[ret] = 0;
       //         printf("%s\n", buffer);
       //     }
       //     close(pfd[0]);
       //}
    //    i++;
    //}
    // int     i = 0;
    // int     stdoutcopy = dup(1);
    //  dprintf(1, "hey");
    //  dup2(pfd[0], 1);
    //  close(pfd[0]);
    //  dup2(stdoutcopy, 1);
    //  close(stdoutcopy);
    //       argv[0] = "cat";
    //  argv[1] ="test.c";
    //  argv[2] = NULL;
    //  dup2(pfd[1], 0);
    //  execve("/bin/cat", argv, NULL);
    //  dprintf(1, "hey");
    // int     id;
    // int fd = open("testing", O_CREAT | O_RDWR | O_TRUNC, 0644);
    //     id = fork();
    // if (id == 0)
    // {
    //     NULL;
    // }
    // else
    // {
    //     dup2(fd, 1);
    //     dup2(fd, 0);
    //     close(fd);
    //     printf("bonjour\n");
    // }
    //     i++;
    // if (id == 0)
    // {
    //     argv[0] = "testing";
    //     close(pfd[0]);
    //     dup2(pfd[1], 1);
    //     execve("/bin/ls", argv, NULL);
    // }
    // else
    // {
    //     dup2(pfd[0], 0);
    //     argv[0] = "testing";
    //     close(pfd[1]);
    //     execve("/bin/cat", argv, NULL);
    //     // while ((ret = read(pfd[0], buffer, 1023)) != 0)
    //     // {
    //     //     buffer[ret] = 0;
    //     // }
    // }
}

// int main(void)
// {
//     char *argv[2];
//     int     status;
//     argv[0] = "/bin/ls";
//     argv[1] = NULL;
//     int pfd[2];
//     pipe(pfd);
//     int     id = fork();
//     printf("%d\n", id);
//     if (id != 0)
//     {
//         dup2(pfd[1], 1);
//         execve(argv[0], argv, NULL);
//     }
//     else
//     {   
//         int     i = 0;
//         int     ret;
//         char buffer[10000];
//         close(pfd[1]);
//         while (((ret = read(pfd[0], buffer, 1023)) != 0))
//         {
//             buffer[ret] = 0;
//             i++;
//         }
//         wait(&status);
//     }
// }