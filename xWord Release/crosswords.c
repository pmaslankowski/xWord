/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#include "crosswords.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "wordList.h"

board *create() {
    return malloc(sizeof(board));
}

void clearBoard(board *b) {
    for(int i=1; i<=b->size_y; i++)
        for(int j=1; j<=b->size_x; j++)
            b->cells[i][j]='0';
}

void printBoard(board *b) {
    for(int i=1; i<=b->size_y; i++) {
        for(int j=1; j<=b->size_x; j++) {
            g_print("%d ", b->cells[i][j]);
        }
        g_print("\n");
    }
}

int boardLoadFromFile(board *b, char *path) {
    FILE *file = fopen(path, "r");
    if(file == NULL)
        return 1;

    fscanf(file, "%[^\n]s", b->title);
    fscanf(file, "%d %d", &b->size_x, &b->size_y);
    for(int i=1; i <= b->size_y; i++)
        for(int j=1; j <= b->size_x; j++)
            fscanf(file, "%s", &b->cells[i][j]);

    fclose(file);
    return 0;
}

int boardSaveToFile(board *b, char *path) {
    FILE *file = fopen(path, "w");
    if(file == NULL)
        return 1;

    fprintf(file, "%s\n", b->title);
    fprintf(file, "%d %d\n", b->size_x, b->size_y);
    for(int i=1; i <= b->size_y; i++) {
        for(int j=1; j <= b->size_x; j++)
            fprintf(file, "%c ", b->cells[i][j]);
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}

WordArray *wordMatch(char *pattern) {
    int n = strlen(pattern);
    char path[22];
    sprintf(path, "dictionaries/%d.txt", n);
    FILE *file = fopen(path, "r");
    if(file == NULL)
        return NULL;

    char word[2*n];
    WordArray *result = createWordArray(0, 2*n);
    while(fscanf(file, "%s", word) != EOF) {
        int i=0; int j=0; int ok=1;
        while(pattern[i] != '\0' && word[j] != '\0' && ok) {
            if(pattern[i] != '.' && pattern[i] != word[j])
                ok=0;
            if ((int)word[j] < 0) //hack for polish characters...
                j++;
            i++; j++;
        }
        if(ok)
            pushWord(result, word);
    }
    fclose(file);
    return result;
}
