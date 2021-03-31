#ifndef _012_CALC_H
#define _012_CALC_H

struct polishFormExpression {
    char *str;
    long long bufflen;
    char **variables;
    char *name;
    char *varName;
};

//func(tmp,tmp1,tmp2) = tmp1*5

void dtoa(double num, char **expr, long long *bufflen, long long *len, int *CALC_ERROR_CODE);
void exptoa(char *tmpExression, char **newExp, long long *newExpEnd, long long *newExpLen, int *ERROR_CODE);
double calc(const char *expression, long long len, char *convertedExpr, int *ERROR_CODE);
polishFormExpression * convertToPolishForm(const char *expression, char *_newExp, long long len, long long *newExpEnd, char **endPtr, int *ERROR_CODE);
char * bracketsConvert(char *tmpPtr, char *newExp, long long *right, long long *newExpEnd, int *ERROR_CODE);
char * varSubstitution(const char *expression, double number, long long len, int *ERROR_CODE);
long long findCountVarOccurrences(const char *expression, long long arrLen, long long varLen, char *var, int *ERROR_CODE);

int checkOutOfBounds(const char * expression, char **endPtr, long long len, char * buff, char * _newExp, char * newExp);

void checkIfExpressionCorrect(const char * expression, long long len, int *ERROR_CODE);

//Operations in Polish Converting (operations):
char * addSignPolish(char **endPtr, char * buff, long long *buffSize, char substS);
char * polishPlusOp(char * buff, long long *buffSize, long long *newExpEnd, long long *newExpLen, char **newExp, char *_newExp);
char * polishMinusOp(char * buff, long long *buffSize, long long *newExpEnd, long long *newExpLen, char **newExp, char *_newExp);

//Malloc/Free
char * freeBuffSizePolish(char *buff, long long *buffSize, long long *newExpEnd, long long *newExpLen, char **newExp, char *_newExp);

void mallocFunc(char *node, long long size, char *buff, char *newExp, char *_newExp, int *ERROR_CODE);

//Addition nodes
polishFormExpression * PolishFormExpressionAddition(polishFormExpression *Node, polishFormExpression *tmpNode, int *ERROR_CODE);


#endif
