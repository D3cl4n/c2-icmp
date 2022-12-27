#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <string.h>


#define SOCKET_CREATE_ERROR 0x1
#define TEST_BOT "192.168.239.128"

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct icmphdr icmp_hdr;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
	exit(SOCKET_CREATE_ERROR);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&icmp_hdr, 0, sizeof(icmp_hdr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(TEST_BOT);
    
    icmp_hdr.type = ICMP_ECHO;
    icmp_hdr.code = 0;
    icmp_hdr.un.echo.id = 0;
    icmp_hdr.un.echo.sequence = 0;
    icmp_hdr.un.frag.__unused = cpu_to_be16(1234); 

    sendto(sockfd, &icmp_hdr, sizeof(icmp_hdr), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    close(sockfd);

    return 0;
}

