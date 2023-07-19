#include "helper.h"


void error_handle(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}