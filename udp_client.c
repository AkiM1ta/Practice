/*********************************************
 * function:根据套接字建立UDP 通信的过程，创建客户端程序，通过服务端的地址向其发送指定字符串
 * time:2016-5-27
 ***********************************************/
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>

#define SERVER_PORT 8888
#define MAX_BUF_SIZE 1024

void udpc_requ(int sockfd,const struct sockaddr_in *addr,int len)
{
    char buffer[MAX_BUF_SIZE];
    int n;
    while(1)
    {
        printf("Please input char:\n");
        fgets(buffer,MAX_BUF_SIZE,stdin);
        sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)addr,len);
        bzero(buffer,MAX_BUF_SIZE);
    } 
}

int main(int argc,char **argv)
{
    int sockfd;
    struct sockaddr_in addr;
    if(argc!=2)
    {
        fprintf(stderr,"Usage:%s server_ip\n",argv[0]);
        exit(1);
    }    
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)
    {
        fprintf(stderr,"Socket Error:%s\n",strerror(errno));
        exit(1);
    }
    bzero(&addr,sizeof(struct sockaddr_in));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(SERVER_PORT);
    if(inet_aton(argv[1],&addr.sin_addr)<0)
    {
        fprintf(stderr,"IP error:%s\n",strerror(errno));
        exit(1);
    }
    udpc_requ(sockfd,&addr,sizeof(struct sockaddr_in));
    close(sockfd);
}
