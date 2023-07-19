#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFER_SIZE 100

int main(int argc, char* argv[])
{

    if (argc != 2) {
        printf("Usage %s <filename>\n", argv[0]);
        exit(0);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Fail to openfile\n");
        exit(0);
    }

    char buffer[BUFFER_SIZE];
    int res = 0;
    res = read(fd, buffer, sizeof(buffer));
    if (res == -1) {
        fprintf(stderr, "read file error");
    } else {
        printf("file content: %s\n", buffer);
    }

    close(fd);
    return 0;
}