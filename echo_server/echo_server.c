#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#define MESSAGE_BUF 100


// 一个简单的回声服务器，但是却可以搞清楚TCP 的原理

void error_handle(char* message);

int main(int argc, char* argv[])
{

	int serv_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	int message_len;
	char message[MESSAGE_BUF];

	if(argc != 2) {
		printf("Usage %s <port>\n", argv[0]);
		exit(1);	
	} 
	// 这是一个服务器的套接字，将需要连接的客户端，按照顺序排队
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1) 
		error_handle("create socket error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		error_handle("bind socket error");
	}

	if (listen(serv_sock, 5) == -1) {
		error_handle("listen socket error");
	}

	int addr_len = sizeof(client_addr);
	for (int i=0; i<5; i++) {
		// 将客户端的连接从队列中取出，并且创建一个
		// 真正用于连接客户端的套接字
		client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &addr_len);
		if (client_sock == -1) {
			error_handle("accept error");
		}
		puts("A client connect success");
		while (message_len = read(client_sock, message, MESSAGE_BUF)) {
			if (message_len == -1) {
				error_handle("read error");
			}
			message[message_len - 1] = 0;
			printf("message: %s\n", message);
			write(client_sock, message, message_len);
		}
		close(client_sock);
	}
	close(serv_sock);
	return 0;
}


void error_handle(char* message) 
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
