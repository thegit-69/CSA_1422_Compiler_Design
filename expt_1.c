
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int main() {
    char s[1000], token[MAX];
    int i = 0, j, k;

    printf("Enter a C statement:\n");
    fgets(s, sizeof(s), stdin);

    while (s[i] != '\0') {
        if (isspace((unsigned char)s[i])) {
            i++;
        }
        else if (s[i] == '/' && s[i + 1] == '/') {
            break;
        }
        else if (s[i] == '/' && s[i + 1] == '*') {
            i += 2;
            while (s[i] != '\0' &&
                   !(s[i] == '*' && s[i + 1] == '/'))
                i++;
            if (s[i] != '\0')
                i += 2;
        }
        else if (isalpha((unsigned char)s[i]) || s[i] == '_') {
            j = 0;
            while (isalnum((unsigned char)s[i]) || s[i] == '_') {
                if (j < MAX - 1)
                    token[j++] = s[i];
                i++;
            }
            token[j] = '\0';
            printf("Identifier: %s\n", token);
        }
        else if (isdigit((unsigned char)s[i])) {
            j = 0;
            while (isdigit((unsigned char)s[i]) || s[i] == '.') {
                if (j < MAX - 1)
                    token[j++] = s[i];
                i++;
            }
            token[j] = '\0';
            printf("Constant: %s\n", token);
        }
        else {
            char op[3] = {s[i], '\0', '\0'};

            if (strchr("+-*/%=!<>&|^", s[i])) {
                if ((s[i + 1] == '=' &&
                     strchr("+-*/%=!<>", s[i]) != NULL) ||
                    (s[i] == '+' && s[i + 1] == '+') ||
                    (s[i] == '-' && s[i + 1] == '-') ||
                    (s[i] == '&' && s[i + 1] == '&') ||
                    (s[i] == '|' && s[i + 1] == '|')) {
                    op[1] = s[i + 1];
                    i++;
                }
                printf("Operator: %s\n", op);
            }
            i++;
        }
    }

    return 0;
}
