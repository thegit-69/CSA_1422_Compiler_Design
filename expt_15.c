
#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *fp;
    char filename[100];
    int ch, inWord = 0;
    int characters = 0, words = 0, lines = 0;
    int lastChar = '\0';

    printf("Enter file name: ");
    scanf("%99s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        characters++;
        lastChar = ch;

        if (ch == '\n')
            lines++;

        if (isspace((unsigned char)ch)) {
            inWord = 0;
        } else if (!inWord) {
            words++;
            inWord = 1;
        }
    }

    if (characters > 0 && lastChar != '\n')
        lines++;

    fclose(fp);

    printf("\nCharacters = %d\n", characters);
    printf("Words = %d\n", words);
    printf("Lines = %d\n", lines);

    return 0;
}
