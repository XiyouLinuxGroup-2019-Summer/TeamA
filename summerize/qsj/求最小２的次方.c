#include<stdio.h>

int main()
{
    int number;
    unsigned mask;
    mask = 1u << 31;
    scanf("%d", &number);
    
    while ( mask ) {
        if ( (mask & number) != 0 ) 
            break;
        mask >>= 1;
    }
    
    printf("%d\n", mask);
    
    return 0;
}

