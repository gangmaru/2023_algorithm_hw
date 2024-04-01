#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int size = 0;
int max, flag;
char** pancakes;

void findmax() {
    max = 0;
    flag = 0;
    for (int i = 0; i <= size; i++) {
        if (max < atoi(pancakes[i])) {
            max = atoi(pancakes[i]);
            flag = i;
        }
    }
}

void flip(int point) {
    for (int i = 0; i <= point; i++) {
        char* tmp = pancakes[i];
        pancakes[i] = pancakes[point];
        pancakes[point] = tmp;
        point--;
    }
}

int main() {
    char* line = NULL;
    char* seq = "";
    FILE* file = fopen("cooking_delicious_pancakes_input.txt", "r");

    if (file == NULL) {
        printf("File Not Found\n");
        return 1;
    }

    size_t len = 0;
    size_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        // Remove the newline character at the end of the line
        line[read - 1] = '\0';

        char* token = strtok(line, " ");
        int length = 0;
        pancakes = (char**)malloc(sizeof(char*));
        while (token != NULL) {
            pancakes[length] = (char*)malloc(strlen(token) + 1);
            strcpy(pancakes[length], token);
            length++;

            pancakes = (char**)realloc(pancakes, (length + 1) * sizeof(char*));
            token = strtok(NULL, " ");
        }
        size = length - 1;

        while (size >= 1) {
            findmax();
            if (flag == 0) {
                flip(size);
                char num[10];
                sprintf(num, "%d", length - size);
                seq = strcat(seq, " ");
                seq = strcat(seq, num);
            }
            else if (flag == size) {
                // Do nothing
            }
            else {
                flip(flag);
                flip(size);
                char num1[10], num2[10];
                sprintf(num1, "%d", length - flag);
                sprintf(num2, "%d", length - size);
                seq = strcat(seq, " ");
                seq = strcat(seq, num1);
                seq = strcat(seq, " ");
                seq = strcat(seq, num2);
            }
            size--;
        }
        for (int i = 0; i < length; i++) {
            printf(" %s", pancakes[i]);
        }
        seq = strcat(seq, " 0");
        printf("\n%s\n", seq);

        for (int i = 0; i < length; i++) {
            free(pancakes[i]);
        }
        free(pancakes);
    }

    free(line);
    fclose(file);
    return 0;
}
