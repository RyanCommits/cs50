// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

unsigned int words = 0;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    node *address = table[index];

    while (strcasecmp(word, address->word) != 0) {
        if (address->next == NULL) return false;
        address = address->next;
    }

    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH] = "";
    FILE *file = fopen(dictionary, "r");

    if (file == NULL) {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    while (fscanf(file, "%s", word) != EOF) {
        node *n = malloc(sizeof(node));

        // creating new node
        strcpy(n->word, word);
        n->next = NULL;
        words++;

        // hash
        int index = hash(word);

        // organize next node
        if (table[index] != NULL) {
            n->next = table[index];
        }
        table[index] = n;
    }

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++) {
        node *currentNode = table[i];
        node *tmp = NULL;

        while (currentNode != NULL) {
            tmp = currentNode->next;
            free(currentNode);
            currentNode = tmp;
            words--;
        }
    }
    return words == 0;
}
