//
// Created by Administrator on 2023/9/11.
//
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

// 错误处理
void error_die(const char *errMsg);

int main() {
//    time_t start;
    printf("socket udp server begin\n");
    // 输出当前时间
    time_t timer;
    struct tm *tm;

    time(&timer);

    tm = localtime(&timer);
    char cur_time[80];
    strftime(cur_time, sizeof(cur_time), "%Y-%m-%d %H:%M:%S", tm);
    printf("当前时间 %s \n", cur_time);

    int fd;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error_die("socket create error");
    }

    printf("Socket success!,sockfd=%d\n", fd);

    // 将套接字设置为允许重复使用本机地址或者设置为端口复用
    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        error_die("socket opt error :1223 \n");
    }

    struct sockaddr_in server_add;
    // 以 sockaddr 结构体填充socket信息
    server_add.sin_family = AF_INET; //设置结构类型为TCP/IP
    server_add.sin_addr.s_addr = htonl(INADDR_ANY); //服务端是等待别人来连，不需要找谁的ip
    //这里写一个长量INADDR_ANY表示server上所有ip，这个一个server可能有多个ip地址，因为可能有多块网卡
    server_add.sin_port = htons(5400); //指定一个端口号并将hosts字节型传化成Inet型字节型（大端或或者小端问题）

    // -- Server information
    printf("ip=%s , port= %d \n", inet_ntoa(server_add.sin_addr), ntohs(server_add.sin_port));

    //绑定地址与Socket
    if (bind(fd, (struct sockaddr *) &server_add, sizeof(server_add)) < 0) {
        error_die("bind error");
    }

//    server_add.sin_family = AF_INET;
//    server_add.sin_addr.s_addr = htonl(INADDR_ANY);
//    server_add.sin_port = htons(54004);
//
//    // 设置连接服务器网络地址为0
//    memset(&server_add, 0, sizeof(server_add));

//    if (bind(fd, (struct sockaddr *) &server_add, sizeof(server_add)) < 0) {
//        error_die("bind error");
//    }

    // 打印服务器信息
//    printf("client info :  ip address {%s}, port { %d }\n", inet_ntoa(server_add.sin_addr), ntohs(server_add.sin_port));

    // 监听 ，阻塞队列长度
    if (listen(fd, 2) < 0) {
        error_die("listen error");
    }

    struct sockaddr_in client_addr;
    // 客户端地址和客户端连接
    int client_addr_len = sizeof(client_addr);
    int client_fd = -1;

    // 发送服务器时间
    printf(" client info : ipaddr { %u } port {%d}", ntohl(client_addr.sin_addr.s_addr), ntohs(client_addr.sin_port));

    while (1) {

        if ((client_fd = accept(fd, (struct sockaddr *) &client_addr, &client_addr_len)) < 0) {
            error_die("accept error");
        }


        // 接收内容
        char acceptMsg[128];
        if (recv(client_fd, acceptMsg, sizeof(acceptMsg), MSG_PEEK) < 0) {
            error_die("recv message error");
        }

        if (strncmp("quit", acceptMsg, sizeof(4))) {
            exit(1);
        }

        char backMsg[128] = {21, 3};
        // 结束符
        backMsg[sizeof(backMsg) - 1] = '\0';
        strcpy(backMsg, acceptMsg);

        if (send(client_fd, acceptMsg, sizeof(acceptMsg), 0) < 0) {
            error_die(" send client message error");
        }

    }

    // 恢复内容

//    return 0;
}


void error_die(const char *errMsg) {
    perror(errMsg);
    exit(1);
}
