#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    // socket
    int socketfd;
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("failed to create socket.\n");
        exit(1);
    }
    printf("socket = %d\n", socketfd);

    // connect
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("192.168.218.129");
    serveraddr.sin_port = htons(atoi("30010"));
    socklen_t addrLen = sizeof(serveraddr);
    if(connect(socketfd, (struct sockaddr *)&serveraddr, addrLen) == -1)
    {
        perror("failed to connect server.\n");
        exit(1);
    }


    while (1)
    {
        // recv
        char text[128] = "";
        printf("wait recv data ...\n");
        if(recv(socketfd, text, 128, 0) == -1)
        {
            perror("failed to recv data.\n");
            exit(1);
        }
        printf("recv data: %s\n", text);

         // send
        char buff[128] = "";

        fgets(buff, 128, stdin);
        buff[strlen(buff) - 1] = '\0';
        if(send(socketfd, buff, strlen(buff), 0) == -1)
        {
            perror("failed to send data.\n");
            exit(1);
        }
    }
    

   

    
    // close
    close(socketfd);

    return 0;
}