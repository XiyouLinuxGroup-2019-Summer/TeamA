#include "client.h"

void work()
{
    printf("*****************************\n");
    printf("*****  0.exit           *****\n");
    printf("*****  1.message box    *****\n");
    printf("*****  2.add friend     *****\n");
    printf("*****  3.delete friend  *****\n");
    printf("*****  4.show friends   *****\n");
    printf("*****  5.chatone        *****\n");
    printf("*****  6.create group   *****\n");
    printf("*****  7.invite person  *****\n");
    printf("*****  8.add group      *****\n");
    printf("*****  9.chat in group  *****\n");
    printf("*****  10.send file     *****\n");
    printf("*****  11.show groups   *****\n");
    printf("*****  12.kick person   *****\n");
    printf("*****  13.quit group    *****\n");
    printf("*****************************\n");
}

int function()
{
    char choice_t[101];
    int choice;
    do {
        work();
        printf("*****choice:\n");
        scanf("%s", choice_t);getchar();
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
        case 6:
            creategroup();
            break;
        case 7:
            inviteperson();
            break;
        case 8:
            addgroup();
            break;
        case 9:
            chatgroup();
            break;
        case 10:
            sendfile();
            break;
        case 11:
            showgroups();
            break;
        case 12:
            kickperson();
            break;
        case 13:
            quitgroup();
            break;
        default:
            break;
        }
    }while (choice != 0);
    return 0;
}

