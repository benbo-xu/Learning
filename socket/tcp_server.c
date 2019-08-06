#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int server_sockfd;   // 服务器断套接字
    int client_sockfd;   // 客户端套接字
    int len;

    struct sockaddr_in my_addr;      // 服务器网络地址结构
    struct sockaddr_in remote_addr;  // 客户端网络地址结构

    int sin_size;
    char buf[BUFSIZ];

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;// 服务器IP地址--允许连接到所有本地地址
    my_addr.sin_port = htons(8000);      // 服务器端口号

    /* 创建服务器端套接字 */
    if( (server_sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0 )
    {
        perror("socket");
        return 1;
    }

    /* 将套接字绑定到服务器断的网络地址上 */
    if(bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
    {
        perror("blind error!");
        return 1;
    }

    /*监听连接--队列长度为5*/
    listen(server_sockfd,5);
    sin_size = sizeof(struct sockaddr_in);

    /*等待客户端连接请求到达*/
    if( (client_sockfd = accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size)) < 0)
    {
        perror("accept");
        return 1;
    }
    
    printf("accept client%s\n",inet_ntoa(remote_addr.sin_addr));
    len = send(client_sockfd, "Welcome to my server.\n",21,0);

    while((len=recv(client_sockfd,buf,BUFSIZ,0)) > 0)
    { 
        buf[len] = '\0';
        printf("%s\n",buf);
        if(send(client_sockfd,buf,len,0) < 0)
        {
            perror("write");
            return 1;
        }
    }
    close(client_sockfd);
    close(server_sockfd);
    return 0;

   
} 
