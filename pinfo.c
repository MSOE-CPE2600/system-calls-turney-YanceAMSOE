/*
* Filename: pinfo.c
* Description: 
* Author: Aden Yance
* Date: 10/30/2025
* Section 111
* compile with a Makefile then ./PINFO
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int priority;
    int policy;

   
    if (argc == 2) {
        pid = atoi(argv[1]);
    } else {
        pid = getpid();
    }

    // Get process priority 
    errno = 0;  // Clear errno before calling
    priority = getpriority(PRIO_PROCESS, pid);
    if (errno != 0) {
        perror("Error retrieving priority");
        return 1;
    }

    // Get process scheduling policy 
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("Error retrieving scheduling policy");
        return 1;
    }

    // Print process information
    printf("PID: %d\n", pid);
    printf("Priority (nice value): %d\n", priority);

    printf("Scheduling Policy: ");
    switch (policy) {
        case SCHED_OTHER:
            printf("SCHED_OTHER (Normal)\n");
            break;
        case SCHED_FIFO:
            printf("SCHED_FIFO (Real-Time FIFO)\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR (Real-Time Round Robin)\n");
            break;
#ifdef SCHED_BATCH
        case SCHED_BATCH:
            printf("SCHED_BATCH (Batch Processing)\n");
            break;
#endif
#ifdef SCHED_IDLE
        case SCHED_IDLE:
            printf("SCHED_IDLE (Very Low Priority)\n");
            break;
#endif
        default:
            printf("Unknown Policy (%d)\n", policy);
    }

    return 0;
}