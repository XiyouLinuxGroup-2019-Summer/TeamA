#include "client.h"

void welcome()
{
    printf("*****l.register*****\n");
    printf("*****2.login   *****\n");
    printf("*****0.exit    *****\n");
}

int menu()
{
    char choice_t[101];
    int choice;
    do {
        welcome();
        printf("*****choice:");
        scanf("%s", choice_t);
        choice = get_choice(choice_t);
        switch (choice) {
        case 1:
            registe();
            break;
        case 2:
            if ( login() == 1 )
                return 1;
            break;
        default:
            break;
        }
    }while (choice != 0);
    return 0;
}
