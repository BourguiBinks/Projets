
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "Board.h"
#include "List.h"
#include "Set.h"

const char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";

// Probability of letters in english words in percentage

const float probaLetters[26] = {7.8, 2.0, 4.0, 3.8, 11.0, 1.4, 3.0, 2.3, 8.6,
                                0.21, 0.97, 5.3, 2.7, 7.2, 6.1, 2.8, 0.19, 7.3,
                                8.7, 6.7, 3.3, 1.0, 0.91, 0.27, 1.6, 0.44};

#define MIN(a, b) a < b ? a : b

struct Board_t
{
    size_t size;
    char **grid;
    bool **flag;
};

/* Prototypes */

static void terminate(char *m);
static char getRandomLetter(void);
static void boardInitFlag(Board *board);
static bool searchDirection(Board *board, const char *word, int len, int r, int c, int incr, int incc);
static char *getStringInADirection(Board *board, int x, int y, int direction);


/* static functions */

/**
 * @brief Terminate the program and display a message
 *
 * @param m
 */
static void terminate(char *m)
{
    fprintf(stderr, "%s\n", m);
    exit(EXIT_FAILURE);
}

/**
 * @brief Generate a random letter according to the distribution in probaLetters
 *
 * @return char
 */
static char getRandomLetter(void)
{

    float r = (float)rand() / (float)(RAND_MAX / 99.59);
    float cumsum = probaLetters[0];
    int i = 0;
    while (i < 26 && cumsum < r)
    {
        i++;
        cumsum += probaLetters[i];
    }
    if (i >= 26)
        printf("Erreur\n");
    return alphabet[i];
}

/**
 * @brief Initialize the flags to false.
 *
 * @param board
 */
static void boardInitFlag(Board *board)
{
    for (size_t r = 0; r < board->size; r++)
        for (size_t c = 0; c < board->size; c++)
            board->flag[r][c] = false;
}

/**
 * @brief return true if the word is found at position (r,c) in the direction
 *        obtained by incrementing row and column by incr and incc respetively
 *
 * @param board       a pointer to a board
 * @param word        the word to be found
 * @param len         the length of the word
 * @param r           the starting row
 * @param c           the starting column
 * @param incr        the row increment
 * @param incc        the column increment
 * @return true       if the word is found
 * @return false      otherwise
 */
static bool searchDirection(Board *board, const char *word, int len, int r, int c, int incr, int incc)
{
    int i = 0;
    int sr = r;
    int sc = c;
    while (i < len && board->grid[sr][sc] == word[i])
    {
        i++;
        sr += incr;
        sc += incc;
    }

    if (i == len)
    {
        i = 0;
        while (i < len)
        {
            board->flag[r][c] = true;
            r += incr;
            c += incc;
            i++;
        }
        return true;
    }

    return false;
}

/* header functions */

Board *boardCreate(size_t size, const char *letters)
{
    if (letters != NULL && strlen(letters) < size * size)
        terminate("createBoard: letters does not have the correct size.");

    Board *board = malloc(sizeof(Board));

    if (board == NULL)
        terminate("createBoard: allocation failed.");

    board->size = size;
    board->grid = malloc(size * sizeof(char *));
    if (board->grid == NULL)
        terminate("createBoard: allocation failed.");
    board->flag = malloc(size * sizeof(bool *));
    if (board->flag == NULL)
        terminate("createBoard: allocation failed.");

    size_t i = 0;

    for (size_t r = 0; r < size; r++)
    {
        board->grid[r] = malloc(size * sizeof(char));
        if (board->grid[r] == NULL)
            terminate("createBoard: allocation failed.");
        board->flag[r] = malloc(size * sizeof(bool));
        if (board->flag[r] == NULL)
            terminate("createBoard: allocation failed.");

        for (size_t c = 0; c < size; c++)
        {
            if (letters != NULL)
                board->grid[r][c] = letters[i++];
            else
                board->grid[r][c] = getRandomLetter();

            board->flag[r][c] = false;
        }
    }

    return board;
}

void boardFree(Board *board)
{
    if (board == NULL)
        return;

    for (size_t r = 0; r < board->size; r++)
    {
        free(board->grid[r]);
        free(board->flag[r]);
    }
    free(board->grid);
    free(board->flag);
    free(board);
}

bool boardContainsWord(Board *board, const char *word)
{
    if (board == NULL || word == NULL)
        return false;

    int len = strlen(word);
    int size = board->size;
    boardInitFlag(board);

    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            // vertical
            if (board->grid[r][c] == word[0])
            {
                if (size - r >= len)
                {
                    if (searchDirection(board, word, len, r, c, 1, 0)) // down
                        return true;
                    if (size - c >= len && searchDirection(board, word, len, r, c, 1, 1)) // down - right
                        return true;
                    if (c + 1 >= len && searchDirection(board, word, len, r, c, 1, -1)) // down - left
                        return true;
                }
                if (r + 1 >= len)
                {
                    if (searchDirection(board, word, len, r, c, -1, 0)) // up
                        return true;
                    if (size - c >= len && searchDirection(board, word, len, r, c, -1, 1)) // up - right
                        return true;
                    if (c + 1 >= len && searchDirection(board, word, len, r, c, -1, -1)) // up - left
                        return true;
                }
                if (size - c >= len && searchDirection(board, word, len, r, c, 0, 1)) // right
                    return true;
                if (c + 1 >= len && searchDirection(board, word, len, r, c, 0, -1)) // left
                    return true;
            }
        }
    }

    return false;
}

void boardDisplay(Board *board)
{
    if (board != NULL && board->size <= 20)
    {
        printf("\t");
        for (size_t i = 0; i < board->size; i++)
            printf("....");
        printf(".\n");
        for (size_t i = 0; i < board->size; i++)
        {
            printf("\t");

            for (size_t j = 0; j < board->size; j++)
                if (board->flag[i][j])
                    printf(":[%c]", board->grid[i][j]);
                else
                    printf(": %c ", board->grid[i][j]);
            printf(":\n");
            printf("\t");
            for (size_t j = 0; j < board->size; j++)
                printf(":...");
            printf(":\n");
        }
        printf("\n");
    }
    else
    {
        printf("board is too large to be printed.\n");
    }
}

/* Student code starts here */

static char *getStringInADirection(Board *board, int x, int y, int direction){
    if(board == NULL)
        return NULL;
    int n = (board->size);
    char *string = malloc(n * sizeof(char) + 1);
    if(string == NULL)
        exit(-1);
    int i = 0;
    switch(direction){
    case 0:
    // up
        while(x >= 0){
            string[i] = board->grid[x][y];
            i++;
            x--;
        }
        break;
    case 1:
    // up right
        while(x >= 0 && y < n){
            string[i] = board->grid[x][y];
            i++;
            x--;
            y++;
        }
        break;
    case 2:
    // right
        while(y < n){
            string[i] = board->grid[x][y];
            i++;
            y++;
        }
        break;
    case 3:
    // down right
        while(x < n && y < n){
            string[i] = board->grid[x][y];
            i++;
            x++;
            y++;
        }
        break;
    case 4:
    // down
        while(x < n){
            string[i] = board->grid[x][y];
            i++;
            x++;
        }
        break;
    case 5:
    // down left
        while(x < n && y >= 0){
            string[i] = board->grid[x][y];
            i++;
            x++;
            y--;
        }
        break;
    case 6:
    // left
        while(y >= 0){
            string[i] = board->grid[x][y];
            i++;
            y--;;
        }
        break;
    case 7:
    // up left
        while(x >= 0 && y >= 0){
            string[i] = board->grid[x][y];
            i++;
            x--;
            y--;
        }
        break;
    default:
        break;
    }
    string[i] = '\0';
    return string;
}


List *boardGetAllWordsFromSet(Board *board, Set *set){
    if (board == NULL || set == NULL)
        return NULL;

    List *result = listNew();
    if(result == NULL)
        exit(-1);
    Set *duplicates = setCreateEmpty();
    if(duplicates == NULL){
        listFree(result, true);
        exit(-1);
    }

    int n = board->size;
    List *prefixes = NULL;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 8; k++){
                char *string = getStringInADirection(board, i,j,k);
                if(!string){
                    listFree(result, true);
                    setFree(duplicates);
                    exit(-1);
                }
                else{
                    prefixes = setGetAllStringPrefixes(set, string);
                    if(!prefixes){
                        listFree(result, true);
                        setFree(duplicates);
                        free(string);
                        exit(-1);
                    }
                    LNode *current = prefixes->head;
                    while(current != NULL){
                        if(!setContains(duplicates, (char *)current->value)){
                            if(!setInsert(duplicates, (char *)current->value)){
                                listFree(result, true);
                                setFree(duplicates);
                                listFree(prefixes, true);
                                free(string);
                                exit(-1);
                            }
                            else{
                            listInsertLast(result, (char *)current->value);
                            }
                        }
                        current = current->next;
                    }   
                }
                free(string);
            }
                
        }
    }

    listFree(prefixes,true);
    setFree(duplicates);
    return result;
}