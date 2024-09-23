//Rett Swyers - CS 4760

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include<signal.h>

void oss();
void worker();
void signal_handler();
void clean();

const int sharedMemoryKey = 44197;

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
  signal(SIGALRM, signal_handler);  // Turn on alarm handler
  alarm(60);  // set up alarm call

}

void worker() {

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
   
  clean();
   
  exit(1);
}

