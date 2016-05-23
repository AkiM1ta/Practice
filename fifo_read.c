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
#define FIFO "/tmp/fifo"

int main(int argc,char** argv)
{
    int fd;
    char buf_r[100];
    int nread;
    printf("Preparing for reading bytes...\n");
    memset(buf_r,0,sizeof(buf_r));
    //打开管道
    fd=open(FIFO,O_RDONLY|O_NONBLOCK,0);
    if(fd==-1)
    {
        perror("open");
        exit(1);
    }
    while(1)
    {
        memset(buf_r,0,sizeof(buf_r));
        if((nread=read(fd,buf_r,100))==-1)
        {
            if(errno==EAGAIN)
                printf("no data yet\n");
        }
        printf("read %s from FIFO\n",buf_r);
        sleep(1);
    }
    close(fd);
    pause();
    unlink(FIFO);
}
