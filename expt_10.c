#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 20
#define MAX_ALTS 20
#define MAX_LEN 100

// Helper function to remove leading and trailing whitespace
void trim(char *str) {
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t') {
        start++;
    }
    if (start > 0) {
        memmove(str, str + start, strlen(str + start) + 1);
    }
    int end = strlen(str) - 1;
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r')) {
        str[end] = '\0';
        end--;
    }
}

// Function to eliminate left factoring from a single production rule
void eliminate_left_factoring(char *rule) {
    char lhs[MAX_LEN] = {0};
    char rhs[MAX_LEN] = {0};
    char alts[MAX_ALTS][MAX_LEN];
    int alt_count = 0;

    // Locate the production arrow '->'
    char *arrow = strstr(rule, "->");
    if (!arrow) {
        printf("%s\n", rule);
        return;
    }

    strncpy(lhs, rule, arrow - rule);
    lhs[arrow - rule] = '\0';
    strcpy(rhs, arrow + 2);

    trim(lhs);
    trim(rhs);

    // Split RHS alternatives delimited by '/' or '|'
    int rhs_len = strlen(rhs);
    int cur = 0;
    for (int i = 0; i <= rhs_len; i++) {
        if (rhs[i] == '|' || rhs[i] == '/' || rhs[i] == '\0') {
            alts[alt_count][cur] = '\0';
            trim(alts[alt_count]);
            if (strlen(alts[alt_count]) > 0) {
                alt_count++;
            }
            cur = 0;
        } else {
            alts[alt_count][cur++] = rhs[i];
        }
    }

    // Rules with only 1 alternative cannot have common prefixes
    if (alt_count <= 1) {
        printf("%s -> %s\n", lhs, rhs);
        return;
    }

    // Find the longest common prefix across all pairs of alternatives
    int max_len = 0;
    char common_prefix[MAX_LEN] = "";

    for (int i = 0; i < alt_count; i++) {
        for (int j = i + 1; j < alt_count; j++) {
            int k = 0;
            while (alts[i][k] && alts[j][k] && alts[i][k] == alts[j][k]) {
                k++;
            }
            if (k > max_len) {
                max_len = k;
                strncpy(common_prefix, alts[i], k);
                common_prefix[k] = '\0';
            }
        }
    }

    // If no common prefix exists, print rule unchanged
    if (max_len == 0) {
        printf("%s -> ", lhs);
        for (int i = 0; i < alt_count; i++) {
            printf("%s%s", alts[i], (i == alt_count - 1) ? "\n" : " | ");
        }
        return;
    }

    // Identify alternatives that share the longest prefix
    int matched[MAX_ALTS] = {0};
    for (int i = 0; i < alt_count; i++) {
        if (strncmp(alts[i], common_prefix, max_len) == 0) {
            matched[i] = 1;
        }
    }

    // 1. Output the main factored production: A -> alpha A' | gamma
    printf("%s -> %s%s'", lhs, common_prefix, lhs);
    for (int i = 0; i < alt_count; i++) {
        if (!matched[i]) {
            printf(" | %s", alts[i]);
        }
    }
    printf("\n");

    // 2. Output the auxiliary production: A' -> beta1 | beta2 | ...
    printf("%s' -> ", lhs);
    int first = 1;
    for (int i = 0; i < alt_count; i++) {
        if (matched[i]) {
            if (!first) {
                printf(" | ");
            }
            first = 0;
            char *suffix = alts[i] + max_len;
            if (strlen(suffix) == 0) {
                printf("e"); // e represents epsilon / empty string
            } else {
                printf("%s", suffix);
            }
        }
    }
    printf("\n");
}

int main() {
    int n;
    char rules[MAX_RULES][MAX_LEN];

    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }
    while (getchar() != '\n'); // Clear trailing newline

    for (int i = 0; i < n; i++) {
        printf("Enter production %d: ", i + 1);
        if (fgets(rules[i], sizeof(rules[i]), stdin)) {
            rules[i][strcspn(rules[i], "\r\n")] = '\0';
        }
    }

    printf("\n--- Grammar After Eliminating Left Factoring ---\n");
    for (int i = 0; i < n; i++) {
        eliminate_left_factoring(rules[i]);
    }

    return 0;
}