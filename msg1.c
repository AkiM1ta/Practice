/****************************
 * function:本程序创建或打开一个消息队列，并从消息队列中写入消息，直至"end"
 * time:2016-5-22
 ******************************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX_TEXT 512

struct my_msg_st
{
    long int my_msg_type;
    char sometext[MAX_TEXT];
};

int main(void)
{
    int running=1;
    struct my_msg_st somedata;
    int msgid;
    char buffer[BUFSIZ];
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
        printf("Enter some text:");
        fgets(buffer,BUFSIZ,stdin);
        somedata.my_msg_type=1;
        strcpy(somedata.sometext,buffer);
        //添加消息
        if(msgsnd(msgid,(void *)&somedata,MAX_TEXT,0)==-1)
        {
            fprintf(stderr,"msgsed failed\n");
            exit(EXIT_FAILURE);
        }
        //用户输入end 时结束循环
        if(strncmp(buffer,"end",3)==0)
        {
            running=0;    
        }
    }
    exit(EXIT_SUCCESS);
}
