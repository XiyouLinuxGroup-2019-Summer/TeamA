#include "client.h"

void work()
{
    printf("*****0.exit         *****\n");
    printf("*****1.message box  *****\n");
    printf("*****2.add friend   *****\n");
    printf("*****3.delete friend*****\n");
    printf("*****4.show friends *****\n");
    printf("*****5.chatone      *****\n");
}

int function()
{
    char choice_t[101];
    int choice;
    do {
        if ( num_recv_pack != 0 ) 
        printf("you receive some new information or notifications\n");

        work();
        printf("*****choice:");
        scanf("%s", choice_t);
        choice = get_choice(choice_t);
        switch (choice) {
        case 1:
            deal_pack();
            break;
        case 2:
            addfriend();
            break;
        case 3:
            deletefriend();
            break;
        case 4:
            showfriends();
            break;
        case 5:
            chatone();
            break;
        default:
            break;
        }
    }while (choice != 0);
    return 0;
}

