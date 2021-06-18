#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int digit, sum = 0, ndigits = 1, i = 2;
    long number = get_long("Number: ");

    //Checks the number of digits
    while (number/(long)pow(10, ndigits) != 0)
        ++ndigits;
    //Computes first sum
    while (i <= ndigits)
    {
        digit = 2*((number % (long)pow(10, i))/(long)pow(10, i-1));

        if(digit < 10)
        {
            sum += digit;
        }

        else
        {
            sum += (digit % 10) + 1;
        }

        i += 2;
    }

    //Computes second sum
    i = 1;
    while (i <= ndigits)
    {
        digit =(number % (long)pow(10, i))/(long)pow(10, i-1);
        sum += digit;
        i += 2;
    }

    //Checksum
    if(sum % 10 == 0)
    {
        switch (ndigits)
        {

            case 15:
                if(number/(long)pow(10,13) == 34 || number/(long)pow(10,13) == 37)
                    printf("AMEX\n");
                else
                    printf("INVALID\n");
            break;

            case 16:
                if(number/(long)pow(10,14) >= 51 && number/(long)pow(10,14) <= 55)
                    printf("MASTERCARD\n");

                else if(number/(long)pow(10,15) == 4)
                    printf("VISA\n");

                else
                    printf("INVALID\n");
            break;

            case 13:
                if(number/(long)pow(10,12) == 4)
                printf("VISA\n");

                else
                    printf("INVALID\n");
            break;

            default:
            printf("INVALID\n");
        }
    }

    else{
        printf("INVALID\n");
    }
}