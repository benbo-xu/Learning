#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define PORT 8899
#define BUFFER_SIZE 1024

int main(int argc, char ** argv[])
{
 /*   if(argc != 2)
    {
        printf("usage: client IP\n");
        exit(0);
    }*/
     
    int sock_cli = socket(AF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if(connect(sock_cli,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(-1);
    }
    printf("connect server(IP %s).\n","127.0.0.1");

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    while(fgets(sendbuf,sizeof(sendbuf),stdin) != NULL)
    {
        send(sock_cli,sendbuf, strlen(sendbuf),0);
        if(strcmp(sendbuf,"exit\n") == 0)
        {
            printf("client exited.\n");
            break;
        }
        printf("client receive:\n");
        recv(sock_cli,recvbuf,sizeof(recvbuf),0);
        fputs(recvbuf,stdout);

        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));
    }
    close(sock_cli);
    return 0;

}

