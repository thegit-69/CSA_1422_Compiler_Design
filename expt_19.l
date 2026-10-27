%{
#include <stdio.h>

long characters = 0;
long words = 0;
long lines = 0;
int last_char = '\0';
%}

%option noyywrap
%x COMMENT

%%
"//"[^\n]* {
    characters += yyleng;
    last_char = yytext[yyleng - 1];
}

"/*" {
    characters += yyleng;
    last_char = '*';
    BEGIN(COMMENT);
}

<COMMENT>"*/" {
    characters += yyleng;
    last_char = '/';
    BEGIN(INITIAL);
}

<COMMENT>\n {
    characters++;
    lines++;
    last_char = '\n';
}

<COMMENT>. {
    characters++;
    last_char = yytext[0];
}

<COMMENT><<EOF>> {
    return 0;
}

\"([^\\\n]|\\.)*\" {
    characters += yyleng;
    words++;
    last_char = yytext[yyleng - 1];
}

\'([^\\\n]|\\.)*\' {
    characters += yyleng;
    words++;
    last_char = yytext[yyleng - 1];
}

\n {
    characters++;
    lines++;
    last_char = '\n';
}

[ \t\r]+ {
    characters += yyleng;
    last_char = yytext[yyleng - 1];
}

[A-Za-z_][A-Za-z0-9_]* {
    characters += yyleng;
    words++;
    last_char = yytext[yyleng - 1];
}

[0-9]+(\.[0-9]+)? {
    characters += yyleng;
    words++;
    last_char = yytext[yyleng - 1];
}

. {
    characters++;
    last_char = yytext[0];
}

%%

int main(void)
{
    yylex();

    if (characters > 0 && last_char != '\n')
        lines++;

    printf("\nNumber of characters = %ld\n", characters);
    printf("Number of words = %ld\n", words);
    printf("Number of lines = %ld\n", lines);

    return 0;
}

