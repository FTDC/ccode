//
// Created by Administrator on 2023/9/7.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define N 128

// 错误处理
void error_die(const char *errMsg);

int main() {
    int client_fd;
    // Initial
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error_die("socket error");
    }

    struct sockaddr_in server_addr;
    socklen_t socket_len = sizeof(server_addr);
    char ipaddr[] = "127.0.0.1";

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    server_addr.sin_addr.s_addr = htonl(atoi("127.0.0.1"));
    // connect
    if (connect(client_fd, (struct sockaddr *) &server_addr, socket_len) == -1) {
        // 连接
        error_die("connect error");
    }

    char buf[N]="";
//    time_t now = ctime(NULL);

    while (1) {

        fgets(buf, N, stdin);
        // end flag
        buf[strlen(buf) - 1] = '\0';

        // send message
        if (send(client_fd, buf, sizeof(buf), 0) == -1) {
            error_die("send msg error");
        }
        printf("send msgr: %s\n", buf);

        // receive message
        char receive_msg[N] = "";
        if (recv(client_fd, receive_msg, N, 0) == -1) {
            error_die("receive message error");
        }
        printf("from server: %s\n", receive_msg);

        // quit 指定退出， 否则一直能输入
        if (strncmp(buf, "quit", 4) == 0) {
            exit(0);
        }

        // 清空缓冲区
//        bzero(buf, N);
    }

    close(client_fd);

    return 0;
}


/**
 *  错误信息
 * @param errMsg
 */
void error_die(const char *errMsg) {
    perror(errMsg);
    exit(1);
}