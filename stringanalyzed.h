
#ifndef MMN22_STRINGANALYZED_H
#define MMN22_STRINGANALYZED_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"

#define VALID_FLAG 1
#define INVALID_FLAG 0

#define VALID_EOF 0
#define EOF_ERROR 1


#define READ_SET 1
#define PRINT_SET 2
#define UNION_SET 3
#define INTERSECT_SET 4
#define SUB_SET 5
#define SYMDIFF_SET 6
#define STOP 7

#define COMMAND_NAME_ERROR -1
#define SPLIT_ERROR -1
#define VALID_SPLIT 1
#define SET_LENGTH 4
#define MAX_SET 3
#define DIGIT_ERROR -1
#define VALID_DIGIT 1

#define SETA_INDEX 0
#define SETB_INDEX 1
#define SETC_INDEX 2
#define SETD_INDEX 3
#define SETE_INDEX 4
#define SETF_INDEX 5
#define ERROR_INDEX -1

void strip(char*);
int split (char*,char* , char*,char*);
int commandAnalysis(char*,set*[]);
int functionNameAnalysis(char*);
int setNameAnalysis(char*);
void setFunctions(int,pset,pset,pset);
int isDigit(char* );

void onlyGroups(int , char [], set *[]);
void readSet(char*, set *[]);
void printSet(char*, set *[]);


#endif /*MMN22_STRINGANALYZED_H*/
