/****************
 * function:以字符串方式显示本地时间
 * time:2016-5-22
 ***************/
#include<time.h>
#include<stdio.h>

int main(void)
{
    struct tm *ptr;
    time_t lt;
    lt=time(NULL);
    ptr=localtime(&lt);
    printf("%s\n",asctime(ptr));
    printf("%s\n",ctime(&lt));
    return 0;
}
