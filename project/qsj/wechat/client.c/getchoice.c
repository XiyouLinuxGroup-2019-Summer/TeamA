#include "client.h"


int get_choice(char *choice_t)
{
    int choice =0;
    for(int i=0;i<strlen(choice_t) ;i++)
        if(choice_t[i]<'0' || choice_t[i]>'9')
            return -1;
    for(int i=0;i<strlen(choice_t);i++)
    {
        int t=1;
        for(int j=1;j<strlen(choice_t)-i;j++)
        {
            t*=10;
        }
        choice += t*(int)(choice_t[i] - 48);
    }
    return choice;
}


