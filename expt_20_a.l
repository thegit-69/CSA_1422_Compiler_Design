%{
#include <stdio.h>
%}

%option noyywrap

%%
\"([^\\\"\n]|\\.)*\" {
    printf("String constant: %s\n", yytext);
}

\'([^\\'\n]|\\.)*\' {
    printf("Character constant: %s\n", yytext);
}

[0-9]+\.[0-9]+([eE][+-]?[0-9]+)? {
    printf("Floating-point constant: %s\n", yytext);
}

[0-9]+ {
    printf("Integer constant: %s\n", yytext);
}

[A-Za-z_][A-Za-z0-9_]* ;
[ \t\r\n]+ ;
. ;
%%

int main(void) {
    yylex();
    return 0;
}
