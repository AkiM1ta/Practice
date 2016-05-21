/***************************
 * function:use vfork() creat a childProcess and in fatherProcess and childProcess,print their ProcessID
 * time:2016-5-20
 ****************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int main(void)
{
    pid_t child;
    if((child=vfork())==-1)
    {
	printf("Fork Error:%s\n",strerror(errno));
	exit(1);
    }
    else
    {
	if(child==0)
	{
	    sleep(1);
	    printf("I am the child:%d\n",getpid());
	    exit(0);
	}
	else
	{
	    printf("I an the father:%d\n",getpid());
	    exit(0);
	}
    }
}
