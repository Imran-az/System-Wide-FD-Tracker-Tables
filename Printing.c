#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include "pidRetrival.h"
#include "dataStruct.h"
#include "errno.h"

void printProcess(dataValues **head, int enteredpidVal){
    ///_|> descry: This function displays all the data that must be presented when the --per-process flag is flagged
    ///_|> head: represents the head of the linked list that contains the PID, FDs, Inodes, and Filename values
    ///_|> enteredpidVal: represents the PID value specified by the user
    ///_|> returning: This function return type is void
    dataValues *temp = *head;
    printf("  PID      FD  \n");
    printf("===============================================\n");

    while (temp != NULL){
        int pidVal = temp->pidVal;

        if (enteredpidVal != 0 && enteredpidVal != pidVal){
            temp = temp -> next;
            continue;
        }

        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "/proc/%d/fd", pidVal);

        fdList *tempfd = temp->fds;
        while (tempfd != NULL){
            printf("%-10d %d\n", pidVal, tempfd->fdVal);
            tempfd = tempfd->next;
        }
        temp = temp -> next;
    }
    printf("===============================================\n");
}
void printSystemWide(dataValues **head, int enteredpidVal){
    ///_|> descry: This function displays all the data that must be presented when the --systemWide flag is flagged
    ///_|> head: represents the head of the linked list that contains the PID, FDs, Inodes, and Filename values
    ///_|> enteredpidVal: represents the PID value specified by the user
    ///_|> returning: This function return type is void
    dataValues *temp = *head;
    printf(" PID        FD         FILENAME \n");
    printf("===============================================\n");

    while (temp != NULL){
        int pidVal = temp->pidVal;
        char filePath[1024];

        if (enteredpidVal != 0 && enteredpidVal != pidVal){
            temp = temp -> next;
            continue;
        }

        fdList *temp2 = temp->fds;
        while (temp2 != NULL){
            snprintf(filePath, sizeof(filePath), "/proc/%d/fd/%d", pidVal, temp2->fdVal);
            printf("%-11d %-10d %s\n", pidVal, temp2->fdVal, temp2->filename);
            temp2 = temp2 -> next;
        }

        temp = temp -> next;
    }
    printf("===============================================\n");
}
void printVnodes(dataValues **head, int enteredpidVal){
    ///_|> descry: This function displays all the data that must be presented when the --Vnodes flag is flagged
    ///_|> head: represents the head of the linked list that contains the PID, FDs, Inodes, and Filename values
    ///_|> enteredpidVal: represents the PID value specified by the user
    ///_|> returning: This function return type is void
    dataValues *temp = *head;
    printf("FD       Inodes         \n");
    printf("===============================================\n");

    while (temp != NULL){
        int pidVal = temp->pidVal;
        char filePath[1024];

        if (enteredpidVal != 0 && enteredpidVal != pidVal){
            temp = temp -> next;
            continue;
        }

        fdList *temp2 = temp->fds;
        while (temp2 != NULL){
            snprintf(filePath, sizeof(filePath), "/proc/%d/fd/%d", pidVal, temp2->fdVal);
            printf("%-8d %ld\n", temp2->fdVal, temp2->inode);
            temp2 = temp2 -> next;
        }
        temp = temp -> next;
    }
    printf("===============================================\n");
}
void printComposite(dataValues **head, int enteredpidVal){
    ///_|> descry: This function displays all the data that must be presented when the --composite flag is flagged
    ///_|> head: represents the head of the linked list that contains the PID, FDs, Inodes, and Filename values
    ///_|> enteredpidVal: represents the PID value specified by the user
    ///_|> returning: This function return type is void
    dataValues *temp = *head;
    printf("   PID         FD         FILENAME                   INODE \n");
    printf("==============================================================\n");

    while (temp != NULL){
        int pidVal = temp->pidVal;
        char filePath[1024];

        if (enteredpidVal != 0 && enteredpidVal != pidVal){
            temp = temp -> next;
            continue;
        }

        fdList *temp2 = temp->fds;
        while (temp2 != NULL){
            snprintf(filePath, sizeof(filePath), "/proc/%d/fd/%d", pidVal, temp2->fdVal);
            printf("%-14d %-10d %-28s %ld\n", pidVal, temp2->fdVal, temp2->filename, temp2->inode);
            temp2 = temp2 -> next;
        }
        temp = temp -> next;
    }
    printf("==============================================================\n");
}
void printSummary(dataValues **head){
    ///_|> descry: This function displays all the data that must be presented when the --summary flag is flagged
    ///_|> head: represents the head of the linked list that contains the PID, FDs, Inodes, and Filename values
    ///_|> enteredpidVal: represents the PID value specified by the user
    ///_|> returning: This function return type is void
    dataValues *temp = *head;
    printf(" Summary Table  \n");
    printf("================\n");
    while (temp != NULL){
        int pidVal = temp->pidVal;

        printf("%d (%d), ", pidVal, temp->fdCount);
        temp = temp -> next;
    }
    printf("\n");
}
void printThreshold(dataValues **head, int thresholdVal){
    ///_|> descry: This function displays all the data that must be presented when the --threshold flag is flagged
    ///_|> head: represents the head of the linked list that contains the PID, FDs, Inodes, and Filename values
    ///_|> enteredpidVal: represents the PID value specified by the user
    ///_|> returning: This function return type is void
    dataValues *temp = *head;
    printf(" Threshold Table  \n");
    printf("================\n");
    while(temp != NULL){
        int pidVal = temp->pidVal;
        if (temp->fdCount > thresholdVal){
            printf("%d (%d), ", pidVal, temp->fdCount );
        }
        temp = temp -> next;
    }
    printf("\n");
}
