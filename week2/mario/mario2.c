#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height, i ,j;

    do{
        height = get_int("Height: ");
    }
    while(height < 1 || height > 8);

    for(i = 0; i < height; ++i){

        for(j = 0;j <height-(i+1) ; ++j){
            printf(" ");
        }

        for(j = 0;j < (i+1) ; ++j){
            printf("#");
        }

        putchar(' ');

        for(j = 0;j < (i+1) ; ++j){
            printf("#");
        }

        putchar('\n');
    }
}