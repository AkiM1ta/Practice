/****************************
 * function:本程序创建或打开一个消息队列，并从消息队列中读出消息，直至"end"
 * time:2016-5-22
 ******************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

struct my_msg_st
{
    long int my_msg_type;
    char some_text[BUFSIZ];
};

int main(void)
{
    int running=1;
    int msgid;
    struct my_msg_st some_data;
    long int msg_to_receive=0;
    //创建消息队列
    msgid=msgget((key_t)1234,0666|IPC_CREAT);
    if(msgid==-1)
    {
        fprintf(stderr,"msgget failed with error:%d\n",errno);
        exit(EXIT_FAILURE);
    }
    //循环地向消息队列中添加消息
    while(running)
    {
        //读取消息
        if(msgrcv(msgid,(void *)&some_data,BUFSIZ,msg_to_receive,0)==-1)
        {
            fprintf(stderr,"msgrcv failed with error:%d\n",errno);
            exit(EXIT_FAILURE);
        }
        printf("You wrote:%s",some_data.some_text);
        //接受到消息end 时结束
        if(strncmp(some_data.some_text,"end",3)==0)
        {
            running=0;
        }
    } 
    //从系统内核中移走消息队列
    if(msgctl(msgid,IPC_RMID,0)==-1)
    {
        fprintf(stderr,"msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
