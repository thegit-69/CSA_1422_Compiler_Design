#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[100], temp[100];
int t = 1;

int main() {
    int i, j, k, n;

    printf("Enter an expression: ");
    scanf("%99s", expr);

    n = strlen(expr);

    // Process multiplication and division first
    for (i = 0; i < n; i++) {
        if (expr[i] == '*' || expr[i] == '/') {
            char a = expr[i - 1];
            char b = expr[i + 1];

            printf("t%d = %c %c %c\n", t, a, expr[i], b);

            // Replace the subexpression with a temporary
            for (j = i - 1, k = 0; j >= 0; j--)
                temp[k++] = expr[j];
            temp[k] = '\0';

            expr[i - 1] = '0' + t;
            for (j = i; j < n - 2; j++)
                expr[j] = expr[j + 2];
            n -= 2;
            i = -1;
            t++;
        }
    }

    // Process addition and subtraction
    for (i = 0; i < n; i++) {
        if (expr[i] == '+' || expr[i] == '-') {
            char a = expr[i - 1];
            char b = expr[i + 1];

            printf("t%d = %c %c %c\n", t, a, expr[i], b);

            expr[i - 1] = '0' + t;
            for (j = i; j < n - 2; j++)
                expr[j] = expr[j + 2];
            n -= 2;
            i = -1;
            t++;
        }
    }

    printf("Result = %c\n", expr[0]);

    return 0;
}
