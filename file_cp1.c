/**************
 * function:该程序通过从待复制的文件中逐步读出数据到缓冲区,再把缓冲区的数据逐个写入到新创建的文件中,完成对原文件的复制工作.
 * time:2016-5-21
 ***************/
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#define BUFFER_SIZE 1024

int main(int argc,char **argv)
{
    FILE *from_fd,*to_fd;
    long file_len=0;
    char buffer[BUFFER_SIZE];
    char *ptr;
    //判断入参
    if(argc!=3)
    {
        printf("Usage:%s fromfile to file\n",argv[0]);
        exit(1);
    }
    //打开源文件
    if((from_fd=fopen(argv[1],"rb"))==NULL)
    {
        printf("Open %s Error\n",argv[1]);
        exit(1);
    }
    //创建目的文件
    if((to_fd=fopen(argv[2],"wb"))==NULL)
    {
        
        printf("Open %s Error\n",argv[2]);
        exit(1);
    }
    //测得文件大小
    fseek(from_fd,0L,SEEK_END);
    file_len=ftell(from_fd);
    fseek(from_fd,0L,SEEK_SET);
    printf("from file size is %d\n",file_len);
    //进行文件复制
    while(!feof(from_fd))
    {
        fread(buffer,BUFFER_SIZE,1,from_fd);
        if(BUFFER_SIZE>=file_len)
        {
            fwrite(buffer,file_len,1,to_fd);
        }
        else
        {
            fwrite(buffer,BUFFER_SIZE,1,to_fd);
            file_len=file_len-BUFFER_SIZE;
        }
        bzero(buffer,BUFFER_SIZE);
    }
    fclose(from_fd);
    fclose(to_fd);
    exit(0);
}
