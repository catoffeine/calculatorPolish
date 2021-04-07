#include <stdio.h>

const char * errorCodeSpellOut(int *ERROR_CODE) {
    switch(*ERROR_CODE) {

        case 0: return "Ok";
        case 1: {
            return "ERROR: code 1";
        }
        case 2: {
            return "ERROR: Bad allocation memory (null pointer returned)";
        }
        case 3: {
            return "ERROR: code 3";
        }
        case 4: {
            //Повторение знаков в выражении
            return "ERROR: Repeating signs in the Expression";
        }
        case 5: {
            //Несоответствие открывающих и закрывающих скобок
            return  "ERROR: The number of open and close brackets is not proper";
        }
        case 6: {
            //После закрывающей скобки перед равенством есть что-то кроме пробела
            return  "ERROR: There is something except space between |Equal Sign| and |Closing Bracket|";
        }
        case 7: {
            //В названии переменной или функции есть недопустимый символ
            return  "ERROR: A |Variable| or |Function| name contains an unacceptable symbol";
        }
        case 8: {
            //Не обозначено название фукнкции или название переменной
            return  "ERROR: A |Variable| or |Function| name has not been specifed";
        }
        case 9: {
            //Больше одного знака равенства в выражении
            return  "ERROR: There are more than one |Equal Sign| in the Expression";
        }
        case 10: {
            //Выражение начинается или заканчивается знаком
            return  "ERROR: The Expression may not start or end with Computation signs";
        }
        case 11: {
            //В выражении нет знаков вычисления
            return  "ERROR: There is no Computation sign in the Expression";
        }
        case 12: {
            //Больше 64 переменных
            return "ERROR: Expression involves more than 64 variables";
        }
        case 13: {
            //Перед закрывающей скобкой стоит знак
            return "ERROR: Before closing bracket there is a Computation sign";
        }
        case 14: {
            //
            return "ERROR: code 14";
        }
        case 15: {
            //Между открывающей скобкой и переменной стоит запятая
            return "ERROR: There is Comma between open bracket and variable";
        }
        case 16: {
            //Повторение запятых подряд в левой части вырежения
            return "ERROR: Repeating Commas on the left part of the Expression";
        }
        default: return "Unknown ERROR";
    }
}
