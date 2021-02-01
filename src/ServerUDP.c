#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>



#define RECV_LEN 1024

int main(int argc, char *argv[])
{
    printf("%s", "Hello World !\n");

    // create socket
    int socketfd;
    if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Error: failed to create socket.");
        exit(1);
    }

    // bind ip, prot
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(30010);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.218.129");

    bind(socketfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    printf("%s, socketfd: %d\n", "bind socket success.", socketfd);
        
    // recv data
    printf("%s", "Start Receive Data...\n");
    char recvBuff[RECV_LEN]; // receive data buffer
    struct sockaddr_in clientaddr;
    socklen_t len;
    
     while (1)
     {
        memset(recvBuff, 0, RECV_LEN);
        len = sizeof(clientaddr);
        ssize_t count = recvfrom(socketfd, recvBuff, RECV_LEN, 0, (struct sockaddr *)&clientaddr, &len);
        if (count == -1)
        {
            printf("Error: receive data failed.");
            continue;
        }
         
        printf("clint: IP:%s, PORT:%d :: %s", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), recvBuff);
        printf("\n");
        // send to data
        char *buff = "Hello, I am Linux.";
        sendto(socketfd, buff, strlen(buff), 0, (struct sockaddr*)&clientaddr, len);
     }
    
    // close socket
    close(socketfd);

    
    return 0;
}