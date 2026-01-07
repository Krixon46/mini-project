#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

/* ---- Comparator functions ---- */

int cmp_by_id(const void *a, const void *b) {
    return ((Image *)a)->id - ((Image *)b)->id;
}

int cmp_by_filename(const void *a, const void *b) {
    return strcmp(((Image *)a)->filename,
                  ((Image *)b)->filename);
}

int cmp_by_width(const void *a, const void *b) {
    return ((Image *)a)->width - ((Image *)b)->width;
}

int cmp_by_height(const void *a, const void *b) {
    return ((Image *)a)->height - ((Image *)b)->height;
}

int cmp_by_size(const void *a, const void *b) {
    float diff = ((Image *)a)->size_kb - ((Image *)b)->size_kb;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int cmp_by_bit_depth(const void *a, const void *b) {
    return ((Image *)a)->bit_depth - ((Image *)b)->bit_depth;
}

/* ---- Main sort controller ---- */

void sort_images(Image *images, int count, int choice) {
    if (count <= 1) {
        printf("Not enough records to sort.\n");
        return;
    }

    switch (choice) {
        case 1:
            qsort(images, count, sizeof(Image), cmp_by_id);
            break;
        case 2:
            qsort(images, count, sizeof(Image), cmp_by_filename);
            break;
        case 3:
            qsort(images, count, sizeof(Image), cmp_by_width);
            break;
        case 4:
            qsort(images, count, sizeof(Image), cmp_by_height);
            break;
        case 5:
            qsort(images, count, sizeof(Image), cmp_by_size);
            break;
        case 6:
            qsort(images, count, sizeof(Image), cmp_by_bit_depth);
            break;
        default:
            printf("Invalid sort option.\n");
            return;
    }

    printf("Images sorted successfully.\n");
}
