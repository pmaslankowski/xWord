/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "promptWindow.h"
#include "crosswords.h"
#include "config.h"

void createPromptWindow(PromptWindowGui *gui, GtkWindow *parent, char *word, Orientation o, int length) {
    gui->response = 0;
    gui->selected = 0;

    gui->window = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(gui->window), PROMPT_WINDOW_TITLE);
    gtk_window_set_position(GTK_WINDOW(gui->window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_modal(GTK_WINDOW(gui->window), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(gui->window), parent);

    gui->boxVert = gtk_dialog_get_content_area(GTK_DIALOG(gui->window));
    gtk_box_set_spacing(GTK_BOX(gui->boxVert), 5);

    gui->grid = gtk_grid_new();
    gui->boxHor = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gui->boxVert2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    if(o == VERT) {
        gtk_box_pack_start(GTK_BOX(gui->boxVert), gui->boxHor, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(gui->boxHor), gui->grid, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(gui->boxHor), gui->boxVert2, TRUE, TRUE, 0);
    } else {
        gtk_box_pack_start(GTK_BOX(gui->boxVert), gui->grid, FALSE, FALSE, 0);
    }
    gui->scroll = gtk_scrolled_window_new(NULL, NULL);

    for(int i=0; i < length; i++) {
        gui->cells[i] = gtk_image_new_from_file("graphics/boardCell.png");
        gui->texts[i] = gtk_label_new("");
        gtk_widget_set_name(gui->texts[i], "texts");
    }

    gui->array = wordMatch(word);
    int wordCount = gui->array->current;
    char tmp[200];
    sprintf(tmp, "Liczba pasujących słów: %d", wordCount);
    gui->infoLabel = gtk_label_new(tmp);

    gui->list = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(gui->scroll), gui->list);

    if(wordCount <= RESULTS_NUMBER) {
        for(int i=0; i < wordCount; i++)
            gui->positions[i] = i;
    } else {
        int used[wordCount];
        for(int i=0; i < wordCount; i++)
            used[i] = 0;

        srand(time(NULL));
        int pos;
        for(int i=0; i < RESULTS_NUMBER; i++) {
            do {
                pos = rand() % (wordCount+1);
            } while(used[pos] != 0);
            gui->positions[i] = pos;
            used[pos] = 1;
        }
    }

    for(int i=0; i < MIN(wordCount, RESULTS_NUMBER); i++) {
        gui->labels[i] = gtk_label_new(getNthWord(gui->array, gui->positions[i]));
        gui->rows[i] = gtk_list_box_row_new();
        gtk_container_add(GTK_CONTAINER(gui->rows[i]), gui->labels[i]);
        gtk_container_add(GTK_CONTAINER(gui->list), gui->rows[i]);
    }

    if(o == VERT) {
        //gtk_window_set_default_size(GTK_WINDOW(gui->window), PROMPT_WINDOW_WIDTH, CELL_SIZE*length + PROMPT_WINDOW_HEIGHT);
        gtk_widget_set_halign(gui->grid, GTK_ALIGN_START);
        gtk_box_pack_start(GTK_BOX(gui->boxVert2), gui->infoLabel, FALSE, FALSE, 0);
        gtk_box_pack_end(GTK_BOX(gui->boxVert2), gui->scroll, TRUE, TRUE, 0);
        for(int i=0; i < length; i++) {
            gtk_grid_attach(GTK_GRID(gui->grid), gui->texts[i], 0, i, 1, 1);
            gtk_grid_attach(GTK_GRID(gui->grid), gui->cells[i], 0, i, 1, 1);
        }
    } else {
        gtk_window_set_default_size(GTK_WINDOW(gui->window), CELL_SIZE * length + PROMPT_WINDOW_WIDTH_MARGIN, CELL_SIZE + PROMPT_WINDOW_HEIGHT);
        gtk_widget_set_halign(gui->grid, GTK_ALIGN_CENTER);
        gtk_box_pack_end(GTK_BOX(gui->boxVert), gui->infoLabel, FALSE, FALSE, 0);
        gtk_box_pack_end(GTK_BOX(gui->boxVert), gui->scroll, TRUE, TRUE, 0);
        for(int i=0; i < length; i++) {
            gtk_grid_attach(GTK_GRID(gui->grid), gui->texts[i], i, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(gui->grid), gui->cells[i], i, 0, 1, 1);
        }
    }

    gui->cancelButton = gtk_dialog_add_button(GTK_DIALOG(gui->window), "Anuluj", 0);
    gui->okButton = gtk_dialog_add_button(GTK_DIALOG(gui->window), "Wpisz", 1);

    setWord(gui, word, 1);
    connectPromptWindowSignals(gui);

    gtk_widget_show_all(gui->window);
}

void setWord(PromptWindowGui *gui, char *word, int setColors) {
    //arrays of polish characters codes - utf8
    char polishFirst[9]  = {0xC4, 0xC4, 0xC4, 0xC5, 0xC5, 0xC3, 0xC5, 0xC5, 0xC5};
    char polishSecond[9] = {0x84, 0x86, 0x98, 0x81, 0x83, 0x93, 0x9A, 0xB9, 0xBB};

    int j=0;
    int pos=0;
    while(word[j] != '\0') {
        int polishCharFirst = -1;
        int polishCharSecond = -1;

        for(int i=0; i < 9 && polishCharFirst == -1; i++)
            if(word[j] == polishFirst[i])
                polishCharFirst = i;

        if(polishCharFirst == -1) {
            if(word[j] != '.') {
                char tmp[2];
                tmp[0] = word[j];
                tmp[1] = '\0';
                gtk_label_set_text(GTK_LABEL(gui->texts[pos]), tmp);
                if(setColors)
                    gtk_widget_set_name(gui->texts[pos], "textsMatchedLetter");
            }
        } else {
            j++;
            for(int i=0; i < 9 && polishCharSecond == -1; i++)
                if(word[j] == polishSecond[i])
                    polishCharSecond = i;

            char tmp[3];
            tmp[0] = polishFirst[polishCharFirst];
            tmp[1] = polishSecond[polishCharSecond];
            tmp[2] = '\0';
            gtk_label_set_text(GTK_LABEL(gui->texts[pos]), tmp);
            if(setColors)
                gtk_widget_set_name(gui->texts[pos], "textsMatchedLetter");
        }
        j++;
        pos++;
    }
}

void listSelectedEvent(GtkWidget *widget, GtkListBoxRow *row, PromptWindowGui *gui) {
    int found=0;
    int pos=-1;
    for(int i=0; i < MIN(gui->array->current, RESULTS_NUMBER) && !found; i++)
        if(gui->rows[i] == GTK_WIDGET(row)) {
            found=1;
            pos = i;
        }
    gui->selected = pos;
    setWord(gui, getNthWord(gui->array, gui->positions[pos]), 0);
}

void promptWindowResponseEvent(GtkWidget *widget, gint response_id, PromptWindowGui *gui) {
    g_signal_handler_disconnect(G_OBJECT(gui->list), gui->listSelectedEventId); //i don't know why response event causes row-selected event too
    if(response_id == 1) {
        if(gui->array->current != 0) {
            gui->response = 1;
            strcpy(gui->wordResult, getNthWord(gui->array, gui->positions[gui->selected]));
        }
    }
    delWordArray(gui->array);
    gtk_widget_destroy(gui->window);
}

void connectPromptWindowSignals(PromptWindowGui *gui) {
    gui->listSelectedEventId = g_signal_connect(G_OBJECT(gui->list), "row-selected", G_CALLBACK(listSelectedEvent), gui);
    g_signal_connect(G_OBJECT(gui->window), "response", G_CALLBACK(promptWindowResponseEvent), gui);
}

PromptWindowGui *newPromptWindow(GtkWindow *parent, char *word, Orientation o, int length) {
    PromptWindowGui *result = malloc(sizeof(PromptWindowGui));
    createPromptWindow(result, parent, word, o, length);
    return result;
}
