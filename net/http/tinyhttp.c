//
// Created by Administrator on 2023/9/12.
//
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>

void error_die(const char *message);

int main(int argc, char *argv[]) {
    printf("Usage: namespace");

    int http_fd = -1;
    struct sockaddr_in server_addr;

    if ((http_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error_die("create socket failed");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8081);

    socklen_t server_addr_len = sizeof(server_addr);

    // 端口循环使用
    int on = 0;
    setsockopt(http_fd, SOL_SOCKET, SO_BINDTODEVICE, &on, on);

    if (bind(http_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        error_die("bind failed");
    }

    if (listen(http_fd, 5) < 0) {
        error_die("listen fail");
    }

    while (1) {
        // 接收请求
        if (accept(http_fd, (struct sockaddr *) &server_addr, &server_addr_len) < 0) {
            error_die("accept failed");
        }

        // 接收内容
        char buf[128] = "";
        if (recv(http_fd, buf, sizeof(buf), 0) < 0) {
            error_die(" recv failed");
        }

        printf("received content %s\n", buf);

        // 处理请求

    }

    return 0;
}

void error_die(const char *message) {
    perror(message);
    exit(1);
}
