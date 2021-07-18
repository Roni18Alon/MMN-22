/*
Name: Maman 22
Author: Roni Alon 315565176
Description: The program is an interactive calculator for set operations. It provides a set of operation the user can make 
	     using predefined format inputs from the standard input. The calculator notice everytime the input is not in 
	     the predefined format. The program should stop, only by insert "stop" as an input.
*/


#include "set.h"
#include "stringanalyzed.h"

int main() {

    char line[MAXLENGTH] = {0};
    char lineCpy[MAXLENGTH] = {0};
    int i;
    int commandVal = 0;
    int flag = VALID_FLAG;
    int reachedEOF = VALID_EOF;
    int ch;
    /*initialized the sets to empty sets*/
    set SETA = {0};
    set SETB = {0};
    set SETC = {0};
    set SETD = {0};
    set SETE = {0};
    set SETF = {0};
    set *sets[6];

    sets[0] = &SETA;
    sets[1] = &SETB;
    sets[2] = &SETC;
    sets[3] = &SETD;
    sets[4] = &SETE;
    sets[5] = &SETF;

    printf("\nWelcome to the  Interactive Sets calculator! \n");

    while (flag) {
        memset(line, 0, MAXLENGTH);
        memset(lineCpy, 0, MAXLENGTH);


        printf("\nPlease enter your commend: \n");

        if (reachedEOF) {
            printf("Reached EOF!");
            break;
        }

        fgets(line, MAXLENGTH, stdin);
        if (feof(stdin)) { reachedEOF = EOF_ERROR; }
        /*checks if the row is in the length boundaries*/
        for (i = 0; i <= LASTCHAR; i++) {
            if (line[i] == '\0') {
                strncpy(lineCpy, line, i + 1);
                break;
            }
        }

        if (((i - 1) == LASTCHAR) && line[i - 1] != '\0') {
            printf("%s", line);
            printf("\nThe maximum line length is 80 chars, please enter a new line\n");
            /*clear the invalid input*/
            while ((ch = getchar()) != '\n' && (ch = getchar()) != EOF)
                if (ch == EOF) {
                    printf("The program should not end with EOF\n");
                    flag = INVALID_FLAG;
                    return 0;
                } else { continue; }
        }
        printf(lineCpy[strlen(lineCpy) - 1] == '\n' ? "%s" : "%s\n", lineCpy);

        strip(lineCpy); /*strip white chars*/
        if (strcmp(lineCpy, "") == 0 || strcmp(lineCpy, "\n") == 0) {
            printf("\nEmpty command,please entre new a new one.\n");
            continue;
        }
        commandVal = commandAnalysis(lineCpy, sets);
        if (commandVal == STOP)
            flag = INVALID_FLAG;
    }

    printf("\nThanks for using the interactive sets calculator!\n");
    return 0;
}


