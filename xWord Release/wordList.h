/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#ifndef _WORD_LIST_H
#define _WORD_LIST_H


typedef struct wordArray {
    char **words;
    int current;
    int currentMaxSize;
    int wordLength;
} WordArray;

WordArray *createWordArray(int startSize, int wordLength);
void delWordArray(WordArray *array);
char *getNthWord(WordArray *array, int n);
void pushWord(WordArray *array, char *word);

#endif
