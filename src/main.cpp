#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <list.h>
#include <calc.h>
#include <time.h>
#include <iomanip>
#include <easylogging++.h>

//#include "easyloggingpp/src/easylogging++.h"
//
INITIALIZE_EASYLOGGINGPP


//
//0.1 + 0.1 + 0.1 != 0.3
//
//1.12345236*10^5
//
//1*10^-1
//
//binary: 0.1 + 0.1 == 1.0
//
//dec: 0.5 + 0.5 == 1.0
//
//0.0001 = 0.0625
//
//0.0625 = 0.125/2
//
//dec 0.1 = bin 0.0(0011)
//
//Ввести переменную X например
int main (int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv); //must be on
    double timeStart = clock();
    double timeEnd{0};
    char expr[5000] = {0,};
    long long size{0}, i{0}, equalIndex{0};
    double result{0}, number{0};
    char * convertedExpr{0};
    int ERROR_CODE{0};
    scanf("%5000[0-9+.-*/()= a-zA-Z]", expr);
    if(VLOG_IS_ON(2)) LOG(TRACE) << "expression is " << expr;
    size = strlen(expr);
    printf("size: %lld\n", size);

    //Конвертируем строку в польскую форму записи

    char *endPtr{expr};
    long long newExpEnd{0};

    checkIfExpressionCorrect(expr, size, &ERROR_CODE);

    switch(ERROR_CODE) {
        case 0: break;
        case 4: {
            //Повторение знаков в выржении
            fprintf(stderr,"ERROR: Repeating signs in the Expression\n");
            return 0;
        }
        case 5: {
            //Несоответствие открывающих и закрывающих скобок
            fprintf(stderr, "ERROR: Count of open and close brackets mismatch\n");
            return 0;
        }
        case 6: {
            //После закрывающей скобки перед равенством есть что-то кроме пробела
            fprintf(stderr, "ERROR: There is something except space between |Equal Sign| and |Closing Bracket|\n");
            return 0;
        }
        case 7: {
            //В названии переменной или функции есть недопустимый символ
            fprintf(stderr, "ERROR: In the name of the |Variable| or the |Function| there is an unacceptable symbol\n");
            return 0;
        }
        case 8: {
            //Не обозначено название фукнкции или название переменной
            fprintf(stderr, "ERROR: You haven't indicated the name of Variable or the name of Function\n");
            return 0;
        }
        case 9: {
            //Больше одного знака равенства в выражении
            fprintf(stderr, "ERROR: There is more than one |Equal Sign| in the Expression\n");
            return 0;
        }
        case 10: {
            //Выражение начинается или заканчивается знаком
            fprintf(stderr, "ERROR: The Expression cann't begins or ends with Computation signs\n");
            return 0;
        }
        case 11: {
            //В выражении нет знаков вычисления
            fprintf(stderr, "ERROR: There is nothing Computation signs in the Expression\n");
            return 0;
        }
        default: break;
    }

    polishFormExpression *node;
    node = convertToPolishForm(expr, NULL, size, &newExpEnd, &endPtr, &ERROR_CODE);
    if (ERROR_CODE) {
      switch(ERROR_CODE){
        case 1: {"returned error with code 1"; break;}
        case 2: {"returned error with code 2"; break;}
        case 3: {"returned error with code 3"; break;}
        case 4: {"returned error with code 4"; break;}
        default: break;
      }
      return 0;
    }
    printf("Converting into polish form Expression: \"%s\"\n", node->str);
    //Считаем конвертированную форму
    if(VLOG_IS_ON(2)) LOG(TRACE) << "convertedExpr: " << node->str;
    result = calc(expr, size, node->str, &ERROR_CODE);

    if (ERROR_CODE) {
      switch(ERROR_CODE){
        case 1: {"returned error with code 1"; break;}
        case 2: {"returned error with code 2"; break;}
        case 3: {"returned error with code 3"; break;}
        case 4: {"returned error with code 4"; break;}
        default: break;
      }
      return 0;
    }
    printf("calculated: %.4f\n", result);
    timeEnd = clock();
    if(VLOG_IS_ON(1)) LOG(TRACE) << std::fixed << "The program's working time is "
     << (timeEnd - timeStart) / CLOCKS_PER_SEC << "\n";
//    char *expression;
//    expression = (char*)malloc(20*sizeof(char));
//    size = 20;
//    i = 0;
//    for (i = 0; i != '\0'; i++) {
//        if (i > size) {
//            expression = (char*)realloc(expression, (size+20)*sizeof(char));
//            size += 20;
//        }
//        scanf("%c", &expression[i]);
//        printf("%c", expression[i]);
//    }
    printf("\n");
    return 0;
}
