#ifndef ARRAY_OPS_H
#define ARRAY_OPS_H

typedef struct {
    int id;
    char fileName[100];
    int width;
    int height;
    float sizeKB;
    int bitDepth;
} Image;

// Initialize dynamic array
void initArray(Image **images, int *size, int *capacity);

// Push new image
void addImage(Image **images, int *size, int *capacity, Image img);

#endif
