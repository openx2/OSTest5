/*
 * Filename:    myipc.h
 * copyright:   2016 chenxin
 * Function:    declaration of the function prototypes and global variables in IPC mechanism
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/sem.h> 
#include <sys/msg.h> 
#include <signal.h>

#define BUFSZ 256
#define SOFA 1          //沙发队列的通信类型
#define WAITINGROOM 2   //等待室队列的通信类型
#define RANDSIZE 10

int get_ipc_id(char *proc_file,key_t key);
char* set_shm(key_t shm_key,int shm_num,int shm_flag);
int set_msq(key_t msq_key,int msq_flag);
int set_sem(key_t sem_key,int sem_val,int sem_flag);

void ipc_init(void);

int down(int sem_id);
int up(int sem_id);

typedef union semuns {
    int val;
} Sem_uns;

typedef struct msgbuf {
    long mtype;
    int mid;
} Msg_buf;

//与沙发有关的全局变量
key_t sofa_key;
int sofa_flg;
int q_sofa;

//与等待室有关的全局变量
key_t wait_key;
int wait_flg;
int q_wait;

//账本信号量
key_t account_key;
int s_account;

//顾客信号量
key_t customer_key;
int s_customer;

int sem_val;
int sem_flg;
