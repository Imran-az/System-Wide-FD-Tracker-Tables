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

int checkisdigit(char* str){
    ///_|> descry: This function goes through a given string and ensures that the string only contains digits
    ///_|> str: represents the string we want to check that only contains digits
    ///_|> returning: This function returns 0 if the string contians something other than only digits and 1 if it only consists of digits, type: int
    int length = strlen(str);
    for (int i = 0; i < length; i++){
        if (!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}

void createNode(dataValues *newNode, int pidValue){
    ///_|> descry: This function creates a new dataValues node and assigns each field to its default type
    ///_|> newNode: represents the dataValues node we want to assign its following fields to its default types
    ///_|> pidValue: represents the PID value we want saved in the linked list
    ///_|> returning: This functions return type is a void
    if (newNode == NULL){
        fprintf(stderr, "Error with Memory Allocation");
        exit(1);
    }
        newNode ->pidVal = pidValue;
        newNode ->fds = NULL;
        newNode ->next = NULL;
}

dataValues *pidValues(){
    ///_|> descry: This function gets all the PID Values 
    ///_|> returning: This function returns a dataValues type
    DIR *dir = opendir("/proc");

    if (dir == NULL){
        fprintf(stderr,"Error opening Directory");
        exit(1);
    }
    
    dataValues *head = NULL;
    dataValues *temp = NULL;
    //writing the values in the directory to the file
    struct dirent *dp;
    while ((dp = readdir(dir)) != NULL){
        char *pid = dp -> d_name; 
        //ensuring we only get pid numbers
        if (checkisdigit(pid) == 1){
            char filePath[1024];
            snprintf(filePath, sizeof(filePath), "/proc/%s/fd", pid);
            DIR *dir2 = opendir(filePath);
            
            if( dir2 != NULL){
                dataValues *newNode = (dataValues*)malloc(sizeof(dataValues));
                int pidValue = strtol(pid, NULL, 10);
                createNode(newNode, pidValue);

                //adding the node to linked list
                if (head == NULL){
                    head = newNode;
                    temp = head;
                }
                else{
                    temp->next = newNode;
                    temp = temp->next;
                }
                closedir(dir2);
            }
        }
    }
    closedir(dir);
    return head;
}