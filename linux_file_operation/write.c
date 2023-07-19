#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char* argv[]) 
{
    if (argc != 3) {
        printf("Usage %s <fileName> <content>\n", argv[0]);   
    }
    // int open(const char *file, int flag)
    int fp = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY);
    if (fp == -1) {
        fprintf(stderr,"fail to open file");
        exit(1);
    }
    if (write(fp, argv[2], strlen(argv[2])) == -1) {
        fprintf(stderr, "Fail to write file\n");
    }
    // 关闭文件,可用于普通文件和套接字
    close(fp);

    return 0;
}