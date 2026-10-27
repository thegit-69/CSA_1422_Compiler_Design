
#include <stdio.h>

int main() {
    printf("GIVEN GRAMMAR:\n");
    printf("E -> E + T | T\n");
    printf("T -> T * F | F\n");
    printf("F -> ( E ) | id\n");

    printf("\nLEADING SETS:\n");
    printf("LEADING(E) = { +, *, (, id }\n");
    printf("LEADING(T) = { *, (, id }\n");
    printf("LEADING(F) = { (, id }\n");

    return 0;
}
