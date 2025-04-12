#ifndef pidRetrival_header
#define pidRetrival_header
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

int checkisdigit(char* str);
int countNumLines(FILE* file);


struct dataValues *pidValues();
void populateData(struct dataValues *dataArray, int size);
void populatePID(FILE* file, struct dataValues* dataArray);

#endif