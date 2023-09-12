//
// Created by Administrator on 2023/9/11.
//
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

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


    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error_die("socket create error");
    }


    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(atoi("5400"));


    char buf[32] = "";
    while (1) {

//        char buf[128] = "";
        fgets(buf, sizeof(buf), stdin);

        buf[strlen(buf) - 1] = '\0';

        // 退出选项
        if (strncmp(buf, "quit", 4) == 0) {
            exit(1);
        }

        // 发送内容
        if (sendto(client_fd, buf, sizeof(buf), 0, (struct sockaddr *) &server_addr,
                   sizeof(server_addr)) < 0) {
            error_die("send message error");
        }

        char text[32] = "";

        // 接收内容
        if (recvfrom(client_fd, text, sizeof(text), 0, (struct sockaddr *) &server_addr, &server_addr_len) < 0) {
            error_die("recv message error");
            exit(1);
        }
//        if (recvfrom(client_fd, text, sizeof(text), 0, (struct sockaddr *) &server_addr, &server_addr_len) < 0) {
//            perror("fail to recvfrom");
//            exit(1);
//        }
        printf("from server: %s\n", text);

    }


//    close(client_fd);


//    return 0;
}