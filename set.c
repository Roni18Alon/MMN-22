#include "set.h"
#include <stdio.h>


void read_set(pset s1 ,int *numbers)
{
    int i=0;
    int mask;

    s1->lowest=0;
    s1->low=0;
    s1->high=0;
    s1->highest=0;

    while (numbers[i]!=(-1)) {
        mask = (1<<(numbers[i]%32));

        if (numbers[i]<(8*sizeof(int))) {
            s1->lowest = ((s1->lowest|mask));
        }
        if (numbers[i]>=(8*sizeof(int)) && numbers[i]<(16*sizeof(int))) {
            s1->low = ((s1->low)|mask);
        }
        if (numbers[i]>=(16*sizeof(int)) && numbers[i]<(24*sizeof(int))) {
            s1->high = ((s1->high)|mask);
        }
        if (numbers[i]>=(24*sizeof(int)) && numbers[i]<(32*sizeof(int))) {
            s1->highest = ((s1->highest)|mask);
        }
        numbers[i]=0;
        i++;
    }
}

void print_set(pset s1)
{
    int i=0;
    int mask;
    int counter=0;

    printf("The SET group contains:\n");
    while (i<(32* sizeof(int))) {
        mask = (1<<i%32);
        if (i<(8*sizeof(int))) {
            if (((s1->lowest) | mask) == s1->lowest) {
                printf("%d ",i);
                counter++;
            }
        }
        if (i>=(8*sizeof(int)) && i<(16*sizeof(int))) {
            if ((( s1->low) | mask) ==  s1->low) {
                printf("%d ",i);
                counter++;
            }
        }
        if (i>=(16*sizeof(int)) && i<(24*sizeof(int))) {
            if (((s1->high) | mask) == s1->high) {
                printf("%d ",i);
                counter++;
            }

        }
        if (i>=(24*sizeof(int)) && i<(32*sizeof(int))) {
            if (((s1->highest) | mask) == s1->highest) {
                printf("%d ",i);
                counter++;
            }
        }
        if ((counter%16)==0 && counter!=0) {
            printf("\n");
        }
        i++;
    }
    if (counter == 0)
        printf("The set is empty\n");

	printf("\n");
}

void union_set (pset s1, pset s2 , pset s3)
{
    s3->lowest=((s1->lowest)|(s2->lowest));
    s3->low=((s1->low)|(s2->low));
    s3->high=((s1->high)|(s2->high));
    s3->highest=((s1->highest)|(s2->highest));

}

void intersect_set (pset s1, pset s2 , pset s3)
{
    s3->lowest=((s1->lowest)& (s2->lowest));
    s3->low=((s1->low)& (s2->low));
    s3->high=((s1->high)& (s2->high));
    s3->highest=((s1->highest)& (s2->highest));
}

void sub_set (pset s1, pset s2 , pset s3)
{

    int i=0;
    int mask;

    s3->lowest = 0;
    s3->low = 0;
    s3->high= 0;
    s3->highest = 0;

    while (i<(32*sizeof(int))) {
        mask = (1<<i%32);
        if (i<(8*sizeof(int))) {
            if (((s1->lowest & mask) == mask) && ((s2->lowest & mask) != mask)) {
                s3->lowest = (s3->lowest | mask);
            }
        }
        if (i>=(8*sizeof(int)) && i<(16*sizeof(int))) {
            if (((s1->low & mask) == mask) && ((s2->low & mask) != mask)) {
                s3->low = (s3->low | mask);
            }
        }
        if (i>=(16*sizeof(int)) && i<(24*sizeof(int))) {
            if (((s1->high & mask) == mask) && ((s2->high & mask) != mask)) {
                s3->high = (s3->high | mask);

            }
        }
        if (i>=(24*sizeof(int)) && i<(32*sizeof(int))) {
            if (((s1->highest & mask) == mask) && ((s2->highest & mask) != mask)) {
                s3->highest = (s3->highest | mask);
            }
        }
        i++;
    }
}

void symdiff_set (pset s1, pset s2 , pset s3)  /*xor*/
{
    s3->lowest=((s1->lowest)^ (s2->lowest));
    s3->low=((s1->low)^ (s2->low));
    s3->high=((s1->high)^ (s2->high));
    s3->highest=((s1->highest)^(s2->highest));
}

