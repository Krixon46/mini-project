#include <stdio.h>
#include "menu.h"
#include "array_ops.h"
#include "csv.h"

void runMenu(Image** images, int* count)
{
    int choice;

    while (1)
    {
        printf("\n1.Load  2.Display  3.Add  4.Search  5.Sort  6.Delete  7.Save & Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                *images = loadCSV("data/images.csv", count);
                break;
            case 2:
                displayImages(*images, *count);
                break;
            case 3:
                addImage(images, count);
                break;
            case 4:
                searchImage(*images, *count);
                break;
            case 5:
                sortByHeight(*images, *count);
                break;
            case 6:
                deleteImage(*images, count);
                break;
            case 7:
                saveCSV("data/images.csv", *images, *count);
                return;
        }
    }
}
