#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct msgbuf 
{
    long mtype;
    char mtext[255];
};

int main()
{
    int msg_id = msgget(123, IPC_CREAT | 0666);
    
    if(msg_id != -1)
    {
        struct msgbuf mybuf;
        mybuf.mtype = 1;
        strcpy(mybuf.mtext, "I'm send process.\n");

        if(msgsnd(msg_id,&mybuf,sizeof(mybuf.mtext), 0))
            printf("success\n");
        else
            perror("msgsnd");
    }
    else
    {
        perror("msgget");
    }
    return 0;
}
