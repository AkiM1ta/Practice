/***************
 * function:在主函数中创建两个进程，在父进程中等待子进程结束后才结束父进程
 * time:2016-5-22
 ************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<string.h>

int main(void)
{
    pid_t child;
    if((child=fork())==-1)
    {
        printf("Fork Error:%s\n",strerror(errno));
        exit(1);
    }
    else
    {
        if(child==0)
        {
            printf("the child is run\n");;
            sleep(1);
            printf("I an the child:%d\n",getpid());
            exit(0);
        }
        else
        {
            wait(NULL);
            printf("the father process is run\n");
            printf("I an the father:%d\n",getpid());
            return 0;
        }
    }
}
