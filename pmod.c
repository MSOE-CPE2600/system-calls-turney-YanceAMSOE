/*
* Filename: pmod.c
* Description: 
* Author: Aden Yance
* Section 111
* Date: 10/30/2025
* compile with a Makefile then ./PMOD
*/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(void) {
    //Change process priority 
    int new_nice = nice(10); 
    if (new_nice == -1 && errno != 0) {
        perror("nice() failed");
    } else {
        printf("Priority reduced successfully.\n");
        printf("New nice value: %d\n", new_nice);
    }

    //Sleep for 1,837,272,638 nanoseconds
    struct timespec sleep_time;
    struct timespec remainder;

    // 1,837,272,638 ns = 1 second + 837,272,638 ns
    sleep_time.tv_sec  = 1;
    sleep_time.tv_nsec = 837272638;

    printf("Sleeping for 1,837,272,638 nanoseconds\n");

    if (nanosleep(&sleep_time, &remainder) == -1) {
        perror("nanosleep failed");
    } else {
        printf("Sleep completed successfully.\n");
    }

    // Exit message 
    printf("Goodbye! Process finished successfully.\n");

    return 0;
}