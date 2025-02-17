#include "Stable.h"
#include "Sort.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Represents an element of an array
 * @param value an integer
 * @param index the index of the value in an array
*/
typedef struct{
    int value; 
    size_t index;
}element;


/**
 * @brief Return the difference between array[i] and array[j] 
 *          no matter what the type of the array is.
 * @param array the array of any type
 * @param i the element array[i]
 * @param j the element array[j]
 * @return array[i] - array[j]
*/
static int compareIndexes(const void *array, size_t i, size_t j);

/**
 * @brief Swap the 2 elements array[i] and array[j] 
 *      no matter what the type of the array is.
 * @param array the array of any type
 * @param i the element array[i]
 * @param j the element array[j]
 * @return array[i] and array[j] are swapped
*/
static void swapValues(void *array, size_t i, size_t j);

/**
 * @brief c.f report
 * @param array the array of any type
 * @param i the element array[i]
 * @param j the element array[j]
 * @return c.f report
*/
static int compare_new(const void *array, size_t i, size_t j);

/**
 * @brief c.f report
 * @param array the array of any type
 * @param i the element array[i]
 * @param j the element array[j]
 * @return c.f report
*/
static void swap_new(void *array, size_t i, size_t j);

static int (*global_compare)(const void *, size_t i, size_t j);
static void (*global_swap)(void *array, size_t i, size_t j);
static void *array_stablesort;
static int *indexArray = NULL;

static int compareIndexes(const void *array, size_t i, size_t j){
    const element *arrayPtr = (const element *)array;
    return arrayPtr[i].value - arrayPtr[j].value;
}

static void swapValues(void *array, size_t i, size_t j){
    element *arrayPtr = (element *)array;
    long int tempValue = arrayPtr[i].value;
    arrayPtr[i].value = arrayPtr[j].value;
    arrayPtr[j].value = tempValue;
    long int tempIndex = arrayPtr[i].index;
    arrayPtr[i].index = arrayPtr[j].index;
    arrayPtr[j].index = tempIndex;
}

bool isSortStable(size_t algo, const int *array, size_t length){
    element *intermediateArray = NULL;
    intermediateArray = malloc(length * sizeof(element));
    if(intermediateArray == NULL)
        return NULL;
    // Stores the elements of the array in an intermediate array before sorting
    for(size_t i = 0; i < length; i++){
        intermediateArray[i].value = array[i];
        intermediateArray[i].index = i;
    }
    sort(algo, intermediateArray, length, compareIndexes, swapValues);
    // We look at the indexes of the equal consecutives values and if their indexes are decreasing, the algo isn't stable
    for(size_t i = 0; i < length - 1; i++){
        if(intermediateArray[i].value == intermediateArray[i + 1].value && intermediateArray[i].index > intermediateArray[i + 1].index){
            free(intermediateArray);
            return false; 
        }
    }
    free(intermediateArray);
    return true;
}


static int compare_new(const void *array, size_t i, size_t j){
    int tmp = global_compare(array, i, j);
    if(tmp == 0){
        int tmp2 = indexArray[i] - indexArray[j];
        return tmp2; 
    }else
        return tmp;

}

static void swap_new(void *array, size_t i, size_t j){
    global_swap(array, i, j);
    int tmp = indexArray[i];
    indexArray[i] = indexArray[j];
    indexArray[j] = tmp;
}

void stableSort(size_t algo, void *array, size_t length,
                int (*compare)(const void *, size_t i, size_t j),
                void (*swap)(void *array, size_t i, size_t j))
{
    global_compare = compare;
    global_swap = swap;
    array_stablesort = array;
    indexArray = malloc(length * sizeof(int));
    if(indexArray == NULL)
        return;

    for(size_t i = 0; i < length; i++)
        indexArray[i] = i;

    sort(algo, array_stablesort, length, compare_new, swap_new);
    free(indexArray);
}
