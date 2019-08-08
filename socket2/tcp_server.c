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
#define QUEUE_SIZE 10
#define BUFFER_SIZE 1024

void str_echo(int sockfd)
{
    char buffer[BUFFER_SIZE];
    int len = 0;

    pid_t pid = getpid();

    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        len = recv(sockfd, buffer, sizeof(buffer), 0);
        
        if(strcmp(buffer,"exit\n") == 0)
        { 
            printf("child process: %d exited.\n",pid);
            break;
        }     
        printf("pid: %d receive:\n",pid);
        fputs(buffer,stdout);
        send(sockfd,buffer,len,0);
    }
    close(sockfd);
}


int main(int argc, char **argv[])
{
    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    int count_process = 0;     

    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_sockaddr.sin_port = htons(PORT);

    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr)) == -1)
    {
        perror("bind");
        exit(-1);
    }
    printf("bind success.\n");

    if(listen(server_sockfd,QUEUE_SIZE) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("listen success.\n");

    while(1)
    {    
        if( count_process <= 50)
        {
            struct sockaddr_in client_addr;
            socklen_t length = sizeof(client_addr);
            int conn = accept(server_sockfd,(struct sockaddr*)&client_addr,&length);
            if(conn < 0)
            {
                perror("connect");
                exit(1);
            }
            printf("New client accepted.\n");

            pid_t childid;
            if(childid = fork() == 0)
            {
                count_process += 1;
                printf("child process: %d creates.\n",getpid());
                close(server_sockfd);
                str_echo(conn);
                exit(0);
            }
        }
    }

    printf("closed.\n");
    close(server_sockfd);
    return 0;

}
