#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/ether.h>

#define RECV_LEN 1024*1024

int main(int argc, char *argv[])
{
    // socket
    int sockfd;
    if((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
    //if((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1)
    {
        perror("failed to create socket");
        exit(1);
    }
    printf("sockfd = %d\n", sockfd);

    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);

    char buff[RECV_LEN] = "";

    while(1)
    {
        ssize_t dataLen = recvfrom(sockfd, buff, RECV_LEN, 0, (struct sockaddr*)&clientaddr, &len);
        if (dataLen <= 0)
        {
            continue;
        }
        printf("data length: %ld\n", dataLen);
        printf("recv: %s\n", buff);
    }

    // close
    close(sockfd);
    return 0;
}