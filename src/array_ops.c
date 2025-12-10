#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_ops.h"

// initialize empty array with capacity 10
void initArray(Image **images, int *size, int *capacity) {
    *size = 0;
    *capacity = 10;
    *images = malloc((*capacity) * sizeof(Image));

    if (*images == NULL) {
        printf("Malloc failed! Exiting.\n");
        exit(1);
    }
}

// Add an image (dynamic expansion)
void addImage(Image **images, int *size, int *capacity, Image img) {
    if (*size >= *capacity) {
        *capacity *= 2;
        *images = realloc(*images, (*capacity) * sizeof(Image));
        if (*images == NULL) {
            printf("Realloc failed! Exiting.\n");
            exit(1);
        }
    }

    (*images)[(*size)++] = img;
}
