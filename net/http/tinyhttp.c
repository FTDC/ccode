//
// Created by Administrator on 2023/9/12.
//
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define SERVER_STRING "Server: mys httpd/0.1.0\r\n"

/**
 * 错误信息处理
 * @param message string
 */
void error_die(const char *message);

/**
 * 处理HTTP请求
 * @param http_fd  客户端请求连接
 */
void handle_request(int http_fd);

/**
 * 获取缓冲器大小
 * @param http_fd 客户端请求连接
 * @param buf  缓冲区
 * @param size 缓冲区大小
 * @return 缓冲区大小
 */
int get_line(int http_fd, char *buf, int size);

/**
 * 方法不支持返回
 * @param http_fd  客户端请求连接
 */
void unimplemented(int http_fd);

/**
 * 没找到文件
 * @param http_fd  客户端请求连接
 */
void not_found(int http_fd);

/**
 * 处理访问文件
 * @param http_fd  客户端请求连接
 * @param path  文件路径
 */
void serve_file(int http_fd, char *path);

void execute_cgi(int fd, char *path, char *method, char *queryString);

/**
 * 回复内容头部信息
 * @param http_fd  客户端连接
 * @param path  文件路径
 */
void headers(int http_fd, char *path);

/**
 *  查看文件
 * @param http_fd 客户端请求连接
 * @param pFile  文件指针
 */
void cat(int http_fd, FILE *file_path);

void bad_request(int http_fd);

void cannot_execute(int http_fd);

int main(int argc, char *argv[]) {
    printf("Usage: namespace \n");

    int http_fd = -1;
    struct sockaddr_in server_addr;

    if ((http_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error_die("create socket failed");
    }

    srand((unsigned) time(NULL));
    int port = random() % 510 + 8000;
//    int port = 8081;
    printf("port: %d\n", port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);


    socklen_t server_addr_len = sizeof(server_addr);

    // 端口循环使用
    int on = 0;
    if (setsockopt(http_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        error_die("set socket opt fail");
    }

    if (bind(http_fd, (struct sockaddr *) &server_addr, server_addr_len) < 0) {
        error_die("bind failed");
    }

    // 打印端口，测试方法
//    if(getsockname(http_fd, (struct sockaddr *) &server_addr, &server_addr_len) <0){
//        error_die("get socket name  fail");
//    }

    if (listen(http_fd, 5) < 0) {
        error_die("listen fail");
    }

    // 客户端
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);


    while (1) {
        int client_fd = -1;
        // 接收客户端请求
        if ((client_fd = accept(http_fd, (struct sockaddr *) &client_addr, &client_addr_len)) < 0) {
            error_die("accept failed");
        }

        printf("client ip :: {%s, %d} \n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));


        // 处理请求
        handle_request(client_fd);

    }

    return 0;
}

void handle_request(int http_fd) {
    char buf[1024] = "";

    // 请求方法/ url/ path
    char method[255];
    char url[255];
    char path[512];

    // 请求地址
    char *query_string = NULL;

    size_t i = 0, j = 0;

    // 字符数量
    int chars_nums = 0;

    // 是否开启cgi
    int cgi = 0;

    // 访问的文件结构体
    struct stat st;

    // 接收内容
//    if (recv(http_fd, buf, sizeof(buf), MSG_PEEK) < 0) {
//        error_die(" recv failed");
//    }
////    printf("from ip {%s, %d}:: received content,  %s\n", buf);
//    printf("from ip :: received content,  %s\n", buf);


    // 获取缓冲区字节数大小
    chars_nums = get_line(http_fd, buf, sizeof(buf));

    while (!isspace(buf[j]) && (i < sizeof(method) - 1)) {
        method[i] = buf[j];
        i++;
        j++;
    }
    method[i] = '\0';


    printf("http request method:: %s\n", method);

    //如果请求的方法不是 GET 或 POST 任意一个的话就直接发送 response 告诉客户端没实现该方法
    if (!strcasecmp(method, "GET") && !strcasecmp(method, "POST")) {
        unimplemented(http_fd);
        return;
    }

    //如果是 POST 方法就将 cgi 标志变量置一(true)
    if (strcasecmp(method, "POST") == 0) {
        cgi = 1;
    }

    i = 0;
    //跳过所有的空白字符(空格)
    while (isspace(buf[j]) && (j < sizeof(buf)))
        j++;

    //然后把 URL 读出来放到 url 数组中
    while (!isspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf))) {
        url[i] = buf[j];
        i++;
        j++;
    }
    url[i] = '\0';

    printf("http request url %s \n", url);

    //如果这个请求是一个 GET 方法的话
    if (strcasecmp(method, "GET") == 0) {
        //用一个指针指向 url
        query_string = url;

        // 遍历 url, 跳过字符 ? 前面的所有字符， 如果遍历完毕也没有找到 ? 则退出循环
        while ((*query_string != '?') && (*query_string != '\0')) {
            query_string++;
        }

        // 退出循环后， 检查当前字符是 ? 还是字符串（url）的结尾
        if (*query_string == '?') {
            //如果是 ? 的话，证明这个请求需要调用 cgi，将 cgi 标志变量置一(true)
            cgi = 1;
            //从字符 ? 处把字符串 url 给分隔会两份
            *query_string = '\0';
            //使指针指向字符 ? 后面的那个字符
            query_string++;
        }
    }

    //将前面分隔两份的前面那份字符串，拼接在字符串htdocs的后面之后就输出存储到数组 path 中。相当于现在 path 中存储着一个字符串
    sprintf(path, "htdocs%s", url);

    //如果 path 数组中的这个字符串的最后一个字符是以字符 / 结尾的话，就拼接上一个"index.html"的字符串。首页的意思
    if (path[strlen(path) - 1] == '/') {
        strcat(path, "index.html");
    }


    // 查看文件状态
    if (stat(path, &st) == -1) {
        // todo: 如果不存在，那把这次 http 的请求后续的内容(head 和 body)全部读完并忽略
        while ((chars_nums > 0) && strcmp("\n", buf)) { /* read & discard headers */
            chars_nums = get_line(http_fd, buf, sizeof(buf));
        }
        //然后返回一个找不到文件的 response 给客户端
        not_found(http_fd);
    } else {
        // todo: 如果文件存在， 那去和常量 S_IFMT 相与， 相与之后的值可以判断该文件的类型
        if ((st.st_mode & S_IFMT) == S_IFDIR) {
            // 如果文件类型是目录， 则需要再path 后面凭借一个 "index.html" 的字符串
            strcat(path, "index.html");
        }

        // 如果这个文件是一个可执行文件，不论是属于用户/组/其他这三者类型的，就将 cgi 标志变量置一
        // 判断是否为可执行文件， 如果是可执行文件则 启用 cgi
        if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH)) {
            cgi = 1;
        }
    }


    printf("cgi:: %d", cgi);
    if (!cgi) {
        //如果不需要 cgi 机制的话，
        serve_file(http_fd, path);
    } else {
        printf("cgi::====== %d", cgi);
        //如果需要则调用
        execute_cgi(http_fd, path, method, query_string);

    }

//    close(http_fd);


}

void execute_cgi(int http_fd, char *path, char *method, char *query_string) {
    char buf[1024];
    int cgi_output[2];
    int cgi_input[2];
    // 线程ID
    pid_t pid;

    // 内容长度
    int content_length = -1;

    int char_nums = 1;
    //往 buf 中填东西以保证能进入下面的 while
    buf[0] = 'A';
    buf[1] = '\0';
    //如果是 http 请求是 GET 方法的话读取并忽略请求剩下的内容
    if (strcasecmp(method, "GET") == 0) {
        while ((char_nums > 0) && strcmp("\n", buf)) {  /* read & discard headers */
            char_nums = get_line(http_fd, buf, sizeof(buf));
        }
    } else {/* POST */
        //只有 POST 方法才继续读内容
        char_nums = get_line(http_fd, buf, sizeof(buf));
        // todo:  读取一行数据，并且结尾是换行符
        while ((char_nums > 0) && strcmp("\n", buf)) {
            buf[15] = '\0';
            if (strcasecmp(buf, "Content-Length:") == 0) {
                content_length = atoi(&(buf[16])); //记录 body 的长度大小
            }
            char_nums = get_line(http_fd, buf, sizeof(buf));
        }

        // 没有内容长度， 则提示请求错误
        if (content_length == -1) {
            bad_request(http_fd);
            return;
        }
    }

    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    send(http_fd, buf, strlen(buf), 0);

    //下面这里创建两个管道，用于两个进程间通信
    if (pipe(cgi_output) < 0) {
        cannot_execute(http_fd);
        return;
    }
    if (pipe(cgi_input) < 0) {
        cannot_execute(http_fd);
        return;
    }

    //创建一个子进程  PID =0  则创建子进程成功  -1 则创建错误
    if ((pid = fork()) < 0) {
        cannot_execute(http_fd);
        return;
    }

    //子进程用来执行 cgi 脚本
    if (pid == 0) { // 子进程执行 CGI 脚本

        char meth_env[255];
        char query_env[255];
        char length_env[255];

        // 相比于dup函数，dup2函数可以将一个文件描述符重定向至另一个文件描述符指向的文件, 返回结果只能表示是否执行成功
        //将子进程的输出由标准输出重定向到 cgi_ouput 的管道写端上
        dup2(cgi_output[1], 1);
        //将子进程的输出由标准输入重定向到 cgi_ouput 的管道读端上
        dup2(cgi_input[0], 0);

        //关闭 cgi_ouput 管道的读端与cgi_input 管道的写端
        close(cgi_input[0]);
        close(cgi_output[1]);

        //构造一个环境变量
        sprintf(meth_env, "REQUEST_METHOD=%s", method);
        //putenv()包含于<stdlib.h>中，参读《TLPI》P128
        //将这个环境变量加进子进程的运行环境中
        putenv(meth_env);


        //根据http 请求的不同方法，构造并存储不同的环境变量
        if (strcasecmp(method, "GET") == 0) {
            sprintf(query_env, "QUERY_STRING=%s", query_string);
            putenv(query_env);
        } else {   /* POST */
            sprintf(length_env, "CONTENT_LENGTH=%d", content_length);
            putenv(length_env);
        }

        //execl()包含于<unistd.h>中，参读《TLPI》P567
        //最后将子进程替换成另一个进程并执行 cgi 脚本
        execl(path, path, NULL);
        exit(0);


    } else { /* parent */

        int status;
        int i;
        char c;

        //父进程则关闭了 cgi_output管道的写端和 cgi_input 管道的读端
        close(cgi_output[1]);
        close(cgi_input[0]);

        //如果是 POST 方法的话就继续读 body 的内容，并写到 cgi_input 管道里让子进程去读
        if (strcasecmp(method, "POST") == 0) {
            for (i = 0; i < content_length; i++) {
                recv(http_fd, &c, 1, 0);
                write(cgi_input[1], &c, 1);
            }
        }

        //然后从 cgi_output 管道中读子进程的输出，并发送到客户端去
        while (read(cgi_output[0], &c, 1) > 0) {
            send(http_fd, &c, 1, 0);
        }


        //关闭管道
        close(cgi_output[0]);
        close(cgi_input[1]);
        //等待子进程的退出
        waitpid(pid, &status, 0);

    }


}

void cannot_execute(int http_fd) {
    char buf[1024];

    sprintf(buf, "HTTP/1.0 500 Internal Server Error\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "<P>Error prohibited CGI execution.\r\n");
    send(http_fd, buf, strlen(buf), 0);
}

void bad_request(int http_fd) {
    char buf[1024];

    sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
    send(http_fd, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(http_fd, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(http_fd, buf, sizeof(buf), 0);
    sprintf(buf, "<P>Your browser sent a bad request, ");
    send(http_fd, buf, sizeof(buf), 0);
    sprintf(buf, "such as a POST without a Content-Length.\r\n");
    send(http_fd, buf, sizeof(buf), 0);
}

void serve_file(int http_fd, char *path) {
    int chars_num = 1;
    char buf[1024];
    // 文件句柄
    FILE *resource = NULL;

    //确保 buf 里面有东西，能进入下面的 while 循环
    buf[0] = 'A';
    buf[1] = '\0';

    // 循环
    while ((chars_num > 0) && strcmp("\n", buf)) {
        chars_num = get_line(http_fd, buf, sizeof(buf));
    }

    //打开文件
    resource = fopen(path, "r");

    if (resource == NULL)
        not_found(http_fd);
    else {
        //打开成功后，将这个文件的基本信息封装成 response 的头部(header)并返回
        headers(http_fd, path);
        //接着把这个文件的内容读出来作为 response 的 body 发送到客户端
        cat(http_fd, resource);
    }

    // 关闭句柄
    fclose(resource);
}

void cat(int http_fd, FILE *file_path) {
    char buf[1024];
    // 读取文件
    fgets(buf, sizeof(buf), file_path);
    // 判断文件是否结束
    while (!feof(file_path)) {
        // 发送内容
        send(http_fd, buf, strlen(buf), 0);
        // 读取下一行
        fgets(buf, sizeof(buf), file_path);
//        printf("read file content line: %s\n", buf);
    }

}

/**
 *  输出 HTTP 数据头
 * @param http_fd
 * @param path
 */
void headers(int http_fd, char *path) {
    char buf[1024];
    (void) path; /* 可以使用文件名来确定文件类型 */

    strcpy(buf, "HTTP/1.0 200 OK\r\n");
    send(http_fd, buf, strlen(buf), 0);
    strcpy(buf, SERVER_STRING);
    send(http_fd, buf, strlen(buf), 0);
    strcpy(buf, "Content-Type: text/html\r\n");
    send(http_fd, buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(http_fd, buf, strlen(buf), 0);

}


int get_line(int http_fd, char *buf, int size) {
    int i = 0, n = 0;
    char c = '\0';

    // \r \n 回车换行的含义
    while ((i < size - 1) && c != '\n') {
        // 读取第一个字符放在 c 中
        n = recv(http_fd, &c, 1, 0);
        /* DEBUG printf("%02X\n", c); */
//        printf("%02X\n", c);
        // 接收内容成功， n > 0
        if (n > 0) {
            if (c == '\r') {
                n = recv(http_fd, &c, 1, MSG_PEEK);
                // 换行继续接收内容
                if ((n > 0) && (c == '\n')) {
                    recv(http_fd, &c, 1, 0);
                } else {
                    c = '\n';
                }
            }
            buf[i] = c;
            i++;
        }
    }
    buf[i] = '\0';

    return i;
}

void error_die(const char *message) {
    perror(message);
    exit(1);
}


/**********************************************************************/
/*                             501 方法不支持                           */
/**********************************************************************/
void unimplemented(int http_fd) {
    char buf[1024];

    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(http_fd, buf, strlen(buf), 0);
}


/**********************************************************************/
/*                             404 错误提示                             */
/**********************************************************************/
void not_found(int http_fd) {
    char buf[1024];

    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "your request because the resource specified\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "is unavailable or nonexistent.\r\n");
    send(http_fd, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(http_fd, buf, strlen(buf), 0);
}