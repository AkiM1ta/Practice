/**************
 * function:该程序通过从待复制的文件中逐步读出数据到缓冲区,再把缓冲区的数据逐个写入到新创建的文件中,完成对原文件的复制工作.
 * time:2016-5-21
 ***************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#define BUFFER_SIZE 1024

int main(int argc,char **argv)
{
    int from_fd,to_fd;
    long file_len=0;
    int ret=1;
    char buffer[BUFFER_SIZE];
    char *ptr;
    //判断入参
    if(argc!=3)
    {
        printf("Usage:%s fromfile to file\n",argv[0]);
        exit(1);
    }
    //打开源文件
    if((from_fd=open(argv[1],O_RDONLY|O_CREAT))==-1)
    {
        printf("Open %s Error\n",argv[1]);
        exit(1);
    }
    //创建目的文件
    if((to_fd=open(argv[2],O_WRONLY|O_CREAT))==-1)
    {
        
        printf("Open %s Error\n",argv[2]);
        exit(1);
    }
    //测得文件大小
    file_len=lseek(from_fd,0L,SEEK_END);
    lseek(from_fd,0L,SEEK_SET);
    printf("from file size is %d\n",file_len);
    //进行文件复制
    while(ret)
    {
        ret=read(from_fd,buffer,BUFFER_SIZE);
        if(ret==-1)
        {
            printf("read Error\n");
            exit(1);
        }
        write(to_fd,buffer,ret);
        file_len-=ret;
        bzero(buffer,BUFFER_SIZE);
    }
    printf("there are %d byte(s) data left without copy\n",file_len);
    close(from_fd);
    close(to_fd);
    exit(0);
}
