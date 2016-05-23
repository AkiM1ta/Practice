/****************************
 * function:本程序通过使用信号灯，实现一种基于父子进程的简单进程同步
 * time:2016-5-22
 ******************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h>
#include<unistd.h>
int main()
{
    int pid,semid;
    int val;
    key_t semkey;
    if((semkey=ftok("./sem.c",1))<0)//将文件路径和项目ID 转换为system V IPC key
    {
        printf("ftok failed\n");
        exit(EXIT_FAILURE);
    }
    printf("ftol ok,semkey=%d\n",semkey);

    if((semid=semget(semkey,1,IPC_CREAT|0700))<0)//创建信号灯集，其中包含1个信号灯
    {
        printf("semget failed\n");
        exit(EXIT_FAILURE);
    }
    printf("semget ok,semid=%d\n",semid);

    if((semctl(semid,0,SETVAL,val))<0)//设置semid 对应的信号灯集中第一个信号灯的semval 为1
    {   
        printf("semctl set semval failed\n");
        exit(EXIT_FAILURE);
    }
    printf("semctl set semval ok\n");
    if((pid=fork())<0)
    {
        printf("fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if(pid>0)//父进程，先索取共享资源，而后释放
    {
        struct sembuf p_op_buf,v_op_buf;
        p_op_buf.sem_num=0;
        p_op_buf.sem_op=-1;
        if(semop(semid,&p_op_buf,1)<0)//以上三行向semid 代表的信号灯集的第一个信号灯申请一个资源，即使semval 减1
        {
            printf("semop failed\n");
            exit(EXIT_FAILURE);
        }
        printf("father get the semaphore\n");
        sleep(3);
        printf("father release the semaphore\n");
        v_op_buf.sem_num=0;
        v_op_buf.sem_op=1;
        v_op_buf.sem_flg=0;
        if(semop(semid,&v_op_buf,1)<0)//以上三行将释放一个资源给semid 代表的信号灯集的第一个信号
        {
            printf("semop release semaphore failed\n");
            exit(EXIT_FAILURE);
        }
    }
    else//子进程不断申请共享资源，申请到最后声明一下，然后释放
    {
        struct sembuf p_op_buf,v_op_buf;
        sleep(1);//等待父进程将唯一的资源占用
        printf("child wait for the semaphore\n");
        v_op_buf.sem_num=0;
        v_op_buf.sem_op=-1;
        //v_op_buf.sem_flg=0;//该标志位不需要清零，此处不清零将出现错误
       if(semop(semid,&p_op_buf,1)<0)//向semid 代表的信号灯集的第一个信号灯申请一个资源，申请不到就会阻塞，直到有了资源
       {
           printf("semop get semaphore failed\n");
          // exit(EXIT_FAILURE);
       }
       printf("child get the semaphore\n");
       if(semctl(semid,0,IPC_RMID,0)<0)
       {
           printf("semctl remove semaphore set failed\n");
           exit(EXIT_FAILURE);
       }
       
   }
}
