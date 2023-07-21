#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define MESSAGE_BUF 1024

void error_handle(char* message);

int main(int argc, char* argv[])
{
	int sock;
	int message_len;
	struct sockaddr_in serv_addr;
	char message[MESSAGE_BUF];
	char receive[MESSAGE_BUF];

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)	{
		error_handle("socket create error");
	}

	printf("%d\n", sock);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handle("connect error");
	} 

	while (1) {
		printf("please enter message on hear:");
		fgets(message, MESSAGE_BUF, stdin);

		if (strcmp(message, "Q\n")==0 || strcmp(message, "q\n")==0) {
			break;
		}

		write(sock, message, strlen(message));

		message_len =read(sock, receive, MESSAGE_BUF - 1);
		receive[message_len-1] = 0;
		printf("Message from server: %s\n", receive);
	}

	close(sock);

	return 0;
}

void error_handle(char* message) 
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}