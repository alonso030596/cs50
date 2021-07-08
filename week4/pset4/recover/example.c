#include <stdio.h>
#include <stdint.h>

#define OUT 512

int check(int *);

int main(void)
{
    int buffer[3] = {1, 2, 4};  
    check(buffer);
    printf("%ld", sizeof(OUT));
}

int check(int *buff)
{
    int A[3] = {1, 2, 4};

    if(buff[0] == *A)
        printf("Chi");

}


