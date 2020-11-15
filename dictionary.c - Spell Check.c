// Implements a dictionary's functionality
//https://github.com/Federico-abss/CS50-intro-course/blob/master/C/pset5/speller/dictionary.c - Source of help

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26; //26 because 1 for each letter

// Hash table
node *table[N]; //Array of linked lists
int totalwords = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = table[hash(word)]; //Start with pointing cursor at hashed index of array (go to particular index of array)

    if(strcasecmp(cursor->word, word) == 0) //compare words
    {
        return true;
    }

    while (cursor->next != NULL) //traverse linked list
    {
        cursor = cursor->next; //update cursor to point to next element of the list
        if(strcasecmp(cursor->word, word) == 0) //compare words
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //Hash table is array of 26 letters(A-Z) thus it converts every word to its first letter and uses that as the index in the array
{
    int n = (int) tolower(word[0]) - 97;
    return n;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r"); //Open dictionary file to read
    char *dictword = malloc(LENGTH); //Allocate memory for storage of first word

    while(fscanf(file, "%s", dictword) != EOF) //fscanf(a, b, c) - scans from file 'a' and while scanning saves each string 'b' into pointer variable 'c' till End of File
    {
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }
        strcpy(n->word, dictword); //strcpy copies word from dictword into n->word
        totalwords++;

        n->next = table[hash(dictword)]; //Use hash function as index into hash table which is also where the pointer points to next
        table[hash(dictword)] = n; //Array to point at n which is now the new beginning of the list
    }

    fclose(file);
    free(dictword);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalwords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //creates two pointers to traverse linked list
    node *tmp;
    node *cursor;

    for(int i = 0; i < N; i++)
    {
        if(table[i] == NULL) //If element of table array is null means it contains no linked list
        {
            continue;
        }

        cursor = table[i]; //set cursor pointer to element of table array
        tmp = cursor; //set tmp pointer to point at cursor

        while(cursor->next != NULL) //traverse linked list till you reach end and its null
        {
            cursor=cursor->next; //keep going to next element
            free(tmp); //as you go to next element free the tmp pointer element
            tmp=cursor; //point tmp back at cursor
        }
    }

    free(cursor); //free cursor
    return true;
}
