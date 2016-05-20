/**********
 * function:This Program will apply and allocate the same shared_memory in sharedMemoryCommunication1.c,then loop write data in it until "end".
 * 2016-5-20
 **********/

#define TEXT_SZ 2048
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

struct shared_use_st
{
    int written_by_you;
    char some_text[TEXT_SZ];
};

int main(void)
{
    int running=1;
    void *shared_memory=(void *)0;
    struct shared_use_st *shared_stuff;
    char buffer[BUFSIZ];
    int shmid;
    /*Creat SharedMemory*/
    shmid=shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
    if(shmid==-1)
    {
        fprintf(stderr,"shmget failed\n");
        exit(EXIT_FAILURE);
    }
    /*Map SharedMemory*/
    shared_memory=shmat(shmid,(void *)0,0);
    if(shared_memory==(void *)-1)
    {
    fprintf(stderr,"shmat failed\n");
    exit(EXIT_FAILURE);   
    }
    printf("Memory attached at %X\n",(int)shared_memory);
    /*point the structure pointer to the shared_memory*/
    shared_stuff=(struct shared_use_st *)shared_memory;
    /*loop write data in shared_memory until "end"*/
    while(running)
    {
        while(shared_stuff->written_by_you==1)
        {
            sleep(1);//wait until readProcess finish then write
	    printf("wait fpr client...\n");
        }
	printf("Enter some text:");
	fgets(buffer,BUFSIZ,stdin);
	strncpy(shared_stuff->some_text,buffer,TEXT_SZ);
	shared_stuff->written_by_you=1;
	if(strncmp(buffer,"end",3)==0)
	{
	    running=0;
	}
    }
    /*delete shared_memory*/
    if(shmdt(shared_memory)==-1)
    {
        fprintf(stderr,"shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
