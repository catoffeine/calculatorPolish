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
//Подумать над скобками и сделать логгирование(on/off), разбить на функции, отделить файлы main и functions
int main (int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv); //must be on
    double timeStart = clock();
    double timeEnd{0};
    char expr[5000] = {0,};
    long long size{0};
    double result{0}, i{0};
    char * convertedExpr{0};
    int ERROR_CODE{0};
    scanf("%5000s", expr);
    size = strlen(expr);
    printf("size: %lld\n", size);
    //Конвертируем строку в польскую форму записи
    char *endPtr{expr};
    long long newExpEnd{0};
    convertedExpr = convertToPolishForm(expr, NULL, size, &newExpEnd, &endPtr, &ERROR_CODE);
    printf("Converted into polish form Expression: %s\n", convertedExpr);
    //Считаем конвертированную форму
    if(VLOG_IS_ON(2)) LOG(TRACE) << "convertedExpr: " << convertedExpr;
    result = calc(expr, size, convertedExpr, &ERROR_CODE);

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
     << (timeEnd-timeStart)/CLOCKS_PER_SEC << "\n";
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
