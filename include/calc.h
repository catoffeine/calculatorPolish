#ifndef _012_CALC_H
#define _012_CALC_H

void lltoa(double num, char **expr, long long *buff, long long *len, int *CALC_ERROR_CODE);
void lltoa(long long num, char **expr, long long *buff, long long *len, int *CALC_ERROR_CODE);
double calc(const char *expression, long long len, int *ERROR_CODE, int bracketsStatus = 0);
char * convertToPolishForm(const char *expression, char *newExp, long long len, long long *newExpEnd, int *ERROR_CODE);
char * bracketsConvert(const char *expressionchar, char *tmpPtr, char *newExp, long long *right, long long *newExpEnd, int *ERROR_CODE);

#endif
