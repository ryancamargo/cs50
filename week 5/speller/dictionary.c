// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int TABLE_SIZE = 50000;

// Hash table
node *table[TABLE_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Check if the word is in the hash table
    int index = hash(word);
    node *cursor = table[index];

    for (node *temp = cursor; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function using the length and characters of the word
    unsigned int hashvalue = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hashvalue += tolower(word[i]);
        hashvalue = (hashvalue * tolower(word[i])) % TABLE_SIZE;
    }
    return hashvalue;
}

int counter = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Load dictionary data into the hash table
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening dictionary file");
        return false;
    }

    char wordlist[LENGTH + 1];

    while (fscanf(file, "%s", wordlist) != EOF)
    {
        // Allocate memory for a new node and initialize it
        counter++;
        node *newNode = malloc(sizeof(node));

        if (newNode == NULL)
        {
            return false;
        }

        strcpy(newNode->word, wordlist);
        newNode->next = NULL;

        // Add the new node to the hash table
        int index = hash(wordlist);

        if (table[index] == NULL)
        {
            table[index] = newNode;
        }
        else
        {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Return the number of nodes in the hash table
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free the memory allocated for the hash table
    node *tmp = NULL;
    node *cursor = NULL;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
