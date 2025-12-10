#ifndef CSV_H
#define CSV_H

#include "array_ops.h"

// Loads all rows from CSV into a dynamic array
int loadCSV(const char *filename, Image **images, int *size, int *capacity);

// Saves dynamic array back to CSV
int saveCSV(const char *filename, Image *images, int size);

#endif
