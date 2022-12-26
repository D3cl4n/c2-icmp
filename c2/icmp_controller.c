#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <string.h>


#define SOCKET_CREATE_ERROR 0x1

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



    return 0;
}

