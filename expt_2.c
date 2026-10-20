#include <stdio.h>
#include <string.h>

int main() {
    char line[500];
    int len, i, isComment = 0;

    printf("Enter a line:\n");
    fgets(line, sizeof(line), stdin);

    len = strlen(line);

    // Remove trailing newline
    if (len > 0 && line[len - 1] == '\n')
        line[--len] = '\0';

    // Check single-line comment
    if (len >= 2 && line[0] == '/' && line[1] == '/') {
        isComment = 1;
    }
    // Check multi-line comment
    else if (len >= 4 && line[0] == '/' && line[1] == '*') {
        for (i = 2; i < len - 1; i++) {
            if (line[i] == '*' && line[i + 1] == '/') {
                isComment = 1;
                break;
            }
        }
    }

    if (isComment)
        printf("The given line is a comment.\n");
    else
        printf("The given line is not a comment.\n");

    return 0;
}
