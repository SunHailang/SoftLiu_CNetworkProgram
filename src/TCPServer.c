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

    // bind
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("192.168.218.129");
    serveraddr.sin_port = htons(atoi("30010"));
    socklen_t addrLen = sizeof(serveraddr);
    if(bind(socketfd, (struct sockaddr *)&serveraddr, addrLen) == -1)
    {
        perror("failed to bind.\n");
        close(socketfd);
        exit(1);
    }

    // listen
    if(listen(socketfd, 5) == -1)
    {
        perror("failed to listen.");
        close(socketfd);
        exit(1);
    }

    // accept
    int acceptfd;
    struct sockaddr_in clientaddr;

    if((acceptfd = accept(socketfd, (struct sockaddr *)&clientaddr, &addrLen)) == -1)
    {
        perror("failed to accept.");
        exit(1);
    }
    printf("ip::%s, port::%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

    while (1)
    {
        // recv
        char text[128] = "";
        if(recv(acceptfd, text, 128, 0) == -1)
        {
            perror("failed to recv data.\n");
            exit(1);
        }
        printf("recv data: %s\n", text);

        // send
        strcat(text, "*-*"); 
        if(send(acceptfd, text, strlen(text), 0) == -1)
        {
            perror("failed to send data.\n");
            exit(1);
        }
    }

   
    // close
    close(acceptfd);
    
    close(socketfd);

    return 0;
}