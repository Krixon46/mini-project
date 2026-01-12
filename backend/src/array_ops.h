#ifndef ARRAY_OPS_H
#define ARRAY_OPS_H

#include "csv.h"

void displayImages(Image* arr, int count);
void sortByHeight(Image* arr, int count);
void addImage(Image** arr, int* count);
void deleteImage(Image* arr, int* count);
void searchImage(Image* arr, int count);

#endif
