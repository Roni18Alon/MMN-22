#ifndef MMN22_SET_H
#define MMN22_SET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct set *pset;
typedef struct set{
    int lowest; /*0-31*/
    int low;   /*32-63*/
    int high; /*64 - 95*/
    int highest; /*96 - 127*/
}set;

#define MAXLENGTH 82
#define LASTCHAR 80

void read_set(pset ,int*);
void print_set(pset);
void union_set (pset, pset,pset);
void intersect_set (pset,pset,pset);
void sub_set (pset,pset,pset);
void symdiff_set (pset,pset,pset);

#endif
