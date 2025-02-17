/* ========================================================================= *
 * BST definition
 * ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"
#include "Set.h"

/* Opaque Structure */

typedef struct BNode_t BNode;

struct BNode_t
{
    BNode *parent;
    BNode *left;
    BNode *right;
    char *key;
};

struct Set_t
{
    BNode *root;
    size_t size;
};

typedef struct Pair_t
{
    long sum;
    size_t n;
} Pair;

/* Prototypes of static functions */

static void bstFreeRec(BNode *n);
static BNode *bnNew(const char *key);
static char *duplicate_string(const char *str);
static char *searchPrefixesTree(BNode *node, char *prefix);


/* static functions */

/**
 * @brief Create a new tree node with its associated key.
 *
 * @param key
 * @return BNode*
 */
static BNode *bnNew(const char *key)
{
    BNode *n = malloc(sizeof(BNode));
    if (n == NULL)
    {
        printf("bnNew: allocation error\n");
        return NULL;
    }
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    n->key = duplicate_string(key);
    return n;
}

/**
 * @brief free the tree recursively, including its keys
 *
 * @param n   the root of the tree to be freed.
 */
static void bstFreeRec(BNode *n)
{
    if (n == NULL)
        return;
    bstFreeRec(n->left);
    bstFreeRec(n->right);
    free(n->key);
    free(n);
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
    Set *bst = malloc(sizeof(Set));
    if (bst == NULL)
    {
        printf("bestNew: allocation error");
        return NULL;
    }
    bst->root = NULL;
    bst->size = 0;
    return bst;
}

void setFree(Set *bst)
{
    bstFreeRec(bst->root);
    free(bst);
}

size_t setNbKeys(const Set *bst)
{
    if (bst == NULL)
        return (size_t)-1;
    return bst->size;
}

int setInsert(Set *bst, const char *key)
{
    if (bst->root == NULL)
    {
        bst->root = bnNew(key);
        if (bst->root == NULL)
        {
            return false;
        }
        bst->size++;
        return true;
    }
    BNode *prev = NULL;
    BNode *n = bst->root;
    while (n != NULL)
    {
        prev = n;
        int cmp = strcmp(key, n->key);
        if (cmp == 0)
            return 0;
        else if (cmp < 0)
            n = n->left;
        else
            n = n->right;
    }
    BNode *new = bnNew(key);
    if (new == NULL)
    {
        return -1;
    }
    new->parent = prev;
    if (strcmp(key, prev->key) <= 0)
    {
        prev->left = new;
    }
    else
    {
        prev->right = new;
    }
    bst->size++;
    return 1;
}

bool setContains(const Set *bst, const char *key)
{
    BNode *n = bst->root;
    while (n != NULL)
    {
        int cmp = strcmp(key, n->key);
        if (cmp < 0)
        {
            n = n->left;
        }
        else if (cmp > 0)
        {
            n = n->right;
        }
        else
        {
            return true;
        }
    }
    return false;
}

/* student code starts here */

//return the prefixes if it is found in the tree
static char *searchPrefixesTree(BNode *node, char *prefix){
    if(node == NULL)
        return NULL;

    if(strcmp(prefix, node->key) == 0){
        return prefix;
    }
    int cmp = strcmp(prefix, node->key);
    if(cmp < 0)
        return searchPrefixesTree(node->left, prefix);
    else
        return searchPrefixesTree(node->right, prefix);
}

List *setGetAllStringPrefixes(const Set *set, const char *str){
    if(!set || !str)
        exit(-1);
   

    //create a list to store found prefixes
    List *prefixesInSet = listNew();
        if(!prefixesInSet)
            exit(-1);

    size_t str_len = strlen(str);
    char *prefix = malloc(str_len + 1);
    if(!prefix)
        exit(-1);

    for(size_t len = 1; len <= str_len; len++){
            memcpy(prefix, str, len);
            prefix[len] = '\0';
            if(searchPrefixesTree(set->root, prefix)){
                char *prefix_copy = duplicate_string(prefix);
                if(!prefix_copy){
                    free(prefix);
                    listFree(prefixesInSet, true);
                    exit(-1);
                }
            
                if(!listInsertLast(prefixesInSet, prefix_copy)){
                    free(prefix_copy);
                    free(prefix);
                    listFree(prefixesInSet, true);
                    exit(-1);
                }
            }
    }
    LNode *current = prefixesInSet->head;
    while (current != NULL) {
        char *prefix = current->value;
        if (prefix == NULL || strcmp(prefix, "") == 0) {
            listFree(prefixesInSet, true);
            return listNew();
        }
        current = current->next;
    }
    free(prefix);
    return prefixesInSet;
}