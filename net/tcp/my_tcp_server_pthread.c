//
// Created by Administrator on 2023/9/6.
//

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

#define N 128

void handler(int sig) {
    // 不在意结束状态值, 则参数 status 可以设成NULL
    wait(NULL);
}

// 连接标识符
struct Socket_connect {
    struct sockaddr_in addr;
    int acceptfd;
} SOCK_FD;

// 启动服务端
int startServer();

// 处理请求
void *handle_request(void *arg);

// 错误处理
void error_die(const char *errMsg);

void *handle_request(void *arg) {
    char buf[N];
    struct Socket_connect fd = *(struct Socket_connect *) arg;
    while (1) {
        // 接收内容的长度, MSG_PEEK： 窥视传入的数据。 数据被复制到缓冲区中，但不会从输入队列中删除。
        int receive_byte = recv(fd.acceptfd, buf, N, 0);
        // if(recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&clientaddr, &addrlen) == -1)
        if (receive_byte == -1) {
            error_die(" recv error");
        }
        if (strncmp(buf, "quit", 4) == 0) {
            error_die("the client command quite close \n");
        } else if (receive_byte == 0) {
            printf("client quite");
            pthread_exit(NULL);
        }


        // 打印接收的数据报文
        printf("from client: %s:%d --> %s\n", inet_ntoa(fd.addr.sin_addr), ntohs(fd.addr.sin_port), buf);

        // 拼接字符串 ，在结尾增加 *_*
        strcat(buf, " -- *_*");

        if (send(fd.acceptfd, buf, N, 0) == -1) {
            error_die("send error");
        }


    }


    // 关闭连接
//    close(acceptfd);

//    printf("hostname", gethostname(acceptfd, sizeof()))

}

int main(void) {
    printf("************** Start Server ****************** \n");

    // 本地服务先启动
    int sockfd = startServer();

    // 客户端连接
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 默认连接状态为失败
    int client_fd = -1;

    // 使用信号，异步的方式处理僵尸进程
    signal(SIGCHLD, handler);

    // 接收处理的数据
    while (1) {

        if ((client_fd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_len)) < 0) {
            error_die("accept fail");
        }

        // 输出客户端的IP和端口
        printf("client_fd = %d, client_addr= %s， client_prot= %d\n", client_fd, inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        // todo: 使用 fork 函数创建子进程， 父进程负责链接操作， 子进程负责与客户端通信
        pthread_t tid;

        struct Socket_connect socket_fd = {client_addr, client_fd};

        if ((tid = pthread_create(&tid, NULL, handle_request, &socket_fd)) != 0) {
            error_die("fork() fail;");
        }
        // 线程主动与主控线程断开关系。线程结束后（不会产生僵尸线程），其退出状态不由其他线程获取，而直接自己自动释放（自己清理掉PCB的残留资源）
        pthread_detach(tid);


//        int receive_byte;
//        while (1) {
//            char buf[N] = "";
//            // 接收内容的长度, MSG_PEEK： 窥视传入的数据。 数据被复制到缓冲区中，但不会从输入队列中删除。
//            receive_byte = recv(client_fd, buf, N, 0);
//            // if(recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&clientaddr, &addrlen) == -1)
//            if (receive_byte == -1) {
//                error_die(" recv error");
//            } else if (receive_byte == 0) {
//                error_die(" the client quite !");
//            }
//
//            // 区分大小写，对比前面4个字符
//            if (strncmp(buf, "quit", 4) == 0) {
//                exit(0);
//            }
//
//            // 打印接收的数据报文
//            printf("from client: %s\n", buf);
//
//            // 拼接字符串 ，在结尾增加 *_*
//            strcat(buf, " -- *_*");
//
//            // 发送信息
//            if (send(client_fd, buf, strlen(buf), 0) == -1) {
//                error_die("send error");
//            }
//        }
    }

    // 关闭连接
    close(sockfd);

    return 0;
}


int startServer() {
    struct sockaddr_in serverAddr;


    // 监听本地端口
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        error_die("socket error");
    }

    // 将套接字设置为允许重复使用本机地址或者设置为端口复用
    int on = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        error_die("socket opt error :1223 \n");
    }

    printf("Socket success!,sockfd=%d\n", sockfd);

    // todo : check 不知道干什么
    memset(&serverAddr, 0, sizeof(serverAddr));

    // 以 sockaddr 结构体填充socket信息
    serverAddr.sin_family = AF_INET; //设置结构类型为TCP/IP
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //服务端是等待别人来连，不需要找谁的ip
    //这里写一个长量INADDR_ANY表示server上所有ip，这个一个server可能有多个ip地址，因为可能有多块网卡
    serverAddr.sin_port = htons(4000); //指定一个端口号并将hosts字节型传化成Inet型字节型（大端或或者小端问题）

    // -- Server information
    printf("ip=%s , port= %d \n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    //绑定地址与Socket
    if (bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        error_die("bind error");
    }

    // 监听端口
    if (listen(sockfd, 5) < 0) {
        error_die("listen error");
    }

    return sockfd;
}


/**
 *  错误信息
 * @param errMsg
 */
void error_die(const char *errMsg) {
    perror(errMsg);
    exit(1);
}
