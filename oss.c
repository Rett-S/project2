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

  char* x = "-h"; //x and y are used later to compare two strings
  char* y = "-n";

  if (strcmp(argv[1], x) == 0) { //if -h is present, displays a help message only
    printf("-h test\n");
  } else if (strcmp(argv[1], y) == 0) {//if -h is not present, and -n is, the process continues as normal
    int n = atoi(argv[2]); //int n sotres how many processes to run, based on user input
    printf("Processes to launch: %d \n",n);
    int s = atoi(argv[4]); //int s stores how many processes are allowed to run at once, based on user input
    printf("Simultaneous processes: %d \n",s);
    int t = atoi(argv[6]); //int t stores how long processes are allowed to run
    printf("Time limit for each process: %d \n",t);
    int it = 0;
    it = atoi(argv[8]); //int it stores a number that will be used to keep track of when to launch each process
    printf("Interval between each process: %d \n",it);

    int totalLaunched = 0; //keeps track of total processes
    int currentProc = 0; //keeps track of active processes
    int childPid;
    while (totalLaunched < n) {
      if (currentProc < s) {
        childPid = forkProcess();
        currentProc++;
        if (childPid == 0) {
          char* args [] = {"./worker", argv[2]};
          execlp(args[0],args[1]);
        } else {
          totalLaunched++;
        }
      } else {
        for (int i=0;i<totalLaunched;i++) {
          currentProc--;
          break;
        }
      }
    }
  }

  return 0;
}

int forkProcess() {
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
  signal(SIGALRM, signal_handler);  // Turn on alarm handler
  alarm(60);  // set up alarm call
  int shmid = shmget(SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);

  if ( shmid == -1 ) {
    fprintf(stderr,"Parent: ... Error in shmget ...\n");
    exit (1);
  }

  int *pint = (int *)(shmat (shmid, (void*)0, 0 ) );
  //int *nint = (int *)(shmat (nanoid, (void*)0, 0) );
  int *nint = pint + 1;
  for (int i=0;i<10;i++) {
    *pint = i;
    //*systemclock->seconds = 1*i;
    for (int x=0;x<10;x++) {
      usleep(100000);
      *nint = 100000*x;
      //printf("Time: %d : %d\n",*pint,*nint);
    }
    //printf("Seconds: %d Nanoseconds: %d\n",*pint,*nint);

  }

  shmdt(pint);
  shmctl(shmid,IPC_RMID,NULL);

}

void worker() {

  int shmid = shmget(SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);

  if ( shmid == -1 ) {
    fprintf(stderr,"Child: ... Error in shmget ...\n");
    exit ( 1 );
  }
  int *cint = ( int * )( shmat ( shmid, 0, 0 ) );
  int *xint = cint + 1;

  for (int i = 0; i < 10; i++ ) {
    sleep ( 1 );
    printf("Time: %d : %d\n",*cint,*xint);
  }

  shmdt(cint);
}

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

