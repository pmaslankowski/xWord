/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#ifndef _PROMPT_WINDOW_H_
#define _PROMPT_WINDOW_H_

#include <gtk/gtk.h>
#include "config.h"
#include "crosswords.h"
#include "wordList.h"

struct promptWindowGui {
    GtkWidget *window, *grid, *boxHor, *boxVert, *boxVert2, *cells[MAX_WIDTH], *texts[MAX_WIDTH], *list, *scroll;
    GtkWidget *rows[RESULTS_NUMBER], *labels[RESULTS_NUMBER];
    GtkWidget *infoLabel;
    GtkWidget *okButton, *cancelButton;

    gint listSelectedEventId;
    char *word;
    WordArray *array;
    int positions[RESULTS_NUMBER];
    int response;
    int selected;
    char wordResult[100];
};

typedef struct promptWindowGui PromptWindowGui;

void createPromptWindow(PromptWindowGui *gui, GtkWindow *parent, char *word, Orientation o, int length);
void setWord(PromptWindowGui *gui, char *word, int setColors);
void listSelectedEvent(GtkWidget *widget, GtkListBoxRow *row, PromptWindowGui *gui);
void promptWindowResponseEvent(GtkWidget *widget, gint response_id, PromptWindowGui *gui);
void connectPromptWindowSignals(PromptWindowGui *gui);

PromptWindowGui *newPromptWindow(GtkWindow *parent, char *word, Orientation o, int length);
#endif
