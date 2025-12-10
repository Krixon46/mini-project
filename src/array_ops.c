#include <stdio.h>
#include "array_ops.h"

void displayImages(Image* arr, int count) {
    if (count == 0) {
        printf("\nNo records loaded.\n");
        return;
    }

    printf("\n===== IMAGE RECORDS =====\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\n", arr[i].id);
        printf("Filename: %s\n", arr[i].filename);
        printf("Resolution: %dx%d\n", arr[i].width, arr[i].height);
        printf("Size: %.2f KB\n", arr[i].size_kb);
        printf("Bit Depth: %d\n", arr[i].bit_depth);
        printf("-----------------------------\n");
    }
}
