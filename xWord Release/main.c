/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include "config.h"
#include "main_gui.h"
#include "crosswords.h"
#include "wordList.h"

int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    mainGui *gui = newMainGui();
    run(gui);
    gtk_main();
    free(gui);
    return 0;
}
