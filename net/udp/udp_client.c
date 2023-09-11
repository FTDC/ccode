//
// Created by Administrator on 2023/9/11.
//
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>

void error_die(const char *message) {
    perror(message);
    exit(1);
}

int main(int argc, char *ars[]) {

    time_t timer;
    time(&timer);

    struct tm *tm;

    tm = localtime(&timer);

    char cur_time[80];

    strftime(cur_time, sizeof(cur_time), "%Y-%m-%d %H:%M:%s", tm);

    printf("current time: %s\n", cur_time);


    int client_fd = -1;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.

    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error_die("socket create error");
    }


    int accept_fd = -1;
    if ((accept_fd = connect(client_fd, addr, sizeof(addr))) < 0) {
        error_die("connect error");
    }



    return 0;
}