#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int coins = 0, cents, sum = 0;
    float dollars;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);

    cents = round((dollars - (int)dollars) * 100);

    while (sum + 25 <= cents)
    {
        sum += 25;
        ++coins;
    }

    while (sum + 10 <= cents)
    {
        sum += 10;
        ++coins;
    }

    while (sum + 5 <= cents)
    {
        sum += 5;
        ++coins;
    }

    while (sum + 1 <= cents)
    {
        sum++;
        ++coins;
    }

    printf("%i\n", coins);

}
