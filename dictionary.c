// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 9973;

// Hash table
node *table[N];

// Number of words
int words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char *copy = malloc(strlen(word) + 1);
    if (copy == NULL)
    {
        return false;
    }
    strcpy(copy, word);
    for(int i = 0; copy[i]; i++){
        copy[i] = tolower(copy[i]);
    }
    unsigned int hashedValue = 0;
    hashedValue = hash(copy);
    free(copy);
    node *cursor;
    cursor = table[hashedValue];
    while (cursor != NULL)
    {
        if(strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    };
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //SOURCE of hash function: http://www.cse.yorku.ca/~oz/hash.html by Dan Bernstein
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;

}

//take dictionary entry and insert it into a linked list at a part of the hash table
void insert(int key, const char *buffer)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return;
    }
    strcpy(n->word, buffer);
    n->next = NULL;
    if (table[key] == NULL)
    {
        n->next = NULL;
        table[key] = n;
    }
    else
    {
        n->next = table[key];
        table[key] = n;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    else
    {
        char buf[LENGTH];
        while (fscanf(dict, "%s", buf) != EOF)
        {
            int hashedValue = hash(buf);
            insert(hashedValue, buf);
            words++;
        }
    //size();
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

//destroy list

bool destroy(node *head)
{
    if (head == NULL)
    {
        free(head);
        return true;
    }
    else
    {
        destroy(head->next);
        free(head);
        return true;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if(destroy(table[i]))
        {
            return true;
        }
    }
    return false;
}
