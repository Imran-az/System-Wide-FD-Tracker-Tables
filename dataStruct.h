#ifndef dataStruct_header
#define dataStruct_header
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

typedef struct fdList {
    int fdVal; 
    long int inode;
    char filename[1024];
    struct fdList *next;
} fdList;

typedef struct dataValues {
    int pidVal;
    struct fdList *fds;
    int fdCount;
    struct dataValues *next;
} dataValues;

#endif