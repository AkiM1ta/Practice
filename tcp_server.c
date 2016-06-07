/*********************************
 * function:根据套接字建立TCP 连接的过程，创建服务端程序，并在服务端等待接受客户端的数据，并打印到终端上
 * time:2016-5-23
 **********************************/
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define portnumber 3333

int main(int argc,char *argv[])
{
    int sockfd,new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sin_size;
    int nbytes;
    char buffer[1024];
    //服务器端开始建立sockfd 描述符
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)//AF_INET:IPv4;SOCK_STREAM:TCP
    {
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
        exit(1);
    }    
    //服务器端填充sockaddr 结构
    bzero(&server_addr,sizeof(struct sockaddr_in));//初始化，置0
    server_addr.sin_family=AF_INET;//Internet
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);//（将本机上的long 数据转化为网络上的 long 数据）服务器程序能运行在任何IP 主机上
    //INADDR_ANY表示主机可以是任意IP 地址，即服务器程序可以绑定到所有的IP 上
    //server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");
    //用于绑定到一个固定IP,inet_addr 用于把数字加格式的IP 转化为整型IP
    server_addr.sin_port=htons(portnumber);
    //(将本机器上的short 数据转化为网络上的short 数据) 端口号
    //绑定sockfd 描述符到IP 地址
    if((bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)))==-1)
    {
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        exit(1);
    }
    //设置允许连接的最大客户端数
    if((listen(sockfd,5))==-1)
    {
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
        exit(1);
    }
    while(1)
    {
        //服务器阻塞，直到客户程序建立连接
        sin_size=sizeof(struct sockaddr_in);
        if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
        {
            fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
            exit(1);
        }
        fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));//将网络地址转换成字符串
        if((nbytes=read(new_fd,buffer,1024))==-1)
        {
            fprintf(stderr,"Read Error:%s\n",strerror(errno));
            exit(1);
        }
        buffer[nbytes]='\0';
        printf("Server received %s\n",buffer);
        //这个通信已结束
        close(new_fd);
        //循环下一个
    }
    //结束通信
    close(sockfd);
    exit(0);
}

