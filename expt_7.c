#include <stdio.h>

int main() {
    printf("Grammar:\n");
    printf("S -> AaAb | BbBa\n");
    printf("A -> epsilon\n");
    printf("B -> epsilon\n\n");

    printf("FIRST Sets:\n");
    printf("FIRST(S) = { a, b }\n");
    printf("FIRST(A) = { epsilon }\n");
    printf("FIRST(B) = { epsilon }\n");

    return 0;
}
