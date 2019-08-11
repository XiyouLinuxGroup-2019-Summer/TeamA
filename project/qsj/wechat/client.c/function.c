#include "client.h"

void work()
{
    printf("*****0.exit         *****\n");
    printf("*****1.add friend   *****\n");
    printf("*****2.delete friend*****\n");
}

int function()
{
    char choice_t[101];
    int choice;
    do {
        work();
        printf("*****choice:");
        scanf("%s", choice_t);
        choice = get_choice(choice_t);
        switch (choice) {
        case 1:
            addfriend();
            break;
        case 2:
            break;
        default:
            break;
        }
    }while (choice != 0);
    return 0;
}
