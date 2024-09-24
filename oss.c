//Rett Swyers - CS 4760

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include<signal.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void oss();
void worker();
void signal_handler();
void clean();

#define SHMKEY 44197
#define BUFF_SZ sizeof (int)

int main(int argc, char** argv) {

  switch (fork()) {
    case -1:
        fprintf(stderr,"Failed to fork\n");
        return ( 1 );
    case 0:
        worker();
        break;
    default:
        oss();
        break;
    }

    return 0;
}

void oss() {
  
  int i;
  signal(SIGALRM, signal_handler);  // Turn on alarm handler
  alarm(60);  // set up alarm call
  int shmid = shmget(SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);

  if ( shmid == -1 ) {
    fprintf(stderr,"Parent: ... Error in shmget ...\n");
    exit (1);
  }

  int * pint = ( int * )( shmat ( shmid, 0, 0 ) );

  for ( i = 0; i < 10; i++ ) {
    sleep ( 2 );
    *pint = 10 * i ;             /* Write into the shared area. */
    printf("Parent: Written Val.: = %d\n",*pint);

  }

  shmdt(pint);

  shmctl(shmid,IPC_RMID,NULL);

}

void worker() {

  int i;
  int shmid = shmget(SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);

  if ( shmid == -1 ) {
    fprintf(stderr,"Child: ... Error in shmget ...\n");
    exit ( 1 );
  }
  int * cint = ( int * )( shmat ( shmid, 0, 0 ) );

  for ( i = 0; i < 10; i++ ) {
    sleep ( 1 );
    printf("Child: Read Val. = %d\n",*cint);
  }

  shmdt(cint);
}

struct systemclock {
    int seconds;
    int nanoseconds;
};

struct PCB {
    int occupied; // either true or false
    pid_t pid; // process id of this child
    int startSeconds; // time when it was forked
    int startNano; // time when it was forked
};
struct PCB processTable[20];

void signal_handler(int sig) {
  // code to send kill signal to all children based on their PIDs in process table
   
  free(processTable);
  
  exit(1);
}

