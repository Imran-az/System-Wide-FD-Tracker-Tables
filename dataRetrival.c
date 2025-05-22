#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include "dataStruct.h"
#include "dataRetrival.h"
#include "pidRetrival.h"
#include "sys/stat.h"
#include <linux/limits.h>

void getData(fdList **head, int pidVal, int fdVal){
    ///_|> descry: This function retrives all the other data relating to the PID and FD, such as Inodes and Filenames
    ///_|> head: this refers to the head of the linked list as we traverse through the PIDs and FDs retriving the relating Inodes, and Filenames
    ///_|> pidVal: represents the pidVal we are trying to retrieve data from
    ///_|> fdVal: represents the fdVal we are trying to retrieve data from
    ///_|> returning: This function's return type is a void as this function directly updates the linkedlist
    if (*head == NULL){
        fprintf(stderr, "error with linked list");
        return;
    }
    struct stat file_stat;
    char filePath[1024];
    char buffer[PATH_MAX];
    ssize_t nbytes;
    snprintf(filePath, sizeof(filePath), "/proc/%d/fd/%d", pidVal, fdVal);
    int ret = stat(filePath, &file_stat);

    if (ret < 0){
        fprintf(stderr, "error with stat struct");
        return;
    }
    else{
        (*head)->inode = (long)(file_stat.st_ino);
        nbytes = readlink(filePath, buffer, sizeof(buffer) - 1);
        if(nbytes == -1){
            fprintf(stderr, "error with readlink");
            exit(1);
        }
        else{
            buffer[nbytes] = '\0';
            strcpy((*head)->filename, buffer);
        }
    }
}

void createFDNode(fdList *newNode, int fdNum){
    ///_|> descry: This function creates a new FD node and sets all the fields to defualt values and assigns the fd Val to num
    ///_|> fdNum: represents the fd value we want saved
    ///_|> returning: This function return type is a void type
    if (newNode == NULL){
        fprintf(stderr, "Error with Memory Allocation");
        exit(1);
    }
    newNode ->fdVal = fdNum;
    newNode ->filename[0] = '\0';
    newNode ->inode = 0;
    newNode -> next = NULL;

}

void getFDs(dataValues **head){
    ///_|> descry: This function gets the FD Values relating to the PID value which we assign as we traverse through our linked list
    ///_|> head: represents the head of the linked list of PIDs that we are traversing
    ///_|> returning: This function's return type is null as we are directly editing the linked list
    dataValues *temp = *head;
    while (temp != NULL){
        int pidVal = temp ->pidVal;
        char filePath[1024];
        int index = 0;
        snprintf(filePath, sizeof(filePath), "/proc/%d/fd", pidVal);

        DIR *dir = opendir(filePath);
        if (dir == NULL){
            fprintf(stderr, "error opening directory");
            exit(1);
        }

        struct dirent *dp;
        while((dp = readdir(dir)) != NULL){
            char* dpVal = dp ->d_name;
            if (checkisdigit(dpVal) == 1){
                int dpNum = strtol(dpVal, NULL, 10);
                fdList *newFD = (fdList*)malloc(sizeof(fdList));
                createFDNode(newFD, dpNum);
                
                if (temp->fds == NULL){  
                    temp -> fds = newFD;
                    getData(&newFD, pidVal, dpNum);
                }
                else{
                    fdList *tempy = temp->fds;
                    while (tempy->next != NULL){
                        tempy = tempy->next;
                    }
                    getData(&newFD, pidVal, dpNum);
                    tempy->next = newFD;
                }
                index++;
            }
        }
        closedir(dir);
        temp -> fdCount = index;
        temp = temp -> next;
    }
}