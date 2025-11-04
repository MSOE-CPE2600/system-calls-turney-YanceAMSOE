/*
* Filename: finfo.c
* Description: 
* Author: Aden Yance
* Date: 10/30/2025
* Section 111
* compile with a Makefile then ./FINFO
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    // Owner permissions
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    // Group permissions
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    // Other permissions
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Check if a filename was provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Get file stats
    struct stat fileStat;
    if (stat(argv[1], &fileStat) == -1) {
        perror("Error retrieving file info");
        exit(EXIT_FAILURE);
    }

    printf("File Information for: %s\n", argv[1]);
    printf("----------------------------------------\n");

    // File type
    printf("File Type: ");
    if (S_ISREG(fileStat.st_mode))      printf("Regular File\n");
    else if (S_ISDIR(fileStat.st_mode)) printf("Directory\n");
    else if (S_ISLNK(fileStat.st_mode)) printf("Symbolic Link\n");
    else if (S_ISCHR(fileStat.st_mode)) printf("Character Device\n");
    else if (S_ISBLK(fileStat.st_mode)) printf("Block Device\n");
    else if (S_ISFIFO(fileStat.st_mode))printf("FIFO/Named Pipe\n");
    else if (S_ISSOCK(fileStat.st_mode))printf("Socket\n");
    else                                printf("Unknown Type\n");

    // Permissions 
    print_permissions(fileStat.st_mode);

    // Owner (UID) 
    printf("Owner UID: %d\n", fileStat.st_uid);

    // File size 
    printf("File Size: %ld bytes\n", fileStat.st_size);

    //Last modified time
    char mod_time[100];
    struct tm *timeinfo = localtime(&fileStat.st_mtime);
    strftime(mod_time, sizeof(mod_time), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified: %s\n", mod_time);

    return 0;
}