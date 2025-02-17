#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Set.h"
#include "List.h"


/* Opaque Structure */

typedef struct RNode_t RNode;

// Structure representing a node of the radix tree
struct RNode_t{
    RNode *parent;            // Pointer to the parent node
    char *prefix;              // Prefix of the node
    char *key;                 // Key of the node
    RNode *children[26];  // Array of pointers to the children nodes
    size_t childrenCount;     // Number of children
};

// Structure representing the radix set
struct Set_t{
    RNode *root;  // Root of the radix tree
    size_t size;      // Number of elements in the set
};


/* Prototypes of static functions */
static RNode *rnNew(const char *key);
static char *duplicate_string(const char *str);
static bool setContainsRec(RNode *node, const char *key);
static char* findCommonPrefix(const char* str1, const char* str2);
static char* findRemainingSuffix(const char* str1, const char* str2);
static char* findCommonSuffix(const char* str1, const char* str2);
static char* findRemainingPrefix(const char* str1, const char* str2);
static void removeSubstring(char *string, const char *substring);




/* static functions */

static RNode *rnNew(const char *key){
    RNode *n = malloc(sizeof(RNode));
    if(n == NULL){
        // Memory allocation error handling
        printf("rnNew: allocation error\n");
        exit(-1);
    }
    n->prefix = NULL; // The prefix will be set later
    n->parent = NULL; // The parent will be set later
    n->key = duplicate_string(key); // Node key
    for(int i = 0; i < 26; i++){
        n->children[i] = NULL; // Initialize the children array to NULL
    }
    n->childrenCount = 0; // No children for now
    return n;
}

/**
 * @brief Duplicate a string
 *
 * @param str
 * @return char*
 */
static char *duplicate_string(const char *str){
    char *copy = malloc(strlen(str) + 1);
    if (!copy)
        exit(-1);
    memcpy(copy, str, strlen(str) + 1);
    return copy;
}

/* header functions */
Set *setCreateEmpty(void){
    Set *radix = malloc(sizeof(Set));
    if (radix == NULL)
    {
        printf("bestNew: allocation error");
        exit(-1);
    }
    radix->root = NULL;
    radix->size = 0;
    return radix;
}

/**
 * @brief free the tree recursively, including its keys
 *
 * @param n   the root of the tree to be freed.
 */
static void radixFreeRec(RNode *n){
    if(n == NULL)
        exit(-1);

    for(int i = 0; i < 26; i++){
        if(n->children[i] != NULL && n->children[i]->prefix != NULL){
            free(n->children[i]->prefix);
            radixFreeRec(n->children[i]);  
        }
    }
    free(n->key);
    free(n);
}

void setFree(Set *set){
    radixFreeRec(set->root);
    free(set);
}

size_t setNbKeys(const Set *set){
    if(set == NULL)
        return (size_t)-1;
    return set->size;
}

static bool setContainsRec(RNode *node, const char *key){
    if(node == NULL){
        return false;
    }
    if(node->key != NULL && strcmp(node->key, key) == 0){
        return true;
    }
    for(int i = 0; i < 26; i++){
        if(node->children[i] != NULL && findCommonPrefix(node->children[i]->prefix, key) != NULL){
            node = node->children[i];
            return setContainsRec(node, key);
        }
    }
    return false;
}

bool setContains(const Set *set, const char *key){
    return setContainsRec(set->root, key);
}

// "Subtracts" two strings. Example: "hello" - "hel" = "lo" 
// Counter example: "goodbye" - "bye" = NULL because "bye" is not a prefix of "goodbye"
// Counter example: "soap" - "tornado" = NULL because "tornado" is not a prefix of "soap"

static char* findCommonPrefix(const char* str1, const char* str2){
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int prefixLength = 0;
    
    // Find the length of the common prefix
    while (prefixLength < len1 && prefixLength < len2 && str1[prefixLength] == str2[prefixLength]) {
        prefixLength++;
    }
    
    // Allocate memory for the result string
    char* result = malloc((prefixLength + 1) * sizeof(char));
    
    // Copy the common prefix to the result string
    strncpy(result, str1, prefixLength);
    
    // Null-terminate the result string
    result[prefixLength] = '\0';
    if(strlen(result) == 0){
        exit(-1);
    }
    return result;
}

static char* findRemainingSuffix(const char* str1, const char* str2){
    // Assuming the first string is larger than the second one
    if(strlen(str1) < strlen(str2)){
        return NULL;
    }

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int prefixLength = 0;
    
    // Find the length of the common prefix
    while (prefixLength < len1 && prefixLength < len2 && str1[prefixLength] == str2[prefixLength]) {
        prefixLength++;
    }
    
    // Allocate memory for the result string
    char* result = malloc((len1 - prefixLength + 1) * sizeof(char));
    
    // Copy the remaining suffix to the result string
    strncpy(result, str1 + prefixLength, len1 - prefixLength);
    // Null-terminate the result string
    result[len1 - prefixLength] = '\0';
    
    return result;
}
static char* findCommonSuffix(const char* str1, const char* str2){
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int suffixLength = 0;
    
    // Find the length of the common suffix
    while (suffixLength < len1 && suffixLength < len2 && str1[len1 - suffixLength - 1] == str2[len2 - suffixLength - 1]) {
        suffixLength++;
    }
    
    // Allocate memory for the result string
    char* result = malloc((suffixLength + 1) * sizeof(char));
    
    // Copy the common suffix to the result string
    strncpy(result, str1 + len1 - suffixLength, suffixLength);
    
    // Add the null-terminating character
    result[suffixLength] = '\0';
    
    return result;
}
static char* findRemainingPrefix(const char* str1, const char* str2) {
    // Find the common suffix between the two strings
    char* commonSuffix = findCommonSuffix(str1, str2);
    
    // Find the length of the common suffix
    int suffixLength = strlen(commonSuffix);
    
    // Find the length of the first string
    int len1 = strlen(str1);
    
    // Allocate memory for the result string
    char* result = malloc((len1 - suffixLength + 1) * sizeof(char));
    
    // Copy the non-common part of the first string to the result
    strncpy(result, str1, len1 - suffixLength);
    
    // Add the null-terminating character
    result[len1 - suffixLength] = '\0';
    
    // Free the allocated memory for the common suffix
    free(commonSuffix);
    
    return result;
}


static void removeSubstring(char *string, const char *substring) {
    char *position = strstr(string, substring);
    if (position != NULL) {
        // Copy the part of the string before the substring
        strcpy(position, position + strlen(substring));
    }
}

int setInsert(Set *set, const char *key){
    if(set == NULL || key == NULL){
        exit(-1);
    }
    if(set->root == NULL){
         set->root = rnNew("");
         set->root->prefix = "";
         set->root->childrenCount = 1;
         set->root->children[0] = rnNew(key);
         set->root->children[0]->prefix = duplicate_string(key);
         set->root->children[0]->parent = set->root;
         set->size++;
         return true;
   }
   RNode *current = set->root->children[0];
   RNode *parent = set->root;
   int index = 0;
   int floor = 1;


   char *concat = malloc(sizeof(char)*255);
   if(concat == NULL){
        exit(-1);
    }
   concat[0] = '\0';

   while(current != NULL){
        strcat(concat, current->prefix);
        if(strcmp(key, concat) == 0){
            current->key = duplicate_string(key);
            if(current->key == NULL){
                free(concat);
                exit(-1);
            }
            set->size++;
            free(concat);
            return 0;
        }
        char *tmp = findRemainingSuffix(key, parent->prefix);
        if(tmp == NULL){
            free(concat);
            exit(-1);
        }
        if(findCommonPrefix(current->prefix, tmp) != NULL){
            int comparison = strcmp(current->key, key);
            if(comparison == 0){
            // The key is already present in the set
                free(concat);
                free(tmp);
                return 0;
            }
            if(current->childrenCount > 0 && strcmp(findCommonPrefix(concat, key), concat) == 0){
                parent = current;
                current = current->children[0];
                floor++;
                index = 0;
            }
            else if(comparison > 0 && strcmp(findCommonPrefix(concat, key), key) == 0){
                // The key is a prefix of the current node's key --> we need to insert a new node between the current node and the parent 
                // Example: we have "hello" initially and we want to insert "hel" --> "hel" is inserted between "hello" and the root

                // Create a new node
                RNode *newNode = rnNew(key);
                if(newNode == NULL){
                    free(concat);
                    free(tmp);
                    exit(-1);
                }
                if(parent->key == NULL){
                    char *tmp = findRemainingSuffix(concat, key);
                    if(tmp == NULL){
                        free(concat);
                        free(newNode);
                        exit(-1);
                    }
                    newNode->prefix = findRemainingPrefix(current->prefix, tmp);
                    if(newNode->prefix == NULL){
                        free(concat);
                        free(newNode);
                        free(tmp);
                        exit(-1);
                    }
                    // We know that the new node will have a child (the current node)
                    current->prefix = tmp;
                    if(current->prefix == NULL){
                        free(concat);
                        free(newNode);
                        free(tmp);
                        free(newNode->prefix);
                        exit(-1); 
                    }
                }else{
                    newNode->prefix = findRemainingSuffix(key, parent->prefix);
                    if(newNode->prefix == NULL){
                        free(concat);
                        free(newNode);
                        free(tmp);
                        exit(-1);
                    }
                    current->prefix = findRemainingSuffix(current->key, key);
                    if(current->prefix == NULL){
                        free(concat);
                        free(newNode);
                        free(newNode->prefix);
                        free(tmp);
                        exit(-1);
                    }
                }
                newNode->childrenCount = 1;
                // Set the parent of the current node to the new node
                current->parent = newNode;
                // Change the child of the parent to the new node
                parent->children[index] = newNode;
                // Change the parent of the new node to the parent
                newNode->parent = parent;
                newNode->children[0] = current;
                set->size++;
                free(concat);
                free(tmp);
                return 0;
            }
            else if(comparison < 0 && strcmp(findCommonPrefix(concat, key), concat) == 0){
                // The key of the current node is a prefix of the key to be inserted --> add the node after the current node
                // Example: we have "word" initially and we want to insert "wording" --> "wording" is added after "word"
                // Create a new node
                RNode *newNode = rnNew(key);
                if(newNode == NULL){
                    free(concat);
                    free(tmp);
                    exit(-1);
                }
                // Connect the new node to the current node
                newNode->parent = current;
                current->children[index] = newNode;
                // Add the remaining suffix to the new node
                newNode->prefix = findRemainingSuffix(key, current->key);
                if(newNode->prefix == NULL){
                    free(concat);
                    free(tmp);
                    free(newNode);
                    exit(-1);
                }
                set->size++;
                current->childrenCount++;                    
                free(concat);
                free(tmp);
                return 0;
            }
            else if(strcmp(findCommonPrefix(concat, key), key) != 0 || strcmp(findCommonPrefix(concat, key), concat) != 0){
                // The key has a common prefix with an edge of the current node --> we need to split into 2 new nodes
                // Example: we have "team" initially and we want to add "tears" --> We create an empty transition node instead of the current node and create two children with "tears" and "team"
                // Create a new node
                RNode *newNode = rnNew(key);
                if(newNode == NULL){
                    free(concat);
                    free(tmp);
                    exit(-1);
                }
                // Find the common prefix of the key and the current node and store it in the prefix of the current node
                current->prefix = findCommonPrefix(key, current->key);
                if(current->prefix == NULL){
                    free(concat);
                    free(tmp);
                    free(newNode);
                    exit(-1);
                }
                // Create a new node with the key of the current node (and set the current node's key to "")
                RNode *new2 = rnNew(current->key);
                if(new2 == NULL){
                    free(concat);
                    free(tmp);
                    free(newNode);
                    free(current->prefix);
                    exit(-1);
                }
                current->key = "";
                // Connect the new nodes to their parent (the current node)
                current->children[current->childrenCount] = new2;
                current->children[current->childrenCount + 1] = newNode;
                // Add 2 children to the current node
                current->childrenCount += 2;
                new2->parent = current;
                newNode->parent = current;                    
                // Add the prefixes to the new nodes
                new2->prefix = findRemainingSuffix(new2->key, current->prefix);
                if(new2->prefix == NULL){
                    free(concat);
                    free(tmp);
                    free(newNode);
                    free(current->prefix);
                    free(new2);
                    exit(-1);
                }
                newNode->prefix = findRemainingSuffix(key, current->prefix);
                if(newNode->prefix == NULL){
                    free(concat);
                    free(tmp);
                    free(newNode);
                    free(current->prefix);
                    free(new2);
                    free(new2->prefix);
                    exit(-1);
                }
                set->size++;
                free(concat);
                free(tmp);
                return 0;
            }
        }
        else{
            // We need to check the other children 
            // We want to keep the concatenation of the edges at higher levels and remove the last one we added (at the current level)
            // Remove the last concatenation 
            removeSubstring(concat, current->prefix); 
            current = parent->children[++index];
            if((size_t)index >= parent->childrenCount){
                // Create a new node and copy the key into its prefix
                RNode *newNode = rnNew(key);
                if(newNode == NULL){
                    free(concat);
                    free(tmp);
                    exit(-1);
                }
                newNode->prefix = findRemainingSuffix(key, parent->prefix);
                if(newNode->prefix == NULL){
                    free(concat);
                    free(tmp);
                    free(newNode);
                    exit(-1);
                }
                // Add a child to the parent and link it
                parent->childrenCount++;
                parent->children[parent->childrenCount - 1] = newNode;
                // Link the new node to the parent
                newNode->parent = parent;
                set->size++;
                free(concat);
                free(tmp);
                return 0;

            }
        }
    }
    return 0;   
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
            if(setContains(set, prefix)){
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
    free(prefix);
    return prefixesInSet;
}