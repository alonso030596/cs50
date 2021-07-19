#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char* ptr = "alonso"; 

    *(ptr + 2) = 'O';
    *(ptr + 3) = 'N';

    printf("%s\n", ptr);

}


