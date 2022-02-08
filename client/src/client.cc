#include <iostream>
#include <string>
#include "../include/head.h"

using namespace std;

int main(int argc, char** argv)
{
    int ret;
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socket_fd, -1, "socket");
    
    // struct sockaddr_in cli_addr;
    struct sockaddr_in cli_addr;
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(atoi(argv[2]));
    cli_addr.sin_addr.s_addr = inet_addr(argv[1]);    

    ret = connect(socket_fd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));    
    if(-1 == ret){
        exit(0);
    }
    char first[100];
    int len;
    memset(first, 0, sizeof(first));
    recv(socket_fd, &len, 4, 0);
    printf("len:%d\n", len);
    recv(socket_fd, first, len, 0);
    printf("%s\n", first);
    fflush(stdout);

    char str[100];
    while(1){
        memset(str, 0, sizeof(str));
        setbuf(stdin, NULL);
        scanf("%s", str);
        int cur_len = strlen(str);
        send(socket_fd, &cur_len, 4, 0);
        send(socket_fd, str, strlen(str), 0);
        
        recv(socket_fd, &len, sizeof(int), 0);
        memset(first, 0, sizeof(first));
        recv(socket_fd, first, len, 0);
        printf("%d,%s\n", strlen(first), first);
        fflush(stdout);
    }    
}

