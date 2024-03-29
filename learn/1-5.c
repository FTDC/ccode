#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 100

#define err_sys(info)                                            \
{                                                                \
    printf("%s\n", (info));                                       \
    exit(-1);                                                    \
}

int main()
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if ((pid = fork()) < 0) {
            err_sys("fork error!");
        } else if (0 == pid) {
            execlp(buf, buf, (char *)0);
//            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        if (pid = waitpid(pid, &status, 0) < 0)
            err_sys("waitpid error!");

        printf("%% ");
    }
    exit(0);
}
