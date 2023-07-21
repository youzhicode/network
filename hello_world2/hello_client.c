#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/socket.h>
#include "helper.h"


int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;

    char message[30];
    int str_len;


    if (argc != 3) {
        char message[50];
        sprintf(message, "Uage %s <ip> <port>\n", argv[0]);
        error_handle(message);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        error_handle("socket error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handle("connect error");
    }

    int read_len = 0;
    int idx = 0;

    while (read_len = read(sock, &message[idx++], 1)) {
        if (read_len == -1) {
            error_handle("read error");
        }
        str_len += read_len;
    }

    printf("Message from server %s\n", message);
    return 0; 
}