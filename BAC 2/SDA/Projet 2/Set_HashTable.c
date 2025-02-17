/* ========================================================================= *
 * HashTable
 *
 * Implementation of HashTable.h based on linked lists.
 *
 * ========================================================================= */

#include "Set.h"
#include <stdlib.h>
#include <string.h>
// !!!!!!!!!!!!!!!!!
#include <stdio.h>


#define INIT_CAPACITY 200013

/* Structures */

typedef struct LLElement_t
{
    char *key;
    struct LLElement_t *next;
} LLElement;

struct Set_t
{
    LLElement **table;
    size_t tableSize;
    size_t numElements;
};

/* Prototypes */

static LLElement *findElement(const Set *set, const char *key);
static void freeLLElement(LLElement *element);
static size_t hashFunction(const char *key);
static char *duplicate_string(const char *str);

/* static functions */

/**
 * @brief Find a pointer to the list node that contains the key or
 *        NULL if the key is not in the hash table.
 *
 * @param set              A pointer to a hash table
 * @param key              A valid string
 * @return LLElement*      The list node or NULL
 */
static LLElement *findElement(const Set *set, const char *key)
{
    if (!set)
        return NULL;

    size_t index = hashFunction(key) % set->tableSize;
    LLElement *element = set->table[index];
    while (element != NULL)
    {
        if (strcmp(key, element->key) == 0)
            return element;
        element = element->next;
    }
    return NULL;
}

/**
 * @brief Free a linked list, including its keys.
 *
 * @param element     The start of the linked list to be freed.
 */
static void freeLLElement(LLElement *element)
{
    while (element != NULL)
    {
        LLElement *nextElement = element->next;
        free(element->key);
        free(element);
        element = nextElement;
    }
}

/**
 * @brief Computing an encoding (in base 26) of the key
 *
 * @param key
 * @return size_t
 */
static size_t hashFunction(const char *key)
{
    size_t count = 0;

    for (size_t i = 0; i < strlen(key); i++)
    {
        count *= 26;
        count += key[i] - 'a';
    }

    return count;
}

/**
 * @brief Duplicate a string
 *
 * @param str
 * @return char*
 */
static char *duplicate_string(const char *str)
{
    char *copy = malloc(strlen(str) + 1);
    if (!copy)
        return NULL;
    memcpy(copy, str, strlen(str) + 1);
    return copy;
}

/* header functions */

Set *setCreateEmpty(void)
{
    Set *res = malloc(sizeof(Set));
    if (!res)
        return NULL;

    res->tableSize = INIT_CAPACITY;
    res->numElements = 0;

    res->table = malloc(sizeof(LLElement *) * res->tableSize);
    if (!res->table)
    {
        free(res);
        return NULL;
    }

    for (size_t i = 0; i < res->tableSize; ++i)
        res->table[i] = NULL;

    return res;
}

void setFree(Set *set)
{
    if (!set)
        return;

    for (size_t i = 0; i < set->tableSize; ++i)
        freeLLElement(set->table[i]);

    free(set->table);
    free(set);
}

/**
 * @brief Insert a key into the set.
 *
 * @param set The set to insert the key into.
 * @param key The key to be inserted.
 * @return int Returns -1 if the set is NULL or if memory allocation fails.
 *             Returns 0 if the key is already in the set.
 *             Returns 1 if the key was successfully inserted.
 */
int setInsert(Set *set, const char *key)
{
    // Check if the set is NULL
    if (!set)
        return -1;

    // Compute the index in the hash table for this key
    size_t index = hashFunction(key) % set->tableSize;

    // Get the first element in the linked list at this index
    LLElement *element = set->table[index];

    // Traverse the linked list to check if the key is already in the set
    while (element != NULL)
    {
        // If the key is found, return 0
        if (strcmp(key, element->key) == 0)
        {
            return 0;
        }
        // Move to the next element in the linked list
        element = element->next;
    }

    // If the key was not found in the set, create a new element
    element = malloc(sizeof(LLElement));
    // If memory allocation fails, return -1
    if (!element)
        return -1;

    // Set the key of the new element and insert it at the beginning of the linked list
    element->key = duplicate_string(key);
    element->next = set->table[index];
    set->table[index] = element;

    // Increment the number of elements in the set
    set->numElements++;

    // Return 1 to indicate that the key was successfully inserted
    return 1;
}

size_t setNbKeys(const Set *set)
{
    if (!set)
        return (size_t)-1;
    return set->numElements;
}

bool setContains(const Set *set, const char *key)
{
    return findElement(set, key) ? true : false;
}

/* student code starts here */


List *setGetAllStringPrefixes(const Set *set, const char *str){
    if(!set || !str)
        exit(-1);

    List *prefixes = listNew();
    if(!prefixes)
        exit(-1);
    size_t str_len = strlen(str);
    char *prefix = malloc(str_len + 1);
    if(!prefix)
        exit(-1);

    for(size_t len = 1; len <= str_len; len++){
        memcpy(prefix, str, len);
        prefix[len] = '\0';

        if(findElement(set, prefix)){
            char *prefix_copy = duplicate_string(prefix);
            if(!prefix_copy){
                free(prefix);
                listFree(prefixes, true);
                exit(-1);
            }

            if(!listInsertLast(prefixes, prefix_copy)){
                free(prefix_copy);
                free(prefix);
                listFree(prefixes, true);
                exit(-1);
            }
        }
    }
    LNode *current = prefixes->head;
    while (current != NULL) {
        char *prefix = current->value;
        if (prefix == NULL || strcmp(prefix, "") == 0) {
            listFree(prefixes, true);
            return listNew();
        }
        current = current->next;
    }
    free(prefix);
    return prefixes;
}


