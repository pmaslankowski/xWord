/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#ifndef _GUI_H_
#define _GUI_H_

#include <gtk/gtk.h>
#include "config.h"
#include "crosswords.h"
#include "window_new.h"

struct MainGUI {
    GtkWidget *window, *box, *toolBar, *downToolbar, *separatorToolItem, *layout, *grid;
    GtkWidget *newButton, *openButton, *saveButton, *saveAsButton, *clearButton;
    GtkWidget *newButtonIcon, *openButtonIcon, *saveButtonIcon, *saveAsButtonIcon, *clearButtonIcon;
    GtkWidget *cells[MAX_HEIGHT+2][MAX_WIDTH+2]; //additional 2 for border
    GtkWidget *texts[MAX_HEIGHT+2][MAX_WIDTH+2];
    GtkWidget *eventBoxes[MAX_HEIGHT+2][MAX_WIDTH+2];
    GtkWidget *selectedBorderTop[MAX_HEIGHT+2][MAX_WIDTH+2];
    GtkWidget *selectedBorderRight[MAX_HEIGHT+2][MAX_WIDTH+2];
    GtkWidget *selectedBorderBottom[MAX_HEIGHT+2][MAX_WIDTH+2];
    GtkWidget *selectedBorderLeft[MAX_HEIGHT+2][MAX_WIDTH+2];
    GtkWidget *selectedBorderCorner[4][MAX_HEIGHT+2][MAX_WIDTH+2];
    GtkWidget *focusTarget;

    GtkCssProvider *cssProvider;

    GtkWidget *blackCellButton, *selectCellHorizontalButton, *selectCellVerticalButton, *promptButton; //event boxes
    GtkWidget *blackCellButtonIcon, *selectCellHorizontalButtonIcon, *selectCellVerticalButtonIcon, *promptButtonIcon;

    GdkPixbuf *emptyCellPixbuf, *normalCellPixbuf;
    GdkPixbuf *selectedHorizontalCellPixbuf, *selectedVerticalCellPixbuf, *selectedCornerPixbuf;
    GdkPixbuf *horizontalBorderPixbuf, *verticalBorderPixbuf, *cornerBorderPixbuf;

    gulong blackCellButtonToggledEventId, selectCellHorizontalButtonToggledEventId, selectCellVerticalButtonToggledEventId;
    gulong keyPressedEventId;
    board *board;

    char currentPath[MAX_PATH];
    int modified;
    int selectedX, selectedY, underlined;

    int wordSelectedStartX, wordSelectedEndX, wordSelectedStartY, wordSelectedEndY;
    Orientation selectedOrientation;
};

typedef struct MainGUI mainGui;

typedef enum {EMPTY, NORMAL, SELECTED_HORIZONTAL, SELECTED_VERTICAL,
              SELECTED_CORNER_HORIZONTAL_START, SELECTED_CORNER_HORIZONTAL_END,
              SELECTED_CORNER_VERTICAL_START, SELECTED_CORNER_VERTICAL_END,
              SELECTED_WHOLE} cellType;
typedef enum {VERTICAL, HORIZONTAL, CORNER1, CORNER2, CORNER3, CORNER4} borderType;

void createToolBar(mainGui *gui);
void createDownToolbar(mainGui *gui);
void createMainWindow(mainGui *gui);
int addCell(mainGui *gui, int x, int y);
void setCell(mainGui *gui, int x, int y, cellType type);
cellType getCellState(mainGui *gui, int x, int y);
void addBorder(mainGui *gui, int x, int y, borderType type);
void createBoard(mainGui *gui);
void refreshBoard(mainGui *gui);
void selectWordHorizontal(mainGui *gui, int x, int y);
void selectWordVertical(mainGui *gui, int x, int y);
void setMenuButtonsToggledWithout(mainGui *gui, GtkWidget *widget);
void getFocusedText(mainGui *gui, int *x, int *y);

void loadBoard(mainGui *gui);
void saveBoard(mainGui *gui);

int selectedRefreshTimeoutEvent(mainGui *gui);
void entryChangedEvent(mainGui *gui);
void cellClickedEvent(GtkWidget *widget, GdkEventButton *event, mainGui *gui);
void textClickedEvent(GtkWidget *widget, GdkEventButton *event, mainGui *gui);
void keyPressedEvent(GtkWidget *widget, GdkEventKey *event, mainGui *gui);
void connectBoardSignals(mainGui *gui);

void newButtonClickedEvent(GtkWidget *widget, mainGui *gui);
void openButtonClickedEvent(GtkWidget *widget, mainGui *gui);
void saveButtonClickedEvent(GtkWidget *widget, mainGui *gui);
void saveAsButtonClickedEvent(GtkWidget *widget, mainGui *gui);
void closeButtonClickedEvent(GtkWidget *widget, mainGui *gui);

void blackCellButtonToggledEvent(GtkWidget *widget, mainGui *gui);
void selectCellHorizontalButtonToggledEvent(GtkWidget *widget, mainGui *gui);
void selectCellVerticalButtonToggledEvent(GtkWidget *widget, mainGui *gui);
void promptButtonClickedEvent(GtkWidget *widget, mainGui *gui);

void connectBoardMenuSignals(mainGui *gui);
void connectMainWindowSignals(mainGui *gui);

mainGui *newMainGui();
void run(mainGui *gui);
#endif
