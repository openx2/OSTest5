/*
 * Filename:    barber.c
 * copyright:   2016 chenxin
 * Function:    set up three subprocess and simulate barber
 */
#include "myipc.h"

typedef void(*sighandler_t) (int);
void sigcat()
{
    semctl(s_account,0,IPC_RMID);
    semctl(s_customer,0,IPC_RMID);
    
    struct msqid_ds msg_ds;
    msgctl(q_sofa,IPC_RMID,&msg_ds);
    msgctl(q_wait,IPC_RMID,&msg_ds);

    exit(0);
}

int main(int argc,char* argv[])
{
    int i,*status;
    int rate;
    int pid;
    Msg_buf msg_arg;

    srand(time(0));
    signal(SIGINT,(sighandler_t)sigcat);
    ipc_init();

    for(i = 0; i < 3; i++) {
        if((pid = fork()) == 0) {
            pid = getpid();
            while(1) {
                printf("%d号理发师睡眠\n",pid);
                msgrcv(q_sofa,&msg_arg,sizeof(msg_arg),SOFA,0); //阻塞式接受沙发队列的消息

                //让一个沙发上的顾客来理发
                up(s_customer);
                printf("%d号理发师为%d号顾客理发\n",pid,msg_arg.mid);
                rate = rand()%RANDSIZE;
                sleep(rate);

                //收费过程，同时只能有一个理发师在收费
                down(s_account);
                printf("%d号理发师收取%d号顾客交费\n",pid,msg_arg.mid);
                up(s_account);
            }
        }
    }
    wait(status);
    return EXIT_SUCCESS;
}
