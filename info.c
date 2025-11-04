/*
* Filename: info.c
* Description: Prints the current time, system information, CPU count, and memory info
* Author: Aden Yance
* Date: 11/3/2025
* compile with a Makefile then ./info
*/

#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main(void) {
    struct timespec ts;
    struct utsname uname_info;   
    struct sysinfo mem_info;     

    // Current time
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("Current time in nanoseconds: %ld\n", ts.tv_nsec);

    // System / OS information
    if (uname(&uname_info) == 0) {
        printf("System Information:\n");
        printf("System Network Name: %s\n", uname_info.nodename);
        printf("Operating System: %s\n", uname_info.sysname);
        printf("Release: %s\n", uname_info.release);
        printf("Version: %s\n", uname_info.version);
        printf("Hardware: %s\n", uname_info.machine);
    }

    // CPU count
    long cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    printf("CPU Count: %ld\n", cpu_count);

    // Memory info (from sysinfo function)
    if (sysinfo(&mem_info) == 0) {
        printf("Total Memory: %lu bytes\n", mem_info.totalram);
        printf("Free Memory: %lu bytes\n", mem_info.freeram);
    }

    return 0;
}
/* Research of functions

clock_gettime(clockid_t, struct timespec*): Queries kernel time with nanosecond resolution.
  - CLOCK_REALTIME returns wall clock time since the Unix epoch.
  - struct timespec has fields tv_sec (seconds) and tv_nsec (nanoseconds).
  - To get total nanoseconds: seconds*1e9 + nanoseconds.

*/