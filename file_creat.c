/***************
 * function:与execl.c配合执行,通过creat创建一个通过命令行传入名称的可读写文件
 * time:2016-5-22
 ************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

void creat_file(char *filename)
{
    //创建文件具有可读可写属性
    if(creat(filename,0666)<0)
    {
        printf("creat file %s failure!\n",filename);
        exit(EXIT_FAILURE);
    } 
    else 
    {
        printf("creat file $s success!\n",filename);
    }
}

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("you haven't input the filename,please try again!\n");
        exit(EXIT_FAILURE);
    }
    creat_file(argv[1]);
    exit(EXIT_SUCCESS);
}
