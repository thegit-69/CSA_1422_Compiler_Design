
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;

int E();
int Eprime();
int T();
int Tprime();
int F();

int E() {
    return T() && Eprime();
}

int Eprime() {
    if (input[pos] == '+') {
        pos++;
        return T() && Eprime();
    }
    return 1;  // epsilon
}

int T() {
    return F() && Tprime();
}

int Tprime() {
    if (input[pos] == '*') {
        pos++;
        return F() && Tprime();
    }
    return 1;  // epsilon
}

int F() {
    if (input[pos] == '(') {
        pos++;
        if (E() && input[pos] == ')') {
            pos++;
            return 1;
        }
        return 0;
    }

    if (isalpha((unsigned char)input[pos])) {
        while (isalnum((unsigned char)input[pos]) ||
               input[pos] == '_') {
            pos++;
        }
        return 1;  // id
    }

    return 0;
}

int main() {
    printf("Enter an expression: ");
    scanf("%99s", input);

    if (E() && input[pos] == '\0')
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}
