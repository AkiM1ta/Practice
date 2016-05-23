/***************
 * function:创建一个进程,并在其中创建一个有名管道,并向其中写入数据
 * time:2016-5-22
 ************/
#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#define FIFO_SEVER "/tmp/fifo"

int main(int argc,char** argv)
{
    int fd;
    char w_buf[100];
    int nwrite;
    //创建有名管道
    if((mkfifo(FIFO_SEVER,O_CREAT|O_EXCL|O_RDWR)<0)&&(errno!=EEXIST))
    {
        printf("cannot creat fifosever\n");
    }
    //打开管道
    fd=open(FIFO_SEVER,O_WRONLY|O_NONBLOCK,0);
    if(fd==-1)
    {
        perror("open");
        exit(1);
    }
    //入参检测
    if(argc==1)
    {
        printf("Please send something\n");
        exit(-1);
    }
    strcpy(w_buf,argv[1]);
    //向管道写入数据
    if((nwrite=write(fd,w_buf,100))==-1)
    {
        if(errno==EAGAIN)
            printf("The FIFO has not been read yet.Please try later\n");
    }
    else
    {
        printf("write %s to the FIFO\n",w_buf);
    }
    close(fd);
    return 0;
}

