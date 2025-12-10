#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "csv.h"
#include "array_ops.h"

int main() {
    Image* images = NULL;
    int count = 0;
    int choice;

    while (1) {
        showMenu();
        scanf("%d", &choice);

        if (choice == 1) {
            images = loadCSV("data/images.csv", &count);
            if (images != NULL)
                printf("\n%d records loaded successfully!\n", count);

        } else if (choice == 2) {
            displayImages(images, count);

        } else if (choice == 3) {
            printf("Exiting...\n");
            freeArray(images);
            break;

        } else {
            printf("Invalid option!\n");
        }
    }

    return 0;
}
