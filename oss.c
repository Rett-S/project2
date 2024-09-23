//Rett Swyers - CS 4760

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include<signal.h>
#include"processTable.h"

void signal_handler(int sig) {
  // code to send kill signal to all children based on their PIDs in process table
   
  clean();
   
  exit(1);
}

void clean() {

    

}

int main(int argc, char** argv) {

   signal(SIGALRM, signal_handler);  // Turn on alarm handler
   alarm(60);  // set up alarm call


    return 0;
}
