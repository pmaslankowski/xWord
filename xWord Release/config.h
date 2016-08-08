/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CELL_SIZE 42
#define EDGE_CELL_SIZE 0
#define CORNER_EDGE_SIZE 0
#define FONT_SIZE "12pt"
#define MAX_WIDTH 20
#define MAX_HEIGHT 13
#define MAX_TITLE_LENGTH 25
#define MAX_PATH 512

#define MAIN_WINDOW_TITLE "xWord"
#define MAIN_WINDOW_WIDTH 1000
#define MAIN_WINDOW_HEIGHT 650
#define MAIN_WINDOW_DOWN_TOOLBAR_HEIGHT 38
#define MAIN_WINDOW_DOWN_TOOLBAR_WIDTH 190
#define MAIN_WINDOW_TOGGLE_BUTTONS_START 6
#define MAIN_WINDOW_TOGGLE_BUTTONS_END 8
#define MAIN_WINDOW_TITLE_SPACING 3

#define WINDOW_NEW_TITLE "Tworzenie nowej krzyżówki"
#define WINDOW_NEW_WIDTH 350
#define WINDOW_NEW_HEIGHT 170

#define PROMPT_WINDOW_TITLE "Podpowiedź"
#define PROMPT_WINDOW_HEIGHT 300
#define PROMPT_WINDOW_WIDTH_MARGIN 50
#define PROMPT_WINDOW_WIDTH 300
#define RESULTS_NUMBER 30
#endif
