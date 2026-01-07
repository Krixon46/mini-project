#ifndef CSV_H
#define CSV_H

typedef struct {
    int id;
    char filename[100];
    int width;
    int height;
    float size_kb;
    int bit_depth;
} Image;

Image* loadCSV(const char* filepath, int* count);
void saveCSV(const char* filepath, Image* images, int count);
void freeArray(Image* arr);

#endif
