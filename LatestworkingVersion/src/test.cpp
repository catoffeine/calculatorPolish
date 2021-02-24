#include <iostream>

int main() {
    int i, bracketsC{0}, flag{0};
    char str[100] = {0,};
    scanf("%99s", str);
    
    for (i = 0; i < 100; i++) {
        if (str[i] == '(') {
            if (!flag) {
                flag = i;
            }
            bracketsC++;
        } else if (str[i] == ')') {
            if (!(--bracketsC)) {
                printf("%.*s\n", i - flag - 1, str + flag + 1);
                flag = 0;
            }
        }
    }
    return 0;
}
