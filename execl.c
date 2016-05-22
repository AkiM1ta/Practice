/******************** 
 * function:直接在主函数中调用execl函数执行file_creat创建文件
 * time:2016-5-22
 **********************/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int  main(int argc,char *argv[])
{
    if(argc<2)
    {
        perror("you haven't input the filename,please try again!\n");
        exit(EXIT_FAILURE);
    }
    //调用execl函数，用可执行程序file_creat替换本进程
    if(execl("./file_creat","file_creat",argv[1],NULL)<0)
        perror("execl error!");
}
