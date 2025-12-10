#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

Image* loadCSV(const char* filepath, int* count) {
    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        printf("Error: Could not open CSV file.\n");
        return NULL;
    }

    char line[256];
    *count = 0;
    int capacity = 10;

    Image* arr = malloc(capacity * sizeof(Image));
    if (!arr) return NULL;

    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp)) {
        if (*count >= capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(Image));
        }

        Image img;
        char* token = strtok(line, ",");

        img.id = atoi(token);
        strcpy(img.filename, strtok(NULL, ","));
        img.width = atoi(strtok(NULL, ","));
        img.height = atoi(strtok(NULL, ","));
        img.size_kb = atof(strtok(NULL, ","));
        img.bit_depth = atoi(strtok(NULL, ","));

        arr[*count] = img;
        (*count)++;
    }

    fclose(fp);
    return arr;
}

void freeArray(Image* arr) {
    free(arr);
}
