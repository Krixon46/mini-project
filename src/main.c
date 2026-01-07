#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main()
{
    Image* images = NULL;
    int count = 0;

    runMenu(&images, &count);

    free(images);
    return 0;
}
