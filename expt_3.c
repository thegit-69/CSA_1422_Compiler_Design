
#include <stdio.h>
#include <ctype.h>

int main() {
    int c, next;
    int inBlockComment = 0;
    int inLineComment = 0;

    printf("Enter source code (enter # on a line to stop):\n");

    while ((c = getchar()) != EOF) {
        // Stop when # is entered at the beginning of a line
        if (c == '#' && !inBlockComment && !inLineComment) {
            int ch;
            while ((ch = getchar()) == ' ' || ch == '\t')
                ;
            if (ch == '\n' || ch == EOF)
                break;
            putchar(c);
            if (ch != EOF)
                ungetc(ch, stdin);
            continue;
        }

        if (inLineComment) {
            if (c == '\n') {
                inLineComment = 0;
                putchar('\n');
            }
            continue;
        }

        if (inBlockComment) {
            if (c == '*') {
                next = getchar();
                if (next == '/') {
                    inBlockComment = 0;
                } else if (next != EOF) {
                    ungetc(next, stdin);
                }
            }
            continue;
        }

        if (c == '/') {
            next = getchar();

            if (next == '/') {
                inLineComment = 1;
                continue;
            } else if (next == '*') {
                inBlockComment = 1;
                continue;
            } else {
                putchar(c);
                if (next != EOF)
                    ungetc(next, stdin);
                continue;
            }
        }

        if (isspace((unsigned char)c)) {
            if (c == '\n')
                putchar('\n');
            continue;
        }

        putchar(c);
    }

    printf("\n");
    return 0;
}
