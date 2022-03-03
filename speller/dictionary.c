// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get position in hash table.
    int bucket = hash(word);

    for (node *tmp = table[bucket]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Nothing to edit here, we really do not care about performance.
    // If we were to care, we would have to add more buckets to the hash table.
    return toupper(word[0]) - 'A';
}

// Recursively grow list
bool growlist(const char *word, int bucket)
{

    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        printf("Not enough memory.\n");
        return false;
    }

    // Fill new node and link it to the table.
    node *tmp = table[bucket];
    strcpy(n->word, word);
    n->next = tmp;
    table[bucket] = n;

    return true;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Couldn't open dictionary.\n");
        return false;
    }

    char word[LENGTH + 1];

    // Read through dictionary.
    while (fscanf(dict, "%s", word) != EOF)
    {
        int bucket = hash(word);
        growlist(word, bucket);
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    // Go through each table position.
    for (int i = 0; i < 26; i++)
    {
        // Go through the linked list of the position.
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            count++;
        }
    }

    if (count > 0)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
