#ifndef _012_CALC_H
#define _012_CALC_H

void lltoa(double num, char **expr, long long *buff, long long *len, int *CALC_ERROR_CODE);
void exptoa(char *tmpExression, char **newExp, long long *newExpEnd, long long *newExpLen, int *ERROR_CODE);
double calc(const char *expression, long long len, char *convertedExpr, int *ERROR_CODE);
char * convertToPolishForm(const char *expression, char *_newExp, long long len, long long *newExpEnd, char **endPtr, int *ERROR_CODE);
char * bracketsConvert(char *tmpPtr, char *newExp, long long *right, long long *newExpEnd, int *ERROR_CODE);

#endif
