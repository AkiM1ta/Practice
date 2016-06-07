/***************************
 * function:创建线程并在其中使用函数thread_cleanup_push()pthread_cleanup_pop()，验证这两个清理函数的效果
 * time:2016-5-23
 ***************************/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *clean(void *arg)
{
    printf("cleanup:%s\n",(char *)arg);
    return (void *)0;
}
void *thr_fn1(void *arg)
{
    printf("thread 1 start  \n"); 
    //将线程清理函数压入清除栈两次
    pthread_cleanup_push((void *)clean,"thread 1 first handler");
    pthread_cleanup_push((void *)clean,"thread 1 second handler");
    printf("thread 1 push complete \n");
    if(arg)
    {
        return((void *)1);//线程运行到此结束，后面的代码不会被运行，由于是return 退出，所以不会执行线程清理函数
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0); 
    return (void *)1;
}
void *thr_fn2(void *arg)
{
    printf("thread 2 start \n");
     //将线程清理函数压入清除栈两次
    pthread_cleanup_push((void *)clean,"thread 2 first handler");
    pthread_cleanup_push((void *)clean,"thread 2 second handler");
    printf("thread 2 push complete \n");
    if(arg)
    {
        pthread_exit((void *)2);//线程运行到此结束，后面的代码不会被运行，由于是pthread_exit 退出，所以会执行线程清理函数,后进先出
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0); 
    pthread_exit((void *)2);    
}

int main(void)
{
    int err;
    pthread_t tid1,tid2;
    void *tret;
    
    err=pthread_create(&tid1,NULL,thr_fn1,(void *)1);
    if(err!=0)
    {
        printf("error ...\n");
        return -1;
    } 
    err=pthread_create(&tid2,NULL,thr_fn2,(void *)1);
    if(err!=0)
    {
        printf("error ...\n");
        return -1;
    }    
    
    err=pthread_join(tid1,&tret);
    if(err!=0)
    {
        printf("error ...\n");
        return -1;
    }
    printf("thread 1 exit code %d \n",(int *)tret);
    err=pthread_join(tid2,&tret);
    if(err!=0)
    {
        printf("error ...\n");
        return -1;
    }  
    printf("thread 2 exit code %d \n",(int *)tret);
    return 1;
}
