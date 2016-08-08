/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#ifndef _CROSSWORDS_H_
#define _CROSSWORDS_H_

#include "config.h"
#include "wordList.h"

struct Board {
    char title[MAX_TITLE_LENGTH];
    int size_x, size_y;
    char cells[MAX_HEIGHT+1][MAX_WIDTH+1];
};

typedef struct Board board;
typedef enum {HOR, VERT, NONE} Orientation;

board *create();
void clearBoard(board *b);
void printBoard(board *b);
int boardLoadFromFile(board *b, char *path);
int boardSaveToFile(board *b, char *path);
WordArray *wordMatch(char *pattern);

#endif
