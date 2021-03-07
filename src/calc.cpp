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

    // newExp = (char*)malloc(len * sizeof(char));
    // if (!newExp) {
    //     *ERROR_CODE = 2;
    //     free(newExp);
    //     return 0;
    // }

    // if (!bracketsStatus) {
    //     //Копирование const выражения в новую переменную
    //     tmpPtr = expression;
    //     // Функция подсчета выражений в скобках, вызывается рекурсивно
    //     newExp = bracketsConvert(&tmpPtr, newExp, len - 1, newExpEnd, ERROR_CODE);
    // }

    // newExp = convertToPolishForm(expression, NULL, len, &newExpEnd, &endPtr, &CALC_ERROR_CODE);
    // if (CALC_ERROR_CODE) {
    //     *ERROR_CODE = 3;
    //     free(newExp);
    //     return 0;
    // }
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
                insertInd(&node, buffSize++, temp, &CALC_ERROR_CODE);
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
                PrintList(&node, &CALC_ERROR_CODE);
                temp = popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                if(VLOG_IS_ON(2)) LOG(TRACE) << "tempFirst: " << temp;
                PrintList(&node, &CALC_ERROR_CODE);
                temp -= popInd(&node, --buffSize, &CALC_ERROR_CODE);
                if (CALC_ERROR_CODE) {
                    *ERROR_CODE = CALC_ERROR_CODE;
                    free(newExp);
                    listTrash(&node);
                    return 0;
                }
                if(VLOG_IS_ON(2)) LOG(TRACE) << "tempSecond: " << temp;
                insertInd(&node, buffSize++, abs(temp), &CALC_ERROR_CODE);
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

// void lltoa(long long num, char **expr, long long *buff, long long *len, int *CALC_ERROR_CODE) {
//     long long i, j, tmp;
//     i = *buff;
//     while (num) {
//         tmp = num % 10;
//         if (*buff + 1 > *len) {
//             *expr = (char*)realloc(*expr, (*buff + 10) * sizeof(char));
//             *len += 10;
//         }
//         (*expr)[*buff] = tmp + '0';
//         *buff += 1;
//         num = num / 10;
//     }
//     j = *buff - 1;
//     while (i < j) {
//         tmp = (*expr)[i];
//         (*expr)[i] = (*expr)[j];
//         (*expr)[j] = tmp;
//         ++i;
//         --j;
//     }
//     if(VLOG_IS_ON(2)) LOG(TRACE) << "--lltoa-- long long END\n";
// }


void lltoa(double num, char **expr, long long *buff, long long *len, int *ERROR_CODE) {
    if(VLOG_IS_ON(2)) LOG(TRACE) << "input in lltoa, buff: " << (*buff) << ", len: " << (*len) <<", num: " << num << "\n";
    long long i, j, tmp;
    long long nAfterDot = 4; //цифры после точки с запятой

    long long whole = floor(num);
    long long fractional = ((num - floor(num)) * pow(10, nAfterDot));

    long long rateWhole = ((!whole) ? 1 : (floor(log10(whole)) + 1));
    long long rateFractional = ((!fractional) ? 1 : (floor(log10(fractional)) + 1));
    if(VLOG_IS_ON(3)) LOG(TRACE) << "rateWhole: " << rateWhole << "\nrateFract: " << rateFractional << "\n";
    if ((!expr) || (!buff) || (!len)) {
        *ERROR_CODE = 2;
        return;
    }
    while(rateWhole) {
        tmp = whole / pow(10, --rateWhole);
        if (*buff + 2 > *len) {
            *expr = (char*)realloc(*expr, (*buff + 10) * sizeof(char));
            *len += 10;
        }
        (*expr)[*buff] = tmp + '0';
        *buff += 1;
        whole = whole % ((long long)(pow(10, rateWhole)));
    }

    (*expr)[*buff] = '.';
    *buff += 1;

    while(rateFractional) {
        tmp = whole / pow(10, --rateFractional);
        if (*buff + 2 > *len) {
            *expr = (char*)realloc(*expr, (*buff + 10) * sizeof(char));
            *len += 10;
        }
        (*expr)[*buff] = tmp + '0';
        *buff += 1;
        whole = whole % ((long long)(pow(10, rateFractional)));
    }

    (*expr)[*buff] = ' ';
    *buff += 1;

    if(VLOG_IS_ON(2)) LOG(TRACE) << "--lltoa-- double END\n";
}

// char * bracketsConvert(char *tmpPtr, char *newExp, long long *right, long long *newExpEnd, int *ERROR_CODE) {
//     int bracketsCount{0}, i{0}, j{0}, flag{0}, bracketsMax{0};
//     for (; i < right; i++) {
//         if (tmpPtr[i] == '(') {
//             if (!flag) flag = i;
//             bracketsCount++;
//             if (bracketsCount > bracketsMax) {
//                 bracketsMax = bracketsCount;
//             }
//         } else if (tmpPtr[i] == ')') {
//             if (!--bracketsCount) {
//                 if (!VLOG_IS_ON(2)) printf("[bracketsConvert]: endPtr: %.*s", i - flag - 1, tmpPtr);
//                 flag = 0;
//                 *right = i - 1; //Присваиваем правой границе индекс последней закрывающей скобки
//                 if (bracketsMax == 1) { // Если существует 1 открывающая и 1 закрывающая, то необходимо посчитать выражение
//                     const char *tmpExpression = tmpPtr;
//                     // tmpPtr = calc(tmpExpression, *right, ERROR_CODE); //convertToPolishForm
//                     return tmpPtr;
//                 } else {
//                     tmpPtr += flag;
//                     return bracketsConvert(expression, tmpPtr, newExp, right, newExpEnd, ERROR_CODE);
//                 }
//             }
//         }
//     }
//     return 0;
// }

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
    newExpLen = len;

    // //Копирование const выражения в новую переменную
    // tmpPtr = expression;
    // // Функция подсчета выражений в скобках, вызывается рекурсивно
    // newExp = bracketsConvert(&tmpPtr, newExp, len - 1, newExpEnd, ERROR_CODE);

    // tmpP = *(*endPtr + 1);
    // if (tmpP == '(') {
    //     //Перевести выражние после скобок и добавить в конец
    //     *endPtr += 2;
    //     exptoa(convertToPolishForm(expression, NULL, len, 0, endPtr, ERROR_CODE), &newExp, newExpEnd, &newExpLen, ERROR_CODE);
    //
    // } else if(**endPtr == ')') {
    //     *endPtr++;
    //     while (buffSize) {
    //         if (((*newExpEnd) + 2) > newExpLen) {
    //             newExp = (char*)realloc(newExp, (newExpLen + 10) * sizeof(char));
    //             newExpLen += 10;
    //         }
    //         newExp[(*newExpEnd)++] = buff[--buffSize];
    //         newExp[(*newExpEnd)++] = ' ';
    //     }
    //     return newExp;
    // } else {
    //     number = strtod(*endPtr + 1, endPtr);
    //     lltoa(number, &newExp, newExpEnd, &newExpLen, ERROR_CODE);
    //     if (*ERROR_CODE) {
    //       return NULL;
    //     }
    // }

    // number = strtod(expression, endPtr);
    // if (VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << *endPtr;
    // if (VLOG_IS_ON(2)) LOG(TRACE) << "number: " << number;
    // if (VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
    // if (VLOG_IS_ON(2)) LOG(TRACE) << "newExpEnd: " << *newExpEnd;
    //
    //
    // lltoa(number, &newExp, newExpEnd, &newExpLen, ERROR_CODE);
    // if (*ERROR_CODE) {
    //   return NULL;
    // }
    // if (VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
    // if (VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << *endPtr;

    //исправить realloc, избавиться от копирования в переводе выражения в скобках

    // if (!*endPtr) {
    //      counter = 0;
    // } else {
    //     counter = *endPtr - expression;
    // }
    //
    // *endPtr = expression;

    while (counter < len) {
        switch(expression[counter]) {
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
                lltoa(number, &newExp, newExpEnd, &newExpLen, ERROR_CODE);
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
                // if(VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
                // if(VLOG_IS_ON(2)) LOG(TRACE) << "newExp after converting: " << newExp;
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
                // exptoa(expressionInBracketsTemp, &newExp, newExpEnd, &newExpLen, ERROR_CODE);
                // if (*ERROR_CODE) {
                //     free(buff);
                //     //Проверяем, выделила ли эта функция память или же другая
                //     if (allocNewExprFlag) {
                //         free(newExp);
                //         allocNewExprFlag = 0;
                //     }
                //     return NULL;
                // }
                // free(expressionInBracketsTemp);

                // if(VLOG_IS_ON(2)) LOG(TRACE) << "counter: " << counter;
                // if(VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << endPtr;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op ( END";
                break;
            }
            case ')': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op ) BEGIN";
                if(VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;

                *endPtr += 1;
                while (buffSize) {
                    if (((*newExpEnd) + 2) > newExpLen) {
                        newExp = (char*)realloc(newExp, (newExpLen + 10) * sizeof(char));
                        if (!newExp) {
                            free(buff);
                            //Проверяем, выделила ли эта функция память или же другая
                            if (!_newExp) {
                                free(newExp);
                            }
                            return NULL;
                        }
                        memset(newExp + newExpLen, 0, 10 * sizeof(char));
                        newExpLen += 10;
                    }
                    newExp[(*newExpEnd)++] = buff[--buffSize];
                    newExp[(*newExpEnd)++] = ' ';
                }
                if(VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << *endPtr;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op ) END";
                return newExp;
            }
            case '*': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op * BEGIN";
                if(VLOG_IS_ON(2)) LOG(TRACE) << "newExp: " << newExp;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "expression: " << expression;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "endPtr: " << *endPtr;

                if (*endPtr - expression + 1 >= len) {
                    *ERROR_CODE = 3;
                    free(buff);
                    //Проверяем, выделила ли эта функция память или же другая
                    if (!_newExp) {
                        free(newExp);
                    }
                    return NULL;
                }

                if (VLOG_IS_ON(2)) {
                    for (i = 0; i < *newExpEnd - 1; i++) {
                        LOG(TRACE) << newExp[i];
                    }
                    LOG(TRACE) << "\n";
                }
                buff[buffSize++] = '*';

                *endPtr += 1;
                counter = *endPtr - expression;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op * END";
                break;
            }
            case '/': {
                if (*endPtr - expression + 1 >= len) {
                    *ERROR_CODE = 3;
                    free(buff);
                    //Проверяем, выделила ли эта функция память или же другая
                    if (!_newExp) {
                        free(newExp);
                    }
                    return NULL;
                }

                if (VLOG_IS_ON(2)) LOG(TRACE) << newExp;
                buff[buffSize++] = '/';
                *endPtr += 1;
                counter = *endPtr - expression;
                break;
            }
            case '+': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op + BEGIN";
                if (buffSize) {
                    if ((buff[buffSize - 1] == '*') ||
                            (buff[buffSize - 1] == '/') ||
                            (buff[buffSize - 1] == '-')) {
                        while (buffSize) {
                            if (((*newExpEnd) + 2) > newExpLen) {
                                newExp = (char*)realloc(newExp, (newExpLen + 10) * sizeof(char));
                                if (!newExp) {
                                    free(buff);
                                    //Проверяем, выделила ли эта функция память или же другая
                                    if (!_newExp) {
                                        free(newExp);
                                    }
                                    return NULL;
                                }
                                memset(newExp + newExpLen, 0, 10 * sizeof(char));
                                newExpLen += 10;
                            }
                            newExp[(*newExpEnd)++] = buff[--buffSize];
                            newExp[(*newExpEnd)++] = ' ';
                        }
                    }
                }
                if (*endPtr - expression + 1 >= len) {
                    *ERROR_CODE = 3;
                    free(buff);
                    //Проверяем, выделила ли эта функция память или же другая
                    if (!_newExp) {
                        free(newExp);
                    }
                    return NULL;
                }
                if (VLOG_IS_ON(2)) LOG(TRACE) << newExp;
                buff[buffSize++] = '+';
                *endPtr += 1;
                counter = *endPtr - expression;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "counter: " << counter;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op + END";
                break;
            }
            case '-': {
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op - BEGIN";
                if (buffSize) {
                    if ((buff[buffSize - 1] == '*') ||
                            (buff[buffSize - 1] == '/')) {
                        while (buffSize) {
                            if (((*newExpEnd) + 2) > newExpLen) {
                                newExp = (char*)realloc(newExp, (newExpLen + 10) * sizeof(char));
                                if (!newExp) {
                                    free(buff);
                                    //Проверяем, выделила ли эта функция память или же другая
                                    if (!_newExp) {
                                        free(newExp);
                                    }
                                    return NULL;
                                }
                                memset(newExp + newExpLen, 0, 10 * sizeof(char));
                                newExpLen += 10;
                            }
                            newExp[(*newExpEnd)++] = buff[--buffSize];
                            newExp[(*newExpEnd)++] = ' ';
                        }
                    }
                }
                if (*endPtr - expression + 1 >= len) {
                    *ERROR_CODE = 3;
                    free(buff);
                    //Проверяем, выделила ли эта функция память или же другая
                    if (!_newExp) {
                        free(newExp);
                    }
                    return NULL;
                }
                if (VLOG_IS_ON(2)) LOG(TRACE) << newExp;
                buff[buffSize++] = '-';
                *endPtr += 1;
                counter = *endPtr - expression;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "counter: " << counter;
                if(VLOG_IS_ON(2)) LOG(TRACE) << "op - END";
                break;
            }
            default: if (VLOG_IS_ON(2)) LOG(TRACE) << "Error in Case in convertToPolishForm function";
        }
    }
    if (VLOG_IS_ON(2)) LOG(TRACE) << "Buff: " << buff;
    if (VLOG_IS_ON(2)) LOG(TRACE) << "buffSize: " << buffSize;
    while (buffSize) {
        if (((*newExpEnd) + 2) > newExpLen) {
            newExp = (char*)realloc(newExp, (newExpLen + 10) * sizeof(char));
            if (!newExp) {
                free(buff);
                //Проверяем, выделила ли эта функция память или же другая
                if (!_newExp) {
                    free(newExp);
                }
                return NULL;
            }
            memset(newExp + newExpLen, 0, 10 * sizeof(char));
            newExpLen += 10;
        }
        newExp[(*newExpEnd)++] = buff[--buffSize];
        newExp[(*newExpEnd)++] = ' ';
    }
    memset(newExp + *newExpEnd, 0, (newExpLen - *newExpEnd) * sizeof(char));
    return newExp;
}
