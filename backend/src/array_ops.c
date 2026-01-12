#include <stdio.h>
#include <stdlib.h>
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
void sortByHeight(Image* arr, int count)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j].height > arr[j + 1].height) {
                Image temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void addImage(Image** arr, int* count)
{
    *arr = realloc(*arr, (*count + 1) * sizeof(Image));

    Image* img = &(*arr)[*count];

    printf("ID: ");
    scanf("%d", &img->id);
    printf("Filename: ");
    scanf("%s", img->filename);
    printf("Width Height: ");
    scanf("%d %d", &img->width, &img->height);
    printf("Size (KB): ");
    scanf("%f", &img->size_kb);
    printf("Bit depth: ");
    scanf("%d", &img->bit_depth);

    (*count)++;
}
void deleteImage(Image* arr, int* count)
{
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (arr[i].id == id) {
            for (int j = i; j < *count - 1; j++)
                arr[j] = arr[j + 1];

            (*count)--;
            printf("Deleted.\n");
            return;
        }
    }

    printf("ID not found.\n");
}
void searchImage(Image* arr, int count)
{
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (arr[i].id == id) {
            printf("Found: %s (%dx%d)\n",
                   arr[i].filename,
                   arr[i].width,
                   arr[i].height);
            return;
        }
    }
    printf("Not found.\n");
}
