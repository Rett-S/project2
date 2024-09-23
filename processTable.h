#ifndef PROCESSTABLE_H
#define PROCESSTABLE_H
#include <sys/types.h>

struct PCB {
    int occupied; // either true or false
    pid_t pid; // process id of this child
    int startSeconds; // time when it was forked
    int startNano; // time when it was forked
};
struct PCB processTable[20];

#endif
