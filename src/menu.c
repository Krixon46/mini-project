#include <stdio.h>
#include "menu.h"

void showMenu()
{
    int choice;

    while (1)
    {
        printf("\n=============================\n");
        printf("        MAIN MENU\n");
        printf("=============================\n");
        printf("1. Load images from CSV\n");
        printf("2. Display all images\n");
        printf("3. Add new image\n");
        printf("4. Delete an image\n");
        printf("5. Save and Exit\n");
        printf("=============================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Loading CSV... (will implement later)\n");
                break;

            case 2:
                printf("Displaying images... (will implement later)\n");
                break;

            case 3:
                printf("Adding new image... (will implement later)\n");
                break;

            case 4:
                printf("Deleting image... (will implement later)\n");
                break;

            case 5:
                printf("Saving and exiting...\n");
                return;   // Exit menu

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
