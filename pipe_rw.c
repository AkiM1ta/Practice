/***************
 * function:在父进程中通过无名管道的写端写入数据，通过子进程从管道读出
 * time:2016-5-22
 ************/
#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    int pipe_fd[2];
    pid_t pid;
    char buf_r[100];
    char* p_wbuf;
    int r_num;
    memset(buf_r,0,sizeof(buf_r));
    //创建管道
    if(pipe(pipe_fd)<0)
    {
        printf("pipe creat error\n");
        return -1;
    }
    //创建子进程
    if((pid=fork())==0)
    {
        printf("\n");
        close(pipe_fd[1]);//子进程先关闭管道的写端
        sleep(2);//让父进程先写子进程才有内容读
        if((r_num=read(pipe_fd[0],buf_r,100))>0)
        {
            printf("%d numbers read from the pipe is %s\n",r_num,buf_r);
        }
        close(pipe_fd[0]);
        exit(0);
    }
    else if(pid>0)
    {
        close(pipe_fd[0]);//父进程先关闭了管道的读端 
        if(write(pipe_fd[1],"Hello",5)!=-1)
            printf("parent write1 Hello!\n");
        if(write(pipe_fd[1],"Pipe",5)!=-1)
            printf("parent write2 Pipe!\n");
        close(pipe_fd[1]);
        waitpid(pid,NULL,0);
        exit(0);
    }
    return 0;
}
