//Rett Swyers - CS 4760

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv) {

    int s = atoi(argv[1]); //this is an integer to store the amount of seconds
    int n = atoi(argv[2]); //this is an integer to store the amount of nanoseconds
    


    printf("WORKER PID:%d PPID:%d SysClockS: %d SysClockNano: %d TermTimeS: %d TermTimeNano: %d - %d have passed since starting \n", getpid(),getppid());

    return EXIT_SUCCESS;
}
