/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#ifndef _WINDOW_NEW_H_
#define _WINDOW_NEW_H_
#include <gtk/gtk.h>
#include "main_gui.h"
#include "crosswords.h"


struct WindowNewGui {
    GtkWidget *window, *box, *grid, *titleLabel, *widthLabel, *heightLabel, *okButton, *cancelButton;
    GtkWidget *titleEntry, *widthSpinButton, *heightSpinButton;
    GtkWidget *cssProvider;

    board *result;
    int response;
};

typedef struct WindowNewGui windowNewGui;

void windowNewCreate(windowNewGui *gui, GtkWindow *parent);
int windowNewMakeResult(windowNewGui *gui);

void windowNewResponseEvent(GtkWidget *widget, guint response_id, gpointer user_data);
void windowNewConnectSignals(windowNewGui *gui);

windowNewGui *newWindowNew();
gint windowNewRun(windowNewGui *gui, GtkWindow *parent);
#endif
