// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Constants
#define ALPHABET_LENGTH 26

// Number of letters in each bucket ! CHANGE !
#define LETTERS_PER_BUCKET 2

// Number of buckets in hash table
const unsigned int N = pow(ALPHABET_LENGTH, LETTERS_PER_BUCKET);

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = 0;

    for(int i = 0; i < LETTERS_PER_BUCKET; i++)
    {
        // i = ( ASCII - 97 ) * 26 ^ 3 + ( ASCII - 97 ) * 26 ^ 2 ... 
        index += (*(word + i) - 97) * pow(ALPHABET_LENGTH, LETTERS_PER_BUCKET - i - 1); 
    }

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fptr = fopen(dictionary, "r");

    if(ptr == NULL)
        return false;
    
    char temp[LENGTH + 2];

    while(fgets(temp, LENGTH + 2, fptr) != NULL)
    {
        
    }

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
