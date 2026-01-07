#include <stdio.h>
#include "menu.h"
#include "array_ops.h"
#include "csv.h"
#include "sort.h"
void runMenu(Image **images, int *count)
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
            printf("DEBUG: count = %d, images ptr = %p\n", *count, *images);
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
            printf("\nSort by:\n");
            printf("1. ID\n");
            printf("2. Filename\n");
            printf("3. Width\n");
            printf("4. Height\n");
            printf("5. Size (KB)\n");
            printf("6. Bit Depth\n");
            printf("Enter choice: ");

            int sort_choice;
            scanf("%d", &sort_choice);
            sort_images(* images,* count, sort_choice);
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
