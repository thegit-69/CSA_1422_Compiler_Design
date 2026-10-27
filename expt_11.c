
#include <stdio.h>
#include <string.h>

struct Symbol {
    char name[30];
    char type[20];
    int address;
};

struct Symbol table[100];
int count = 0;

void insert() {
    char name[30], type[20];
    int i;

    printf("Enter symbol name: ");
    scanf("%29s", name);

    for (i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0) {
            printf("Symbol already exists!\n");
            return;
        }
    }

    printf("Enter symbol type: ");
    scanf("%19s", type);

    strcpy(table[count].name, name);
    strcpy(table[count].type, type);
    table[count].address = 1000 + count * 4;
    count++;

    printf("Symbol inserted successfully.\n");
}

void display() {
    int i;

    if (count == 0) {
        printf("Symbol table is empty.\n");
        return;
    }

    printf("\nName\tType\tAddress\n");
    printf("-----------------------------\n");

    for (i = 0; i < count; i++) {
        printf("%s\t%s\t%d\n",
               table[i].name,
               table[i].type,
               table[i].address);
    }
}

void search() {
    char name[30];
    int i;

    printf("Enter symbol to search: ");
    scanf("%29s", name);

    for (i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0) {
            printf("Symbol found!\n");
            printf("Name: %s\n", table[i].name);
            printf("Type: %s\n", table[i].type);
            printf("Address: %d\n", table[i].address);
            return;
        }
    }

    printf("Symbol not found.\n");
}

void deleteSymbol() {
    char name[30];
    int i, j;

    printf("Enter symbol to delete: ");
    scanf("%29s", name);

    for (i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0) {
            for (j = i; j < count - 1; j++) {
                table[j] = table[j + 1];
            }

            count--;
            printf("Symbol deleted successfully.\n");
            return;
        }
    }

    printf("Symbol not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n--- SYMBOL TABLE ---\n");
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Search\n");
        printf("4. Delete\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: deleteSymbol(); break;
            case 5: printf("Exiting program.\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
