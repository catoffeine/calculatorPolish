#include <iostream>
#include <list.h>
#include <calc.h>
#include <math.h>
#include <easylogging++.h>
#include <errno.h>
#include <string.h>

double calc(const char *expression, long long len, char *newExp, int *ERROR_CODE) {
    int CALC_ERROR_CODE{0};
    long long buffSize{0}, i{0}, newExpEnd{0};
    char *endPtr{NULL};
    double number{0};
    double result{0}, temp{0};
    Node *node{NULL};
    char *tmpPtr{NULL};
    newExpEnd = strlen(newExp);
    ++newExpEnd;



    if(VLOG_IS_ON(2)) LOG(TRACE) << "going to calculations";
    for (i = 0; i < newExpEnd; i++) {
        switch(newExp[i]) {
            case '.': {
                continue;
            }
            case '*': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op * BEGIN | len: " << listLen(node);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "buffSize * BEGIN | buffSize: " << buffSize;
                temp = popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                temp *= popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                insertInd(&node, buffSize++, temp, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                i++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op * END | len: " << listLen(node);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "buffSize * END | buffSize: " << buffSize;
                continue;
            }
            case '/': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op / BEGIN | len: " << listLen(node);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "buffSize / BEGIN | buffSize: " << buffSize;
                temp = popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }

                temp /= popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                insertInd(&node, buffSize++, 1 / temp, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                i++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op / END | len: " << listLen(node);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "buffSize / END | buffSize: " << buffSize;
                continue;
            }
            case '+': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op + BEGIN | len: " << listLen(node);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "buffSize + BEGIN | buffSize: " << buffSize;
                temp = popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                temp += popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                insertInd(&node, buffSize++, temp, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                i++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "buffSize + END | buffSize: " << buffSize;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op + END | len: " << listLen(node);
                continue;
            }
            case '-': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op - BEGIN | len: " << listLen(node);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "buffSize - BEGIN | buffSize: " << buffSize;
                temp = popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }

                temp -= popInd(&node, --buffSize, &CALC_ERROR_CODE);
                temp *= -1;

                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                insertInd(&node, buffSize++, temp, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                i++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "calc op - END | len: " << listLen(node);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "buffSize - END | buffSize: " << buffSize;
                continue;
            }

            case ' ': {
                i++;
                continue;
            }
        }
        if(VLOG_IS_ON(2)) LOG(TRACE) << "NOT AN OPERATION ... BEGIN | len: " << listLen(node);
        number = strtod(newExp + i, &endPtr);
        if(VLOG_IS_ON(2)) LOG(TRACE) << "NOT AN OPERATION ... END | number: " << number << " | newExp: \"" << newExp << "\" | newExp + i: \"" << newExp + i << "\" | i: " << i << " | len: " << listLen(node);
        insertInd(&node, buffSize++, number, &CALC_ERROR_CODE);
        if (CALC_ERROR_CODE) {
            *ERROR_CODE = CALC_ERROR_CODE;
            free(newExp);
            listTrash(&node);
            return 0;
        }
        i = endPtr - newExp;
    }
    if(VLOG_IS_ON(2)) LOG(TRACE) << "AFTER CALCULATIONS | len: " << listLen(node);
    result = popInd(&node, 0, &CALC_ERROR_CODE);
    listTrash(&node);
    free(newExp);
    return result;
}

void dtoa(double num, char **expr, long long *bufflen, long long *len, int *ERROR_CODE) {
    if(VLOG_IS_ON(2)) LOG(TRACE) << "input in dtoa, bufflen: " << (*bufflen) << ", len: " << (*len) <<", num: " << num << "\n";
    long long i, j, tmp;
    long long nAfterDot = 4; //цифры после точки с запятой

    long long whole = floor(num);
    long long fractional = ((num - floor(num)) * pow(10, nAfterDot));
    if(VLOG_IS_ON(3)) LOG(TRACE) << "the whole part: " << whole << "\nthe fractional part: " << fractional << "\n";
    long long rateWhole = ((!whole) ? 1 : (floor(log10(whole)) + 1));
    long long rateFractional = ((!fractional) ? 1 : (floor(log10(fractional)) + 1));
    if(VLOG_IS_ON(3)) LOG(TRACE) << "rateWhole: " << rateWhole << "\nrateFract: " << rateFractional << "\n";
    if ((!expr) || (!bufflen) || (!len)) {
        *ERROR_CODE = 2;
        return;
    }
    while(rateWhole) {
        tmp = whole / pow(10, --rateWhole);
        if (*bufflen + 2 > *len) {
            *expr = (char*)realloc(*expr, (*bufflen + 10) * sizeof(char));
            *len += 10;
        }
        (*expr)[*bufflen] = tmp + '0';
        *bufflen += 1;
        whole = whole % ((long long)(pow(10, rateWhole)));
    }

    (*expr)[*bufflen] = '.';
    *bufflen += 1;

    while(rateFractional) {
        tmp = fractional / pow(10, --rateFractional);
        if (*bufflen + 2 > *len) {
            *expr = (char*)realloc(*expr, (*bufflen + 10) * sizeof(char));
            *len += 10;
        }
        (*expr)[*bufflen] = tmp + '0';
        *bufflen += 1;
        fractional = fractional % ((long long)(pow(10, rateFractional)));
    }

    (*expr)[*bufflen] = ' ';
    *bufflen += 1;

    if(VLOG_IS_ON(2)) LOG(TRACE) << "--dtoa-- double END\n";
}

void exptoa(char *tmpExression, char **newExp, long long *newExpEnd, long long *newExpLen, int *ERROR_CODE) {
    if (VLOG_IS_ON(2)) LOG(TRACE) << "exptoa BEGIN----------------";
    long long length = strlen(tmpExression);
    long long i{0};
    if (VLOG_IS_ON(2)) LOG(TRACE) << "length of tmpExression: " << length;
    if (*newExpEnd + length + 2 > *newExpLen) {
        *newExp = (char*)realloc(*newExp, (*newExpEnd + length + 2) * sizeof(char));
        if (!newExp) {
            *ERROR_CODE = 2;
            return;
        }
        *newExpLen = *newExpEnd + length + 2;
    }

    for (; i < length; i++) {
        (*newExp)[(*newExpEnd)++] = tmpExression[i];
    }

    (*newExp)[(*newExpEnd)++] = ' ';
    if (VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << *newExp;
    if (VLOG_IS_ON(2)) LOG(TRACE) << "exptoa END----------------";
}

char * convertToPolishForm(const char *expression, char *_newExp,
        long long len, long long *newExpEnd, char **endPtr, int *ERROR_CODE) {

    if(VLOG_IS_ON(2)) LOG(TRACE) << "convertToPolishForm BEGIN ----------";
    long long buffSize{0};
    long long newExpLen{0}, i{0};
    double number{0};
    long long counter{0};
    char *buff{NULL};
    char *expressionInBracketsTemp{0};
    int allocNewExprFlag{0};
    char *newExp{0};
    long long countVarOccurrences{0}, varLen{0};

    if (!expression) {
        *ERROR_CODE = 1;
        return 0;
    }


    //Проверяем, нужно ли нам создавать новую польскую форму или использовать переданную
    if (_newExp) {
        newExp = _newExp;
    } else {
        newExp = (char*)malloc((len) * sizeof(char));
        memset(newExp, 0, len * sizeof(char));
        if (!newExp) {
            *ERROR_CODE = 2;
            return 0;
        }
    }

    // Выделение памяти под массив операций
    buff = (char*)malloc(len * sizeof(char));
    if (!buff) {
        *ERROR_CODE = 2;
        free(buff);
        //Проверяем, выделила ли эта функция память или же другая
        if (!_newExp) {
            free(newExp);
        }
        return 0;
    }
    memset(buff, 0, len * sizeof(char));

    polishFormExpression *polishNode = (polishFormExpression*)malloc(sizeof(polishFormExpression));

    if (!polishNode) {
        *ERROR_CODE = 2;
        free(buff);
        //Проверяем, выделила ли эта функция память или же другая
        if (!_newExp) {
            free(newExp);
        }
        return NULL;
    }

    newExpLen = len;

    while (counter < len) {
        switch(expression[counter]) {
            case '=':
            case ' ': {
                if(VLOG_IS_ON(2))  LOG(TRACE) << "INPUT IN SKIPPING";
                counter++;
                *endPtr += 1;
                break;
            };
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                if(VLOG_IS_ON(2))  LOG(TRACE) << "NUMBER CONVERTING ----- BEGIN";
                number = strtod(expression + counter, endPtr);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "Errno: " << errno;
                if (VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << *endPtr;
                if (VLOG_IS_ON(2)) LOG(TRACE) << "number: " << number;
                if (VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
                if (VLOG_IS_ON(2)) LOG(TRACE) << "newExpEnd: " << *newExpEnd;

                dtoa(number, &newExp, newExpEnd, &newExpLen, ERROR_CODE);
                if (*ERROR_CODE) {
                    free(buff);
                    //Проверяем, выделила ли эта функция память или же другая
                    if (!_newExp) {
                        free(newExp);
                    }
                    return NULL;
                }
                counter = *endPtr - expression;
                if (VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
                if (VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << *endPtr;
                if(VLOG_IS_ON(2))  LOG(TRACE) << "NUMBER CONVERTING ----- END";
                break;
            }

            case '(': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op ( BEGIN";
                if(VLOG_IS_ON(2)) LOG(TRACE) << "ERROR: INPUT IN (";
                if(VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << *endPtr;
                *endPtr += 1;
                const char * bracketsExp = *endPtr;
                long long brNewExpEnd{*newExpEnd};
                _newExp = newExp;
                newExp = convertToPolishForm(bracketsExp, _newExp, strlen(bracketsExp), &brNewExpEnd, endPtr, ERROR_CODE);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "endPtr after recursive involve: " << *endPtr;
                if (*ERROR_CODE) {
                    free(buff);
                    //Проверяем, выделила ли эта функция память или же другая
                    if (!_newExp) {
                        free(newExp);
                    }
                    return NULL;
                }
                *newExpEnd = brNewExpEnd;
                counter = *endPtr - expression;
                newExpLen = strlen(newExp);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "counter: " << counter;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "len: " << len;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "newExpLen: " << newExpLen;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op ( END";
                break;
            }
            case ')': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op ) BEGIN";
                if(VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
                *endPtr += 1;
                buff = freeBuffSizePolish(buff, &buffSize, newExpEnd, &newExpLen, &newExp, _newExp);
                if (!buff) {
                    *ERROR_CODE = 3;
                    return NULL;
                }
                if(VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << *endPtr;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op ) END";
                return newExp;
            }
            case '*': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op * BEGIN";
                buff = addSignPolish(endPtr, buff, &buffSize, '*');
                *ERROR_CODE = checkOutOfBounds(expression, endPtr, len, buff, _newExp, newExp);
                if(VLOG_IS_ON(2)) LOG(TRACE) << "ERROR_CODE is " << *ERROR_CODE;
                if (*ERROR_CODE) return NULL;
                counter = *endPtr - expression;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op * END";
                break;
            }
            case '/': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op / START";
                buff = addSignPolish(endPtr, buff, &buffSize, '/');
                *ERROR_CODE = checkOutOfBounds(expression, endPtr, len, buff, _newExp, newExp);
                if (*ERROR_CODE) return NULL;
                counter = *endPtr - expression;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op / END";
                break;
            }
            case '+': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op + BEGIN";
                buff = polishPlusOp(buff, &buffSize, newExpEnd, &newExpLen, &newExp, _newExp);
                if (!buff) {
                    *ERROR_CODE = 3;
                    return NULL;
                }
                *ERROR_CODE = checkOutOfBounds(expression, endPtr, len, buff, _newExp, newExp);
                if (*ERROR_CODE) return NULL;
                buff = addSignPolish(endPtr, buff, &buffSize, '+');
                counter = *endPtr - expression;

                if(VLOG_IS_ON(2)) LOG(TRACE) << "op + END";
                break;
            }
            case '-': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op - BEGIN";
                buff = polishMinusOp(buff, &buffSize, newExpEnd, &newExpLen, &newExp, _newExp);
                if (!buff) {
                    *ERROR_CODE = 3;
                    return NULL;
                }
                *ERROR_CODE = checkOutOfBounds(expression, endPtr, len, buff, _newExp, newExp);
                if (*ERROR_CODE) return NULL;
                buff = addSignPolish(endPtr, buff, &buffSize, '-');
                counter = *endPtr - expression;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op - END";
                break;
            }
            default: {
                if (((long long)expression[counter] >= 'A' && (long long)expression[counter] <= 'Z') ||
            ((long long)expression[counter] >= 'a' && (long long)expression[counter] <= 'z')) {

                long long temp{counter};
                while (((long long)expression[temp] >= 'A' && (long long)expression[temp] <= 'Z') ||
            ((long long)expression[temp] >= 'a' && (long long)expression[temp] <= 'z')) {
                    temp++;
                }

                if (!polishNode->name) {
                    polishNode->name = (char*)malloc((temp-counter+1) * sizeof(char));
                    if (!polishNode->name) {
                        *ERROR_CODE = 2;
                        free(buff);
                        //Проверяем, выделила ли эта функция память или же другая
                        if (!_newExp) {
                            free(newExp);
                        }
                        return NULL;
                    }
                    while (((long long)expression[temp] >= 'A' && (long long)expression[temp] <= 'Z') ||
                ((long long)expression[temp] >= 'a' && (long long)expression[temp] <= 'z')) {
                        (polishNode->name)[counter] = expression[counter];
                        counter++;
                    }
                    (polishNode->name)[counter] = 0;
                } else {
                    if(!polishNode->varName) {
                        polishNode->varName = (char*)malloc((temp-counter+1) * sizeof(char));
                        varLen = temp-counter+1;
                        if (!polishNode->varName) {
                            *ERROR_CODE = 2;
                            free(buff);
                            if(!_newExp){
                                free(newExp);
                            }
                        }
                        while (((long long)expression[temp] >= 'A' && (long long)expression[temp] <= 'Z') ||
                    ((long long)expression[temp] >= 'a' && (long long)expression[temp] <= 'z')) {
                            (polishNode->varName)[counter] = expression[counter];
                            counter++;
                        }

                        countVarOccurrences = findCountVarOccurrences(expression, len, varLen, polishNode->varName);
                        if (countVarOccurrences == -1) {
                            *ERROR_CODE = 12; //в названии переменных допущены ошибки
                            free(buff);
                            if(!_newExp){
                                free(newExp);
                            }
                            return NULL;
                        }
                    } else {
                        for (i = 0; i < varLen - 1; i++) {
                            if (*(*endPtr+i) == 0) break;
                            if (*newExpEnd + 2 >= newExpLen) {
                                newExp = (char*)realloc(newExp, (newExpLen + 10) * sizeof(char));
                                if (!newExp) {
                                    *ERROR_CODE = 2; //Ошибка выделения/перевыделения памяти
                                    free(buff);
                                    if(!_newExp){
                                        free(newExp);
                                    }
                                    return NULL;
                                }
                                newExpLen += 10;
                            }
                            newExp[(*newExpEnd)++] = *(*endPtr+i);
                        }
                        newExp[(*newExpEnd)++] == ' ';
                        counter = *endPtr - expression;
                    }
                }



                // while(expression[counter] != '(') {
                //     if (exprssion[counter] == ' ') {
                //         counter++;
                //         continue;
                //     }
                //     (polishNode->name)[counter] = expession[counter];
                //     counter++;
                // }

                break;
            }
                if (VLOG_IS_ON(2)) LOG(TRACE) << "Error in Case in convertToPolishForm function";
            }
        }
    }
    if (VLOG_IS_ON(2)) LOG(TRACE) << "Buff: " << buff;
    if (VLOG_IS_ON(2)) LOG(TRACE) << "buffSize: " << buffSize;
    buff = freeBuffSizePolish(buff, &buffSize, newExpEnd, &newExpLen, &newExp, _newExp);
    if (!buff) {
        *ERROR_CODE = 3;
        return NULL;
    }

    polishNode->str = newExp;
    polishNode->bufflen = newExpLen;
    //return polishNode
    return newExp;
}

//ERROR CHECK FUNCTIONS:

int checkOutOfBounds(const char * expression, char **endPtr, long long len, char * buff, char * _newExp, char * newExp) {
    if(VLOG_IS_ON(2)) LOG(TRACE) << "len: " << len;
    if(VLOG_IS_ON(2)) LOG(TRACE) << "*endPtr - expression: " << *endPtr - expression;
    if (*endPtr - expression + 1 > len) {
        free(buff);
        //Проверяем, выделила ли эта функция память или же другая
        if (!_newExp) {
            free(newExp);
        }
        return 3;
    }
    return 0;
}


//OPERATIONS FUNCTIONS:

char * addSignPolish(char **endPtr, char * buff, long long * buffSize, char substS) {
    if(VLOG_IS_ON(2)) LOG(TRACE) << "addSignPolish BEGIN";
    buff[(*buffSize)++] = substS;
    *endPtr += 1;
    if(VLOG_IS_ON(2)) LOG(TRACE) << "addSignPolish END";
    return buff;
}

char * polishPlusOp(char * buff, long long *buffSize, long long *newExpEnd, long long *newExpLen, char **newExp, char *_newExp) {
    if (buffSize) {
        if ((buff[(*buffSize) - 1] == '*') ||
                (buff[(*buffSize) - 1] == '/') ||
                (buff[(*buffSize) - 1] == '-')) {
            while (*buffSize) {
                if (((*newExpEnd) + 2) > *newExpLen) {
                    *newExp = (char*)realloc(*newExp, (*newExpLen + 10) * sizeof(char));
                    if (!*newExp) {
                        free(buff);
                        //Проверяем, выделила ли эта функция память или же другая
                        if (!_newExp) {
                            free(*newExp);
                        }
                        return NULL;
                    }
                    memset(*newExp + *newExpLen, 0, 10 * sizeof(char));
                    *newExpLen += 10;
                }
                (*newExp)[(*newExpEnd)++] = buff[--(*buffSize)];
                (*newExp)[(*newExpEnd)++] = ' ';
            }
        }
    }
    return buff;
}

char * polishMinusOp(char * buff, long long *buffSize, long long *newExpEnd, long long *newExpLen, char **newExp, char *_newExp) {
    if (buffSize) {
        if ((buff[(*buffSize) - 1] == '*') ||
                (buff[(*buffSize) - 1] == '/')) {
            while (buffSize) {
                if (((*newExpEnd) + 2) > *newExpLen) {
                    *newExp = (char*)realloc(*newExp, (*newExpLen + 10) * sizeof(char));
                    if (!(*newExp)) {
                        free(buff);
                        //Проверяем, выделила ли эта функция память или же другая
                        if (!_newExp) {
                            free(*newExp);
                        }
                        return NULL;
                    }
                    memset(*newExp + *newExpLen, 0, 10 * sizeof(char));
                    *newExpLen += 10;
                }
                (*newExp)[(*newExpEnd)++] = buff[--(*buffSize)];
                (*newExp)[(*newExpEnd)++] = ' ';
            }
        }
    }
    return buff;
}

char * freeBuffSizePolish(char *buff, long long *buffSize, long long *newExpEnd, long long *newExpLen, char **newExp, char *_newExp) {
    while (*buffSize) {
        if (((*newExpEnd) + 2) > *newExpLen) {
            *newExp = (char*)realloc(*newExp, (*newExpLen + 10) * sizeof(char));
            if (!*newExp) {
                free(buff);
                //Проверяем, выделила ли эта функция память или же другая
                if (!_newExp) {
                    free(*newExp);
                }
                return NULL;
            }
            memset(*newExp + *newExpLen, 0, 10 * sizeof(char));
            *newExpLen += 10;
        }
        (*newExp)[(*newExpEnd)++] = buff[--(*buffSize)];
        (*newExp)[(*newExpEnd)++] = ' ';
    }
    memset(*newExp + *newExpEnd, 0, (*newExpLen - *newExpEnd) * sizeof(char));
    return buff;
}

long long findCountVarOccurrences(const char *expression, long long arrLen, long long varLen, char *var, int *ERROR_CODE) {
    long long i{0}, j{0};
    long long count{0};

    for (; i < arrLen; i++) if (expression[i] == '=') break;

    for (; i < arrLen; i++) {
        if (expression[i] == ' ') continue;
        if (expression[i] == var[j]) {
            for (; j < varLen-1; j++) {

                if (var[j] == 0) count++;

                if (expression[i++] != var[j++]) {
                    *ERROR_CODE = -1;
                    return -1;
                }
            }
            if ((j >= varLen-1) && (var[j] != 0)) count++;
            j = 0;
        }
    }
    return count;
}



char * varSubstitution(const char *expression, double number, long long len, int *ERROR_CODE) {

    char * newExp{0};
    long long begin{0}, i{0}, j{0}, brackets{0}, additingCount{0};
    char variable{0};
    //количество чисел после запятой
    long long nAfterDot = 4;
    //дробная часть
    long long fractional = ((number - floor(number)) * pow(10, nAfterDot));
    //длина числа
    long long numbCount = (!floor(number) ? 1 : floor(log10(floor(number))) + 1) +
    ((!fractional) ? 1 : (floor(log10(fractional)) + 1));

    for (; i < len; i++) {
        if (expression[i] == '=') {
            begin = i + 1;
            continue;
        }
        if (brackets) {
            if (expression[i] == ')') {brackets = -1; continue;}
            if (expression[i] == ' ') continue;
            variable = expression[i];
        }
        if (expression[i] == '(' && brackets != -1) {
            brackets = 1;
            continue;
        }
        if (expression[i] == variable) {
            additingCount += numbCount;
            continue;
        }
    }
    newExp = (char*)malloc((len + additingCount) * sizeof(char));
    if (!newExp) {
        *ERROR_CODE = 2;
        return NULL;
    }
    for (i = begin; i < len; i++) {
        if (expression[i] == variable) {
            sprintf(newExp + i + j, "%lf", number);
            j += numbCount;
            memset(newExp + i + j, 0, (len + additingCount - i - j) * sizeof(char));
        }
        newExp[j++] = expression[i];
    }
    return newExp;
}

void checkIfExpressionCorrect(const char * expression, long long len, int *ERROR_CODE) {
    if(VLOG_IS_ON(2)) LOG(TRACE) << "checkIfExpressionCorrect BEGIN";
    if(VLOG_IS_ON(2)) LOG(TRACE) << "len = " << len;
    long long bracketsCount{0}, equalCount{0};
    long long i{0};
    char sign{0};
    int isPrevSign{0}, isInBracketsVar{0}, isOutBracketsVar{0}, isRightBeginEnd{0}, isThereSigns{0};
    long long indexEqual{0};
    int bracketStatus{0}; //Для выражения до '=': 0 - открывающая скобка не найдена, 1 - открывающая найдена, 2 - закрывающая найдена

    for (i = 0; i < len; i++) {
        if (expression[i] == ' ') {
            continue;
        }
        if (expression[i] == '=') {
            equalCount++;
            if(VLOG_IS_ON(2)) LOG(TRACE) << "equalCount: " << equalCount;
            if (equalCount > 1) {
                *ERROR_CODE = 9;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "ERROR_CODE = 9; EXIT of checkIfExpressionCorrect";
                return; //Два или больше знаков равенства в выражении
            }
            indexEqual = i;
        }
    }

    for (i = 0; i < len; i++) {
        switch(expression[i]) {
            case ' ': break;
            case '\0': {
                i = len;
                break;
            }
            case '+':
            case '-':
            case '/':
            case '*': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "SIGN CHECK BEGIN, the sign is " << sign << ", expression[i] is " << expression[i];
                if (isPrevSign) {
                    if (sign == expression[i]) {
                        *ERROR_CODE = 4;
                        if(VLOG_IS_ON(2)) LOG(TRACE) << "ERROR_CODE = 4; EXIT of checkIfExpressionCorrect";
                        return; //Повторение знаков в выражении
                    }
                }
                sign = expression[i];
                isPrevSign = 1;
                isThereSigns = 1;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "SIGN CHECK END " << expression[i];
                break;
            }
            case '(': {
                bracketsCount++;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "bracketsCount++; bracketsCount = " << bracketsCount;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "exprssion[i] == " << expression[i];
                break;
            }
            case ')': {
                bracketsCount--;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "bracketsCount--; bracketsCount = " << bracketsCount;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "exprssion[i] == " << expression[i];
                break;
            }
            default: {
                isPrevSign = 0;
                break;
            }
        }
    }
    if (bracketsCount) {
        *ERROR_CODE = 5;
        if(VLOG_IS_ON(2)) LOG(TRACE) << "ERROR_CODE = 5; EXIT of checkIfExpressionCorrect";
        return; //Несовпадение открывающих и закрыающих скобок
    }
    if(VLOG_IS_ON(2)) LOG(TRACE) << "indexEqual = " << indexEqual;
    if (indexEqual) {
        for (i = indexEqual-1; i >= 0; i--) {
            if(VLOG_IS_ON(2)) LOG(TRACE) << "IndexEqual: expression[i] is " << expression[i];
            switch(expression[i]) {
                case ' ': break;
                case ')': {
                    bracketStatus = 1;
                    break;
                }
                case '(': {
                    bracketStatus = 2;
                    break;
                }
                default: {
                    if(VLOG_IS_ON(2)) LOG(TRACE) << "DEFAULT BEGIN: expression[i] is " << expression[i];
                    if(VLOG_IS_ON(2)) LOG(TRACE) << "bracketStatus is " << bracketStatus;
                    if (!bracketStatus) {
                        *ERROR_CODE = 6;
                        if(VLOG_IS_ON(2)) LOG(TRACE) << "ERROR_CODE = 6; EXIT of checkIfExpressionCorrect";
                        return; //После закрывающей скобки перед равенством есть что-то кроме пробела
                    }
                    if (((long long)expression[i] >= 'A' && (long long)expression[i] <= 'Z') ||
                ((long long)expression[i] >= 'a' && (long long)expression[i] <= 'z')) {
                        if (bracketStatus == 1) {
                            isInBracketsVar = 1;
                        } else {
                            isOutBracketsVar = 1;
                        }
                    } else {
                        *ERROR_CODE = 7;
                        if(VLOG_IS_ON(2)) LOG(TRACE) << "ERROR_CODE = 7; EXIT of checkIfExpressionCorrect";
                        return; //В названии переменной или функции есть недопустимый символ
                    }
                }
            }
        }
        if (!isInBracketsVar || !isOutBracketsVar) {
            *ERROR_CODE = 8;
            if(VLOG_IS_ON(2)) LOG(TRACE) << "ERROR_CODE = 8; EXIT of checkIfExpressionCorrect";
            return; //Не обозначено название фукнкции или название переменной
        }
    }
    i = indexEqual;
    sign = 0;
    while (i < len) {
        switch(expression[i]) {
            case ' ':
            case '=': break;
            case '+':
            case '*':
            case '/':
            case '-': {
                if (!isRightBeginEnd) {
                    *ERROR_CODE = 10; //Выражение начинается или заканчивается знаком
                    return;
                }
                sign = expression[i];
                break;
            }
            default: {
                isRightBeginEnd = 1;
                sign = 0;
                break;
            }
        }
        i++;
    }
    if (sign) {
        *ERROR_CODE = 10; //Выражение начинается или заканчивается знаком
        return;
    }
    if (!isThereSigns && !indexEqual) {
        *ERROR_CODE = 11; //В выражении нет знаков вычисления
        return;
    }


    if(VLOG_IS_ON(2)) LOG(TRACE) << "Expression is correct; EXIT of checkIfExpressionCorrect";
    return; //Выражение корректно
}
