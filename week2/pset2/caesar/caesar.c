#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

#define KEY 1
#define NCMD 2

void caesar(string, int);

int main(int argc, string argv[])
{
    int k, i = 0;

    if(argc != NCMD)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    while (isdigit(argv[KEY][i]) && argv[KEY][i] != '\0')
        i++;

    if(argv[KEY][i])
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    k = atoi(argv[1]);

    string text = get_string("plaintext: ");

    caesar(text, k);

    printf("ciphertext: %s\n", text);

    return 0;
}

void caesar(string text, int k)
{
    int i = 0;

    while (text[i] != '\0')
    {
         if(isalpha(text[i]))
         {   //ci = (pi + k)%26
             if(isupper(text[i]))
                text[i] = ((text[i] - 65 + k)%26) + 65;

             else if(islower(text[i]))
                text[i] = ((text[i] - 97 + k)%26) + 97;
         }
        i++;
    }
}