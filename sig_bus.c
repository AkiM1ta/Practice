/****************************
 * function:在进程中为SIGBUS 注册处理函数，并向该进程发送SIGBUS 信号来触发已注册的处理函数
 * time:2016-5-22
 *********************/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void my_func(int sign_no)
{
    if(sign_no==SIGBUS)
    {
        printf("I have get SIGBUS\n");
    }
}

int main()
{
    printf("Waiting for signal SIGBUS\n");
    //注册信号函数
    signal(SIGBUS,my_func);
    pause();
    exit(0);
}
