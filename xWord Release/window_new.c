/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "window_new.h"
#include "main_gui.h"
#include "config.h"


void windowNewCreate(windowNewGui *gui, GtkWindow *parent) {
    gui->response = 0;
    gui->result = create();

    gui->window = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(gui->window), WINDOW_NEW_TITLE);
    gtk_window_set_position(GTK_WINDOW(gui->window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_default_size(GTK_WINDOW(gui->window), WINDOW_NEW_WIDTH, WINDOW_NEW_HEIGHT);
    gtk_window_set_modal(GTK_WINDOW(gui->window), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(gui->window), GTK_WINDOW(parent));

    gui->box = gtk_dialog_get_content_area(GTK_DIALOG(gui->window));

    gui->grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(gui->grid), 15);
    gtk_grid_set_column_spacing(GTK_GRID(gui->grid), 30);
    gtk_widget_set_halign(gui->grid, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(gui->box), gui->grid, TRUE, TRUE, 0);

    gui->titleLabel = gtk_label_new("Nazwa krzyżówki:");
    gtk_grid_attach(GTK_GRID(gui->grid), gui->titleLabel, 0, 1, 1, 1);

    gui->titleEntry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(gui->titleEntry), 30);
    gtk_grid_attach(GTK_GRID(gui->grid), gui->titleEntry, 1, 1, 1, 1);

    gui->widthLabel = gtk_label_new("Szerokość:");
    gtk_grid_attach(GTK_GRID(gui->grid), gui->widthLabel, 0, 2, 1, 1);

    gui->widthSpinButton = gtk_spin_button_new_with_range(3, MAX_WIDTH, 1);
    gtk_entry_set_max_length(GTK_ENTRY(gui->widthSpinButton), 2);
    gtk_grid_attach(GTK_GRID(gui->grid), gui->widthSpinButton, 1, 2, 1, 1);

    gui->heightLabel = gtk_label_new("Wysokość:");
    gtk_grid_attach(GTK_GRID(gui->grid), gui->heightLabel, 0, 3, 1, 1);

    gui->heightSpinButton = gtk_spin_button_new_with_range(3, MAX_HEIGHT, 1);
    gtk_entry_set_max_length(GTK_ENTRY(gui->heightSpinButton), 2);
    gtk_grid_attach(GTK_GRID(gui->grid), gui->heightSpinButton, 1, 3, 1, 1);

    gui->cancelButton = gtk_dialog_add_button(GTK_DIALOG(gui->window), "Anuluj", 0);
    gui->okButton = gtk_dialog_add_button(GTK_DIALOG(gui->window), "Utwórz", 1);

    gtk_widget_show_all(gui->window);
}

int windowNewMakeResult(windowNewGui *gui) {
    char tmp[MAX_TITLE_LENGTH];
    strcpy(tmp, (char*)gtk_entry_get_text(GTK_ENTRY(gui->titleEntry)));
    if(strcmp(tmp, "") != 0) {
        strcpy(gui->result->title, tmp);
        gui->result->size_x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gui->widthSpinButton));
        gui->result->size_y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gui->heightSpinButton));
    }
    else {
        GtkWidget *message = gtk_message_dialog_new(GTK_WINDOW(gui->window),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_WARNING,
                                                    GTK_BUTTONS_OK,
                                                    "Nie wprowadzono nazwy krzyżówki");
        gtk_dialog_run(GTK_DIALOG(message));
        gtk_widget_destroy(message);
        return 0;
    }
    return 1;
}

void windowNewResponseEvent(GtkWidget *widget, guint response_id, gpointer user_data) {
    windowNewGui *gui = user_data;
    if(response_id == 1) {
        gui->response = 1;
        if(!windowNewMakeResult(gui)) {
            gui->response = 0;
            gtk_dialog_run(GTK_DIALOG(gui->window));
        }
    }
    gtk_widget_destroy(gui->window);
}

void windowNewConnectSignals(windowNewGui *gui) {
    g_signal_connect(G_OBJECT(gui->window), "response", G_CALLBACK(windowNewResponseEvent), gui);
}

windowNewGui *newWindowNew() {
    return malloc(sizeof(windowNewGui));
}

gint windowNewRun(windowNewGui *gui, GtkWindow *parent) {
    windowNewCreate(gui, parent);
    windowNewConnectSignals(gui);
    return gtk_dialog_run(GTK_DIALOG(gui->window));
}
