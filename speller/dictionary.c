// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 97;

// Hash table
node *table[N];

// keep track of words in dictionary
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hvalue = 0;
    node *cursor = NULL;

    //hash word
    hvalue = hash(word);
    //point cursor to the first word in hash table
    cursor = table[hvalue];

    //check for match
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hvalue = 0;
    hvalue = (toupper(word[0]) + toupper(word[1])) % N;
    return hvalue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    int hvalue = 0;
    FILE *open_file;


    open_file = fopen(dictionary, "r"); //takes the dictionary command line argument
    if (open_file == NULL)
    {
        printf("error opening dictionary file.\n");
        fclose(open_file);
        return false;
    }

    char tmp[LENGTH + 1]; //this is going to hold the words scanned from file

    while (fscanf(open_file, "%s", tmp) != EOF)
    {
        //create a node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("error creating node");
            return false;
        }

        //copy word into node
        strcpy(n -> word, tmp);

        hvalue = hash(tmp);

        //need to go to that hashed index value in hash table to attach the node

        n -> next = table[hvalue];
        table[hvalue] = n;
        word_count++;

    }
    fclose(open_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp;
    node *cursor;
    //clearing nodes from memory
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }

    }


    return true;
}
