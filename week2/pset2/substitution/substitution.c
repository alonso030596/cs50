#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

#define KEY 1    //key argv[] position
#define NARG 2    //Number of arguments in command line
#define ALPHA 26    //Alphabet size

int validate_key(string);
void encipher(string, string);

int main(int argc, string argv[])
{
    if(argc != NARG)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    if(validate_key(argv[KEY]))
        return 1;

    string text = get_string("plaintext: ");

    encipher(text, argv[KEY]);

    printf("ciphertext: %s\n",text);

    return 0;
}

int validate_key(string key)
{
    int one_to_one(string);

    int i = 0;

    //Checks for non-alphabetic characters
    while (key[i] != '\0')
    {
        if(!isalpha(key[i]))
        {
            printf("Key must only contain aplhabetic characters.\n");
            return 1;
        }
        i++;
    }

    //Checks size
    if(i != ALPHA)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    return one_to_one(key);
}

int RECORD[ALPHA];
//Checks for repeated characters
int one_to_one(string key)
{
    int i = 0;

    while(key[i] != '\0')
    {
        if(isupper(key[i]))
        {
            RECORD[key[i++] - 'A']++;
        }

        else if(islower(key[i]))
        {
            RECORD[key[i++] - 'a']++;
        }
    }

    i = 0;

    while(i < ALPHA)
    {
        if(RECORD[i++] != 1)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }
    return 0;
}

void encipher(string plaintext, string key)
{
    int i = 0;

    while(plaintext[i] != '\0')
    {
        if(isalpha(plaintext[i]))
        {
            if(isupper(plaintext[i]))
                plaintext[i] = toupper(key[plaintext[i] - 'A']);

            else if(islower(plaintext[i]))
                plaintext[i] = tolower(key[plaintext[i] - 'a']);
        }
        i++;
    }
}

