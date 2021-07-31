// Implements a dictionary's functionality

#include <stdbool.h>

#include <string.h>
#include <strings.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents the size of the dictionary
unsigned int dictionary_size = 0;

// Constants
#define ALPHABET_LENGTH 27 // 26 + apostrophe

// Number of letters in each bucket !! CHANGE !!
#define LETTERS_PER_BUCKET 2

// Number of buckets in hash table !! CHANGE !!
const unsigned int N = 27 * 27;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *cursor = table[index];

    while(cursor != NULL)
    {
        if(!strcasecmp(cursor -> word, word))
            return true;

        cursor = cursor -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = 0;

    for(int i = 0; i < LETTERS_PER_BUCKET; i++)
    {
        if(islower(*(word + i)))
            index += (*(word + i) - 97) * pow(ALPHABET_LENGTH, LETTERS_PER_BUCKET - i - 1);

        else if(isupper(*(word + i)))
            index += (*(word + i) - 65) * pow(ALPHABET_LENGTH, LETTERS_PER_BUCKET - i - 1);

        else if(*(word + i) == '\'')
            index += (*(word + i) - 13) * pow(ALPHABET_LENGTH, LETTERS_PER_BUCKET - i - 1);

        else
            ;
    }

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fptr = fopen(dictionary, "r");

    if(fptr == NULL)
        return false;

    char new_word[LENGTH + 1]; //longest word length + \0
    unsigned int index;
    node* new_node;

    while(fscanf(fptr, "%s", new_word) != EOF)
    {
        if((new_node = malloc(sizeof(node))) == NULL)
            printf("error allocating memory\n");

        index = hash(new_word);
        strcpy(new_node -> word, new_word);

        new_node -> next = table[index];
        table[index] = new_node;
        dictionary_size++;
    }

    fclose(fptr);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i;
    node *cursor;
    node *tmp;

    for(i = 0; i < N; i++)
    {
        cursor = tmp = table[i];

        while(cursor != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }
    }

    if(i != N)
        return false;

    return true;
}
