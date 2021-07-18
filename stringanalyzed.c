
#include "stringanalyzed.h"

/*strip the given string from the white chars in the beginning and the end*/
void strip(char *str) {
    char newString[MAXLENGTH] = {0};
    int left = 0;
    int right = strlen(str) - 1;

    while (isspace(str[left]) && left < right) {
        left++;
    }
    while (isspace(str[right]) && left < right) {
        right--;
    }
    strncpy(newString, str + left, right - left + 1);
    memset(str, 0, MAXLENGTH);
    strcpy(str, newString);
}

int split(char *str, char *delimiter, char *before, char *after) {
    int i, j;
    memset(after, 0, MAXLENGTH);
    memset(before, 0, MAXLENGTH);
    for (i = 0; i < strlen(str); i++) {
        for (j = 0; j < strlen(delimiter); j++) {
            if (delimiter[j] == str[i]) {
                strncpy(before, str, i);
                strcpy(after, str + i + 1);
                return VALID_SPLIT;
            }
        }
    }
    strcpy(before, str);
    return SPLIT_ERROR;
}

int functionNameAnalysis(char *str) {
    if (strcmp(str, "read_set") == 0)
        return READ_SET;
    else if (strcmp(str, "print_set") == 0)
        return PRINT_SET;
    else if (strcmp(str, "union_set") == 0)
        return UNION_SET;
    else if (strcmp(str, "intersect_set") == 0)
        return INTERSECT_SET;
    else if (strcmp(str, "sub_set") == 0)
        return SUB_SET;
    else if (strcmp(str, "symdiff_set") == 0)
        return SYMDIFF_SET;
    else if (strcmp(str, "stop") == 0)
        return STOP;
    return COMMAND_NAME_ERROR; /*error -Undefined command name */
}

int subNameAnalysis(char *str) {
    if (strstr(str, "read_set") != NULL)
        return READ_SET;
    else if (strstr(str, "print_set") != NULL)
        return PRINT_SET;
    else if (strstr(str, "union_set") != NULL)
        return UNION_SET;
    else if (strstr(str, "intersect_set") != NULL)
        return INTERSECT_SET;
    else if (strstr(str, "sub_set") != NULL)
        return SUB_SET;
    else if (strstr(str, "symdiff_set") != NULL)
        return SYMDIFF_SET;
    else if (strstr(str, "stop") != NULL)
        return STOP;
    return COMMAND_NAME_ERROR; /*error -Undefined command name */
}


int setNameAnalysis(char *str) {
    if (strcmp(str, "SETA") == 0)
        return SETA_INDEX;
    else if (strcmp(str, "SETB") == 0)
        return SETB_INDEX;
    else if (strcmp(str, "SETC") == 0)
        return SETC_INDEX;
    else if (strcmp(str, "SETD") == 0)
        return SETD_INDEX;
    else if (strcmp(str, "SETE") == 0)
        return SETE_INDEX;
    else if (strcmp(str, "SETF") == 0)
        return SETF_INDEX;
    return ERROR_INDEX; /*error -Undefined set name */
}

int commandAnalysis(char *str, set *sets[6]) {
    char before[MAXLENGTH] = {0};
    char after[MAXLENGTH] = {0};
    char lineCpy[MAXLENGTH] = {0};
    int splitStr;
    int command;

    splitStr = split(str, " \t", before, after); /*split by tab \t */
    if (splitStr == SPLIT_ERROR) {
        if (functionNameAnalysis(str) == STOP) {
            return STOP;
        }
        if (subNameAnalysis(str) == COMMAND_NAME_ERROR) {
            printf("Undefined command name\n");
            return 0;
        } else {
            printf("Undefined command\n");
            return 0;
        }
    }
    strip(before);
    strip(after);
    /*operands analysis*/
    command = functionNameAnalysis(before);
    if (command == COMMAND_NAME_ERROR) {
        strcpy(lineCpy, before);
        memset(before, 0, MAXLENGTH);
        memset(after, 0, MAXLENGTH);
        splitStr = split(lineCpy, ",", before, after);
        if (splitStr == SPLIT_ERROR) /*couldn't find a ","*/
        {
            printf("Undefined command name\n");
            return 0;
        } else {
            strip(before);
            /*"union_sefff   ,SETA,SETB,SETC"  */
            command = functionNameAnalysis(before);
            if (command == COMMAND_NAME_ERROR) {
                printf("Undefined command name\n");
                return 0;
            }
            /* "read_set,  SETA,..."  situation*/
            printf("Illegal comma \n");
            return 0;
        }
    }
    if (command == UNION_SET || command == INTERSECT_SET || command == SUB_SET || command == SYMDIFF_SET) {
        onlyGroups(command, after, sets);
    } else if (command == READ_SET) {
        readSet(after, sets);
    } else if (command == PRINT_SET) {
        printSet(after, sets);
    }
    return 1;
}

void onlyGroups(int command, char *str, set *sets[6]) {
    int valid, validWhite;
    char before[MAXLENGTH] = {0};
    char after[MAXLENGTH] = {0};
    pset setArray[MAX_SET];
    pset validSet;
    int validSetIndex;
    int counter = 0; /* count the number of valid sets*/
    valid = split(str, ",", before, after);
    if (valid == SPLIT_ERROR) {
        validWhite = split(str, " \t", before, after);
        if (validWhite == SPLIT_ERROR) {
            if (strcmp(str, "") == 0) {
                printf("Missing parameter\n");
                return;
            }
            validSetIndex = setNameAnalysis(str);
            if (validSetIndex == ERROR_INDEX) {
                printf("Undefined set name\n");
                return;
            } else {
                printf("Missing parameter\n");
                return;
            }
        } else {/*we found a white char but not a ,*/
            validSetIndex = setNameAnalysis(before);
            if (validSetIndex == ERROR_INDEX) {
                printf("Undefined set name\n");
                return;
            }
            printf("Missing comma\n"); /*SETF SETD SETE*/
            return;

        }
    }
    strip(before);
    strip(after);
    validSetIndex = setNameAnalysis(before);
    if (validSetIndex == ERROR_INDEX) {
        printf("Undefined set name\n");
        return;
    }
    /*we found the first set*/
    validSet = sets[validSetIndex];
    setArray[counter] = validSet;
    counter++;
    strcpy(str, after);
    memset(before, 0, MAXLENGTH);
    memset(after, 0, MAXLENGTH);

    /*find the second*/
    valid = split(str, ",", before, after);
    if (valid == SPLIT_ERROR) {
        validWhite = split(str, " \t", before, after);
        if (validWhite == SPLIT_ERROR) {
            if (strcmp(str, "") == 0) {
                printf("Missing parameter\n");
                return;
            }
            validSetIndex = setNameAnalysis(str);
            if (validSetIndex == ERROR_INDEX) {
                printf("Undefined set name\n");
                return;
            } else {
                printf("Missing parameter\n");
                return;

            }
        } else {/*we found a white char but not a ,*/
            validSetIndex = setNameAnalysis(before);
            if (validSetIndex == ERROR_INDEX) {
                printf("Undefined set name\n");
                return;
            }
            printf("Missing comma\n"); /*SETF SETD SETE*/
            return;

        }
    }
    strip(before);
    strip(after);
    validSetIndex = setNameAnalysis(before);
    if (validSetIndex == ERROR_INDEX) {
        if (strcmp(before, "") == 0) {
            printf("Multiple consecutive commas\n");
            return;
        }
        printf("Undefined set name\n");
        return;
    }
    /*we found the second set*/
    validSet = sets[validSetIndex];
    setArray[counter] = validSet;
    counter++;
    strcpy(str, after);
    memset(before, 0, MAXLENGTH);

    if ((strcmp(after, "") == 0)) {
        printf("Missing parameter\n");
        return;
    }

    validSetIndex = setNameAnalysis(after);
    if (validSetIndex == ERROR_INDEX) {
        if (strlen(after) <= SET_LENGTH) { /*seta*/
            printf("Undefined set name \n");
            return;
        } else { /*SETA,SETB,SETA,...*/
            printf("Extraneous text after end of command\n");
            return;
        }
    }
    validSet = sets[validSetIndex];
    setArray[counter] = (validSet);
    counter++;
    if (counter < 3) {
        printf("Missing parameter\n");
        return;
    }
    setFunctions(command, (setArray[0]), (setArray[1]), (setArray[2]));
}

void readSet(char *str, set *sets[6]) {
    int valid, value, i, validInt;
    char before[MAXLENGTH] = {0};
    char after[MAXLENGTH] = {0};
    char copy[MAXLENGTH] = {0};
    char command[5] = {0};
    int numbers[MAXLENGTH] = {0};
    pset validSet;
    int validSetIndex;

    valid = split(str, ",", before, after);
    if (valid == SPLIT_ERROR) {
        printf("Missing parameter\n");
        return;
    }
    strip(before);
    validSetIndex = setNameAnalysis(before);
    if (validSetIndex == ERROR_INDEX) {
        /*read_set SETA 1,2,3,4,-1 - missing comma after legal set name*/
        strncpy(command, before, SET_LENGTH);
        validSetIndex = setNameAnalysis(command);
        if (validSetIndex == ERROR_INDEX) {
            printf("Undefined set name\n");
            return;
        }
        memset(before, ' ', SET_LENGTH); /* "     1"*/
        validInt = isDigit(before);
        if (validInt == DIGIT_ERROR) {
            printf("Undefined set name\n");
        } else printf("Missing comma after valid set name\n");
        return;
    }

    validSet = sets[validSetIndex];
    strcpy(copy, after);

    for (i = 0; i < (MAXLENGTH - 2) && numbers[i] != (-1); i++) {
        memset(before, 0, MAXLENGTH);
        memset(after, 0, MAXLENGTH);
        valid = split(copy, ",", before, after);
        strip(before);
        strip(after);
        memset(copy, 0, MAXLENGTH);
        strcpy(copy, after);
        if (valid == SPLIT_ERROR) {
            /*SETA, -1 - we couldn't fine an ',' a valid situation*/
            if (strcmp(before, "-1") == 0) {/* before - a valid set , after: string with -1*/
                numbers[i] = -1;
                break;
            }
                /*"SETA, 45 -1"  - we couldn't fine an ',' and the last number isn't -1 */
            else {
                printf("List of set members is not terminated correctly\n");
                return;
            }
        } else {
            if (strcmp(before, "") == 0) /*SETA,1,2,,-1 */
            {
                printf("Multiple consecutive commas\n");
                return;
            }
            if (strchr(before, ' ') != NULL || strchr(before, '\t') != NULL) /*before : "6   5" not an int*/
            {
                printf("Invalid set member -missing comma\n");
                return;
            }
            if (strcmp(before, "0") != 0) {
                validInt = isDigit(before);
                value = atoi(before);
                if (validInt == DIGIT_ERROR && value > 0) /* If in the string we have a non digit 0-9.*/
                {
                    printf("Invalid set member %s not an integer\n", before);
                    return;
                }

                if (value == 0) /* If no valid int value takes place, then the function atoi returns zero.*/
                {
                    printf("Invalid set member %s not an integer\n", before);
                    return;
                }
                if (value == (-1)) {
                    numbers[i] = value;
                    break;
                }
                if ((value < 0 || value > 127)) {
                    printf("Invalid set member %s value out of range\n", before);
                    return;
                } else {
                    numbers[i] = value;
                }
            } else {
                numbers[i] = 0; /*a 0 number*/}
        }
    }

    if (strcmp(before, "-1") != 0) {
        printf("Extraneous text after end of command the number -1\n");
        return;
    }
    read_set(validSet, numbers);
}

void printSet(char *str, set *sets[6]) {
    int valid;
    char before[MAXLENGTH] = {0};
    char after[MAXLENGTH] = {0};
    pset validSet;
    int validSetIndex;
    if (strcmp(str, "") != 0) {
        valid = split(str, ",", before, after);
        if (valid == SPLIT_ERROR) {
            validSetIndex = setNameAnalysis(str);
            if (validSetIndex == ERROR_INDEX) {
                printf("Undefined set name\n");
                return;
            }
            validSet = sets[validSetIndex];
        } else { /*split succeeded*/
            strip(before);
            validSetIndex = setNameAnalysis(before);
            if (validSetIndex == ERROR_INDEX) {
                printf("Undefined set name\n");
                return;
            } else {
                printf("Extraneous text after end of command\n");
                return;
            }
        }
    } else {
        printf("Missing parameter\n");
        return;
    }
    print_set(validSet);
}

void setFunctions(int command, pset s1, pset s2, pset s3) {
    if (command == UNION_SET) {
        union_set(s1, s2, s3);
    }
    if (command == INTERSECT_SET) {
        intersect_set(s1, s2, s3);

    }
    if (command == SUB_SET) {
        sub_set(s1, s2, s3);
    }
    if (command == SYMDIFF_SET) {
        symdiff_set(s1, s2, s3);
    }
}


int isDigit(char *str) {
    int i = 0;
    while (i < strlen(str)) {
        if (isdigit(str[i]) == 0) /*Not a digit*/
            return DIGIT_ERROR;
        i++;
    }
    return VALID_DIGIT; /*all digit*/
}


