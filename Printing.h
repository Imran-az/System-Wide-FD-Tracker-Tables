#ifndef Printing_header
#define Printing_header
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>


void printing(struct dataValues **head, int flag);
void printProcess(struct dataValues **head, int pidVal);
void printSystemWide(struct dataValues **head, int pidVal);
void printVnodes(struct dataValues **head, int pidVal);
void printComposite(struct dataValues **head, int pidVal);
void printSummary(struct dataValues **head, int pidVal);
void printThreshold(struct dataValues **head, int thresholdVal);
#endif