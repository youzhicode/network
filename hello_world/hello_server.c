#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include "helper.h"


int main(int argc, char* argv[])
{

    int serv_sock;
    int clnt_sock;

    // 定义一个服务端的监听地址
    struct sockaddr_in serv_addr;
    // 定义一个客户端的请求地址
    struct sockaddr_in clnt_addr;

    socklen_t clnt_addr_size;

    char message[] = "hello world";

    if (argc != 2) {
        printf("Usage: %s <port>", argv[0]);
        exit(1);
    }

    // 定义一个server socket
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handle("socket() error");
    }

    // 初始化serv_addr的内存
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET,
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 将sock与地址绑定
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handle("bind() error");
    }

    // 设置监听队列的长度
    if (listen(serv_sock, 5) == -1) {
        error_handle("listen() error");
    }

    // 开始监听
    clnt_addr_size = sizeof(clnt_addr);
    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size)) != -1
        if (clnt_sock == -1){
            error_handle("accept error");
            continue;
        }
        int fc = fork();
        if (fc == 0) {
            write(clnt_sock, message,  sizeof(message));
        }
    }

    return 0;
}
