#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include "pidRetrival.h"
#include "dataStruct.h"
#include "dataRetrival.h"
#include "Printing.h"

void freeNodes(dataValues **head){
    ///_|> descry: frees all the data that has been allocated throughout the program
    ///_|> head: refers to the head of the linked list which ultimately stores all the data on pid, fds, inodes, and filenames
    ///_|> returning: function's return type is a void so it does not return anything
    dataValues *temp = *head;
    //goes through pids
    while(temp != NULL){
        fdList *tempfd = temp ->fds;
        //goes through fds
        while(tempfd != NULL){
            fdList *tempfd2 = tempfd->next;
            free(tempfd);
            tempfd = tempfd2;
        }
        dataValues *temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}

int flag_already_exists(int* flags, int key){
    ///_|> descry: This function is a checker to see if the flags have already been detected
    ///_|> flags: represents an array consisting of the flags and whether or not they have been detected. 1 in the array spot represents if it has been detected and 0 represents it hasnt
    ///_|> key: represents the index I am specifically looking at in the array
    ///_|> returning: returns a 1 if the flags exists and returns 0 if it doesn't exist, type: int
    if (flags[key] == 1){
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]){
    int flagsDetected[6] = {0};
    int threshold = 0;
    int enteredpidVal = 0;
    int enteredPidFlag = 0;
    int errorFlag = 0;

    dataValues *pidList = pidValues();
    getFDs(&pidList);
    dataValues *temp = pidList;

    if (argc == 1){
        printComposite(&temp, enteredpidVal);
    }
    else{
    for (int i = 1; i < argc; i++){
        if (i == 1 && checkisdigit(argv[i]) == 1){
            enteredpidVal = strtol(argv[i], NULL, 10);
            enteredPidFlag = 1;
        }
        //per process flag
        else if (strcmp(argv[i], "--per-process") == 0){
            if (flag_already_exists(flagsDetected, 0)){
                fprintf(stderr, "invalid flag1");
                return 0;
            }
            flagsDetected[0] = 1;
            
        }
        //systemWide
        else if (strcmp(argv[i], "--systemWide") == 0){
            if (flag_already_exists(flagsDetected, 1)){
                fprintf(stderr, "invalid flag2");
                return 0;
            }
            flagsDetected[1] = 1;
        }
        //Vnodes
        else if (strcmp(argv[i], "--Vnodes") == 0){
            if (flag_already_exists(flagsDetected, 2)){
                fprintf(stderr, "invalid flag3");
                return 0;
            }
            flagsDetected[2] = 1;
        }
        //Composite
        else if (strcmp(argv[i], "--composite") == 0){
            if (flag_already_exists(flagsDetected, 3)){
                fprintf(stderr, "invalid flag4");
                return 0;
            }
            flagsDetected[3] = 1;
        }
        //Summary
        else if (strcmp(argv[i], "--summary") == 0){
            if (flag_already_exists(flagsDetected, 4)){
                fprintf(stderr, "invalid flag5");
                return 0;
            }
            flagsDetected[4] = 1;
        }
        //Threshold
        else if (strncmp(argv[i], "--threshold=", 12) == 0){
            if (flag_already_exists(flagsDetected, 5)){
                fprintf(stderr, "invalid flag5");
                return 0;
            }
            char thresholdStr[256];
            strncpy(thresholdStr, argv[i] + 12, sizeof(thresholdStr) - 1);
            if (checkisdigit(thresholdStr) == 1){
                threshold = strtol(thresholdStr, NULL, 10);
                flagsDetected[5] = 1;
            }
            else{
                fprintf(stderr, "invalid threshold value\n");
                exit(1);
            }
        }
        else{
            fprintf(stderr, "invalid flags\n");
            errorFlag = 1;
            break;
        }
    }
}
if (errorFlag != 1){
    //Calling functions if they were flagged by the user
    if (flagsDetected[0] == 1){
        printProcess(&temp, enteredpidVal);
    }
    if (flagsDetected[1] == 1){
        printSystemWide(&temp, enteredpidVal);
    }
    if (flagsDetected[2] == 1){
        printVnodes(&temp, enteredpidVal);
    }
    if (flagsDetected[3] == 1){
        printComposite(&temp, enteredpidVal);
    }
    if (flagsDetected[4] == 1){
        printSummary(&temp, enteredpidVal);
    }
    if (flagsDetected[5] == 1){
        printThreshold(&temp, threshold);
    }
}
//when only positional argument is given
    if ( enteredPidFlag == 1 && flagsDetected[0] == 0 && flagsDetected[1] == 0 && flagsDetected[2] == 0 && flagsDetected[3] == 0
        && flagsDetected[4] == 0 && flagsDetected[5] == 0){
            printProcess(&temp, enteredpidVal);
            printSystemWide(&temp, enteredpidVal);
            printVnodes(&temp, enteredpidVal);
            printComposite(&temp, enteredpidVal);
    }
    freeNodes(&pidList);
    return 0;
}
