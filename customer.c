/*
 * Filename:    barber.c
 * copyright:   2016 chenxin
 * Function:    set up three subprocess and simulate customer
 */
#include "myipc.h"

int get_queue_num(int msq)
{
    struct msqid_ds msg_info;
    if(msgctl(msq,IPC_STAT,&msg_info) == -1)
        return -1;
    else
        return msg_info.msg_qnum;
}

int main(int argc,char* argv[])
{
    int count = 0;
    int sofa_num,wait_num;
    int rate,*status;
    Msg_buf msg_arg;

    ipc_init();

    wait_flg = IPC_NOWAIT;
    while(1) {
        sofa_num = get_queue_num(q_sofa);
        if(sofa_num<4) {
            if(msgrcv(q_wait,&msg_arg,sizeof(msg_arg),WAITINGROOM,wait_flg) >= 0){
                printf("%d号顾客从等候室坐入沙发\n",msg_arg.mid);
                msg_arg.mtype = SOFA;
                msgsnd(q_sofa,&msg_arg,sizeof(msg_arg),0);
            }
            else {
                count++;
                printf("%d号顾客坐入沙发\n",count);
                msg_arg.mtype = SOFA;
                msg_arg.mid = count;
                msgsnd(q_sofa,&msg_arg,sizeof(msg_arg),0);
            }
        }
        else {
            wait_num = get_queue_num(q_wait);
            if(wait_num<13) {
                count++;
                printf("沙发坐满  %d号顾客在等候室等候\n",count);
                msg_arg.mtype = WAITINGROOM;
                msg_arg.mid = count;
                msgsnd(q_wait,&msg_arg,sizeof(msg_arg),0);
            }
            else {
                printf("等候室满，%d号顾客没有进入理发店\n",count);
                down(s_customer);
            }
        }
        rate = rand()%RANDSIZE;
        sleep(rate);
    }
    wait(status);
    return EXIT_SUCCESS;
}
