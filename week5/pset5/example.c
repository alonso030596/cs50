#include <stdio.h>
#include <math.h>

#define LENGTH 45

int main(void)
{
    FILE *fptr = fopen("example.txt", "r");

    if(fptr == NULL)
        return 0;
    
    char temp[LENGTH + 2];

    
    while(fgets(temp, LENGTH + 2, fptr) != NULL)
        printf("%s", temp);
}