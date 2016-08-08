/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#include <stdlib.h>
#include <string.h>
#include "wordList.h"


WordArray *createWordArray(int startSize, int wordLength) {
    WordArray *result = (WordArray*) malloc(sizeof(WordArray));
    if(result == NULL)
        return NULL;

    result->current = 0;
    result->currentMaxSize = startSize;
    result->wordLength = wordLength;

    result->words = (char**) malloc(startSize*sizeof(char*));
    for(int i=0; i < startSize; i++)
        result->words[i] = (char*) malloc((wordLength+1) * sizeof(char));

    return result;
}

void delWordArray(WordArray *array) {
    if(array->currentMaxSize == 0)
        return;
    for(int i=0; i < array->currentMaxSize; i++)
        free(array->words[i]);
    free(array->words);
}

void pushWord(WordArray *array, char *word) {
    if(array->current == array->currentMaxSize) {
        array->currentMaxSize *= 2;
        if(array->currentMaxSize == 0)
            array->currentMaxSize = 1;
            
        array->words = (char**) realloc(array->words, array->currentMaxSize * sizeof(char*));
        for(int i = array->current; i < array->currentMaxSize; i++) {
            array->words[i] = (char*) malloc(array->wordLength * sizeof(char));
            array->words[i][0] = '\0';
        }
    }
    strcpy(array->words[array->current++], word);
}

char *getNthWord(WordArray *array, int n) {
    return array->words[n];
}
