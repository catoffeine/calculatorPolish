#include <iostream>
#include "list.h"
#include "calc.h"
#include "easylogging++.h"
//#include "easyloggingpp/src/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

char * convertToPolishForm(const char *, char *, long long, long long *, int **);

long long calc(const char *expression, long long len, int *ERROR_CODE) {
    //Variables to initianalize in parent function
    long long buffSize = 0, i;
    char *newExp, *endPtr;
    long long newExpEnd = 0, number = 0;
    Node *node{NULL};
    long long result, temp;
    newExp = (char*)malloc(len * sizeof(char));
    if (!newExp) {
        *ERROR_CODE = 2;
        free(newExp);
        return 0;
    }
    //-----------------------------------
    newExp = convertToPolishForm(expression, newExp, len, &newExpEnd, &ERROR_CODE);
    if(VLOG_IS_ON(2)) LOG(TRACE) << "going to calculations";
    for (i = 0; i < newExpEnd; i++) {
        switch(newExp[i]) {
            case '*': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op * BEGIN | len: " << listLen(node);

                temp = popInd(&node, --buffSize);
                temp *= popInd(&node, --buffSize);
                insertInd(&node, buffSize++, temp);
                i++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op * END | len: " << listLen(node);
                continue;
            }
            case '/': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op / BEGIN | len: " << listLen(node);
                temp = popInd(&node, --buffSize);
                temp /= popInd(&node, --buffSize);
                insertInd(&node, buffSize++, temp);
                i++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op / END | len: " << listLen(node);
                continue;
            }
            case '+': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op + BEGIN | len: " << listLen(node);
                temp = popInd(&node, --buffSize);
                temp += popInd(&node, --buffSize);
                insertInd(&node, buffSize++, temp);
                i++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op + END | len: " << listLen(node);
                continue;
            }
            case '-': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op - BEGIN | len: " << listLen(node);
                temp = popInd(&node, --buffSize);
                temp -= popInd(&node, --buffSize);
                insertInd(&node, buffSize++, temp);
                i++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op - END | len: " << listLen(node);
                continue;
            }
            case ' ': {
                i++;
                continue;
            }
        }
        if(VLOG_IS_ON(2)) LOG(TRACE) << "NOT AN OPERATION ... BEGIN | len: " << listLen(node);
        number = strtoll(newExp + i, &endPtr, 10);
        if(VLOG_IS_ON(2)) LOG(TRACE) << "NOT AN OPERATION ... END | number: " << number << " | newExp: \"" << newExp << "\" | newExp + i: \"" << newExp + i << "\" | i: " << i << " | len: " << listLen(node);
        insertInd(&node, buffSize++, number);
        i = endPtr - newExp;
    }
    if(VLOG_IS_ON(2)) LOG(TRACE) << "AFTER CALCULATIONS | len: " << listLen(node);
    result = popInd(&node, 0);
    Node *p = node;
    if (p) {
        while (p->next) {
            if(VLOG_IS_ON(2)) LOG(TRACE) << printf("memoryFreeing: p->next input\n");
            free(p);
            p = p->next;
        }
        free(p);
    }
    free(newExp);
    return result;
}

void lltoa(long long num, char **expr, long long *buff, long long *len) {
    if(VLOG_IS_ON(2)) LOG(TRACE) << "input in lltoa, buff: " << (*buff) << ", len: " << (*len) <<", num: " << num << "\n";
    long long i, j, tmp;
    if ((!expr) || (!buff) || (!len)) {
        fprintf(stderr, "ERROR: invalid pointer on LINE: %d\n", __LINE__);
        return;
    }
    i = *buff;
    while (num) {
        tmp = num % 10;
        if (*buff + 1 > *len) {
            *expr = (char*)realloc(*expr, (*buff + 10) * sizeof(char));
            *len += 10;
//            *buff += 10;
        }
        (*expr)[*buff] = tmp + '0';
        *buff += 1;
        num = num / 10;
    }
    j = *buff - 1;
    while (i < j) {
        tmp = (*expr)[i];
        (*expr)[i] = (*expr)[j];
        (*expr)[j] = tmp;
        ++i;
        --j;
    }
    (*expr)[*buff] = ' ';
    *buff += 1;
    if(VLOG_IS_ON(2)) LOG(TRACE) << "--lltoa-- END\n";
}

char * convertToPolishForm(const char *expression, char *newExp,
        long long len, long long *newExpEnd, int **ERROR_CODE) {
    long long buffSize = 0;
    long long newExpLen = 0, number, i;
    long long counter = 0;
    char *endPtr, *buff;
    if (!expression) {
        **ERROR_CODE = 1;
        return 0;
    }
    buff = (char*)malloc(len * sizeof(char));
    if (!buff) {
        **ERROR_CODE = 2;
        free(buff);
        return 0;
    }
    newExpLen = len;
    number = strtoll(expression, &endPtr, 10);
    lltoa(number, &newExp, newExpEnd, &newExpLen);
    if (VLOG_IS_ON(2)) { //was changed
        for (i = 0; i < *newExpEnd - 1; i++) {
            LOG(TRACE) << newExp[i];
        }
        LOG(TRACE) << "\n";
    }
    if (VLOG_IS_ON(2)) { //was changed
        for (i = 0; i < *newExpEnd - 1; i++) {
            LOG(TRACE) << newExp[i];
        }
        LOG(TRACE) << "\n";
    }
    for (counter = endPtr - expression; counter < len; counter++) {
        switch(expression[counter]) {
            case '*': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op * BEGIN";
                if (endPtr - expression >= len) {
                    **ERROR_CODE = 3;
                    free(newExp);
                    free(buff);
                    return 0;
                }
                number = strtoll(endPtr + 1, &endPtr, 10);
                lltoa(number, &newExp, newExpEnd, &newExpLen);
                if (VLOG_IS_ON(2)) { //was changed
                    for (i = 0; i < *newExpEnd - 1; i++) {
                        LOG(TRACE) << newExp[i];
                    }
                    LOG(TRACE) << "\n";
                }
                buff[buffSize++] = '*';
                counter = endPtr - expression - 1;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op * END";
                break;
            }
            case '/': {
                if (endPtr - expression >= len) {
                    **ERROR_CODE = 3;
                    free(newExp);
                    free(buff);
                    return 0;
                }
                number = strtoll(endPtr + 1, &endPtr, 10);
                lltoa(number, &newExp, newExpEnd, &newExpLen);
                if (VLOG_IS_ON(2)) { //was changed
                    for (i = 0; i < *newExpEnd - 1; i++) {
                        LOG(TRACE) << newExp[i];
                    }
                    LOG(TRACE) << "\n";
                }
                buff[buffSize++] = '/';
                counter = endPtr - expression - 1;
                break;
            }
            case '+': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op + BEGIN";
                if (buffSize) {
                    if ((buff[buffSize - 1] == '*') ||
                            (buff[buffSize - 1] == '/') ||
                            (buff[buffSize - 1] == '-')) {
                        while (buffSize) {
                            newExp[*newExpEnd++] = buff[--buffSize];
                            newExp[*newExpEnd++] = ' ';
                        }
                    }
                }
                if (endPtr - expression >= len) {
                    **ERROR_CODE = 3;
                    free(newExp);
                    free(buff);
                    return 0;
                }
                number = strtoll(endPtr + 1, &endPtr, 10);
                lltoa(number, &newExp, newExpEnd, &newExpLen);
                if (VLOG_IS_ON(2)) { //was changed
                    for (i = 0; i < *newExpEnd - 1; i++) {
                        LOG(TRACE) << newExp[i];
                    }
                    LOG(TRACE) << "\n";
                }
                buff[buffSize++] = '+';
                counter = endPtr - expression - 1;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op + END";
                break;
            }
            case '-': {
                if (buffSize) {
                    if ((buff[buffSize - 1] == '*') ||
                            (buff[buffSize - 1] == '/')) {
                        while (buffSize) {
                            newExp[*newExpEnd++] = buff[--buffSize];
                            newExp[*newExpEnd++] = ' ';
                        }
                    }
                }
                if (endPtr - expression >= len) {
                    **ERROR_CODE = 3;
                    free(newExp);
                    free(buff);
                    return 0;
                }
                number = strtoll(endPtr + 1, &endPtr, 10);
                lltoa(number, &newExp, newExpEnd, &newExpLen);
                if (VLOG_IS_ON(2)) { //was changed
                    for (i = 0; i < *newExpEnd - 1; i++) {
                        LOG(TRACE) << newExp[i];
                    }
                    LOG(TRACE) << "\n";
                }
                buff[buffSize++] = '-';
                counter = endPtr - expression - 1;
                break;
            }
        }
    }
    while (buffSize) {
        newExp[*newExpEnd++] = buff[--buffSize];
        newExp[*newExpEnd++] = ' ';
    }
    return newExp;
}
