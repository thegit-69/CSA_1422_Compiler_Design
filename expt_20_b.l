
%{
#include <stdio.h>

int macros = 0;
int headers = 0;
%}

%option noyywrap

%%
^[ \t]*#[ \t]*define[ \t]+[A-Za-z_][A-Za-z0-9_]* {
    macros++;
}

^[ \t]*#[ \t]*include[ \t]*[<\"][^>\"\n]+[>\"] {
    headers++;
}

\n ;
.  ;
%%

int main(void) {
    yylex();

    printf("Number of macros defined = %d\n", macros);
    printf("Number of header files included = %d\n", headers);

    return 0;
}

