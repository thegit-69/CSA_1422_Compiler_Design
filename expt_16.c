
#include <stdio.h>

int main() {
    char op, arg1[20], arg2[20], result[20];

    printf("Enter three-address code (e.g., t1=a+b): ");
    scanf("%19[^=]=%19s", result, arg2);

    // Extract the operator and operands
    if (sscanf(arg2, "%19[^+*/-]%c%19s",
               arg1, &op, arg2) == 3) {
        printf("\nTarget Assembly Code:\n");

        printf("MOV R0, %s\n", arg1);
        printf("MOV R1, %s\n", arg2);

        switch (op) {
            case '+': printf("ADD R0, R1\n"); break;
            case '-': printf("SUB R0, R1\n"); break;
            case '*': printf("MUL R0, R1\n"); break;
            case '/': printf("DIV R0, R1\n"); break;
            default:
                printf("Invalid operator\n");
                return 1;
        }

        printf("MOV %s, R0\n", result);
    } else {
        printf("Invalid three-address code\n");
    }

    return 0;
}
