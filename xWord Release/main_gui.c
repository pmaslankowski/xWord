/*Projekt ze wstępu do programowania w C
xWord - program do tworzenia krzyżówek typu "Jolka"
Autor: Piotr Maślankowski
Nr indeksu: 280354
Data ukończenia: 8.02.2016r.
*/


#include <gtk/gtk.h>
#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "crosswords.h"
#include "window_new.h"
#include "promptWindow.h"

void createToolBar(mainGui *gui) {
    gui->newButtonIcon = gtk_image_new_from_file("graphics/icons/buttonNew.png");
    gui->newButton = GTK_WIDGET(gtk_tool_button_new(gui->newButtonIcon, NULL));
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->newButton), "Nowa krzyżówka");
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->newButton), 0);

    gui->openButtonIcon = gtk_image_new_from_file("graphics/icons/buttonOpen.png");
    gui->openButton = GTK_WIDGET(gtk_tool_button_new(gui->openButtonIcon, NULL));
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->openButton), "Otwórz krzyżówkę");
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->openButton), 1);

    gui->saveButtonIcon = gtk_image_new_from_file("graphics/icons/buttonSave.png");
    gui->saveButton = GTK_WIDGET(gtk_tool_button_new(gui->saveButtonIcon, NULL));
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->saveButton), "Zapisz krzyżówkę");
    gtk_widget_set_sensitive(gui->saveButton, FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->saveButton), 2);

    gui->saveAsButtonIcon = gtk_image_new_from_file("graphics/icons/buttonSaveAs.png");
    gui->saveAsButton = GTK_WIDGET(gtk_tool_button_new(gui->saveAsButtonIcon, NULL));
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->saveAsButton), "Zapisz krzyżówkę jako...");
    gtk_widget_set_sensitive(gui->saveAsButton, FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->saveAsButton), 3);

    gui->clearButtonIcon = gtk_image_new_from_file("graphics/icons/buttonClear.png");
    gui->clearButton = GTK_WIDGET(gtk_tool_button_new(gui->clearButtonIcon, NULL));
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->clearButton), "Zamknij krzyżówkę");
    gtk_widget_set_sensitive(gui->clearButton, FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->clearButton), 4);

    gui->separatorToolItem = GTK_WIDGET(gtk_separator_tool_item_new());
    gtk_tool_item_set_expand(GTK_TOOL_ITEM(gui->separatorToolItem), TRUE);
    gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(gui->separatorToolItem), FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->separatorToolItem), 5);

    gui->blackCellButtonIcon = gtk_image_new_from_file("graphics/icons/buttonBlackCell.png");
    gui->blackCellButton = GTK_WIDGET(gtk_toggle_tool_button_new());
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(gui->blackCellButton), gui->blackCellButtonIcon);
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->blackCellButton), "Blokowanie komórek");
    gtk_widget_set_sensitive(gui->blackCellButton, FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->blackCellButton), 6);

    gui->selectCellVerticalButtonIcon = gtk_image_new_from_file("graphics/icons/selectCellVerticalIcon.png");
    gui->selectCellVerticalButton = GTK_WIDGET(gtk_toggle_tool_button_new());
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(gui->selectCellVerticalButton), gui->selectCellVerticalButtonIcon);
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->selectCellVerticalButton), "Zaznaczanie pionowe");
    gtk_widget_set_sensitive(gui->selectCellVerticalButton, FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->selectCellVerticalButton), 7);

    gui->selectCellHorizontalButtonIcon = gtk_image_new_from_file("graphics/icons/selectCellHorizontalIcon.png");
    gui->selectCellHorizontalButton = GTK_WIDGET(gtk_toggle_tool_button_new());
    gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(gui->selectCellHorizontalButton), gui->selectCellHorizontalButtonIcon);
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->selectCellHorizontalButton), "Zaznaczanie poziome");
    gtk_widget_set_sensitive(gui->selectCellHorizontalButton, FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->selectCellHorizontalButton), 8);

    gui->promptButtonIcon = gtk_image_new_from_file("graphics/icons/buttonPromptIcon.png");
    gui->promptButton = GTK_WIDGET(gtk_tool_button_new(gui->promptButtonIcon, NULL));
    gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(gui->promptButton), "Podpowiedź");
    gtk_widget_set_sensitive(gui->promptButton, FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(gui->toolBar), GTK_TOOL_ITEM(gui->promptButton), 9);
}

void createMainWindow(mainGui *gui) {
    gui->board = create();
    gui->selectedX = 0;
    gui->selectedY = 0;
    gui->modified = 0;
    gui->grid = NULL;
    gui->currentPath[0] = '\0';

    gui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(gui->window), MAIN_WINDOW_TITLE);
    gtk_window_set_position(GTK_WINDOW(gui->window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(gui->window), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT + MAIN_WINDOW_DOWN_TOOLBAR_HEIGHT);

    gui->cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(gui->cssProvider), "mainStyle.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(gui->cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gui->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(gui->window), gui->box);

    gui->toolBar = gtk_toolbar_new();
    gui->layout = gtk_layout_new(NULL, NULL);

    gui->focusTarget = gtk_button_new_with_label("This button takes default focus - it's tricky.");

    gtk_box_pack_start(GTK_BOX(gui->box), gui->focusTarget, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(gui->box), gui->toolBar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(gui->box), gui->layout, TRUE, TRUE, 0);

    createToolBar(gui);

    gui->emptyCellPixbuf = gdk_pixbuf_new_from_file("graphics/boardCellEmpty.png", NULL);
    gui->normalCellPixbuf = gdk_pixbuf_new_from_file("graphics/boardCell.png", NULL);
    gui->selectedHorizontalCellPixbuf = gdk_pixbuf_new_from_file("graphics/boardCellSelectedHorizontal.png", NULL);
    gui->selectedVerticalCellPixbuf = gdk_pixbuf_new_from_file("graphics/boardCellSelectedVertical.png", NULL);
    gui->selectedCornerPixbuf = gdk_pixbuf_new_from_file("graphics/boardCellSelectedCorner.png", NULL);
    gui->verticalBorderPixbuf = gdk_pixbuf_new_from_file("graphics/verticalBorder.png", NULL);
    gui->horizontalBorderPixbuf = gdk_pixbuf_new_from_file("graphics/horizontalBorder.png", NULL);
    gui->cornerBorderPixbuf = gdk_pixbuf_new_from_file("graphics/cornerBorder.png", NULL);

    gtk_widget_show_all(gui->window);
    gtk_widget_hide(gui->focusTarget);
}

int addCell(mainGui *gui, int x, int y) {
    if(x > MAX_WIDTH || y > MAX_HEIGHT)
        return 0;
    gui->cells[y][x] = gtk_image_new_from_pixbuf(gui->emptyCellPixbuf);
    gui->selectedBorderTop[y][x] = gtk_image_new_from_pixbuf(gui->selectedHorizontalCellPixbuf);
    gui->selectedBorderRight[y][x] = gtk_image_new_from_pixbuf(gui->selectedVerticalCellPixbuf);
    gui->selectedBorderBottom[y][x] = gtk_image_new_from_pixbuf(gui->selectedHorizontalCellPixbuf);
    gui->selectedBorderLeft[y][x] = gtk_image_new_from_pixbuf(gui->selectedVerticalCellPixbuf);
    for(int i=0; i < 4; i++)
        gui->selectedBorderCorner[i][y][x] = gtk_image_new_from_pixbuf(gui->selectedCornerPixbuf);

    gtk_widget_set_valign(gui->selectedBorderTop[y][x], GTK_ALIGN_START);
    gtk_widget_set_halign(gui->selectedBorderRight[y][x], GTK_ALIGN_END);
    gtk_widget_set_valign(gui->selectedBorderBottom[y][x], GTK_ALIGN_END);
    gtk_widget_set_halign(gui->selectedBorderLeft[y][x], GTK_ALIGN_START);

    gtk_widget_set_halign(gui->selectedBorderCorner[0][y][x], GTK_ALIGN_START);
    gtk_widget_set_valign(gui->selectedBorderCorner[0][y][x], GTK_ALIGN_START);
    gtk_widget_set_halign(gui->selectedBorderCorner[1][y][x], GTK_ALIGN_END);
    gtk_widget_set_valign(gui->selectedBorderCorner[1][y][x], GTK_ALIGN_START);
    gtk_widget_set_halign(gui->selectedBorderCorner[2][y][x], GTK_ALIGN_END);
    gtk_widget_set_valign(gui->selectedBorderCorner[2][y][x], GTK_ALIGN_END);
    gtk_widget_set_halign(gui->selectedBorderCorner[3][y][x], GTK_ALIGN_START);
    gtk_widget_set_valign(gui->selectedBorderCorner[3][y][x], GTK_ALIGN_END);


    gui->eventBoxes[y][x] = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(gui->eventBoxes[y][x]), gui->cells[y][x]);
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(gui->eventBoxes[y][x]), FALSE);

    gui->texts[y][x] = gtk_label_new("   ");
    gtk_label_set_max_width_chars(GTK_LABEL(gui->texts[y][x]), 1);
    gtk_widget_set_name(gui->texts[y][x], "texts");

    gtk_grid_attach(GTK_GRID(gui->grid), gui->texts[y][x], x, y, 1, 1);
    gtk_grid_attach(GTK_GRID(gui->grid), gui->selectedBorderTop[y][x], x, y, 1, 1);
    gtk_grid_attach(GTK_GRID(gui->grid), gui->selectedBorderRight[y][x], x, y, 1, 1);
    gtk_grid_attach(GTK_GRID(gui->grid), gui->selectedBorderBottom[y][x], x, y, 1, 1);
    gtk_grid_attach(GTK_GRID(gui->grid), gui->selectedBorderLeft[y][x], x, y, 1, 1);
    for(int i=0; i < 4; i++)
        gtk_grid_attach(GTK_GRID(gui->grid), gui->selectedBorderCorner[i][y][x], x, y, 1, 1);
    gtk_grid_attach(GTK_GRID(gui->grid), gui->eventBoxes[y][x], x, y, 1, 1);

    gtk_widget_show_all(gui->eventBoxes[y][x]);
    return 1;
}

void setCell(mainGui *gui, int x, int y, cellType type) {
    if(x > MAX_WIDTH || y > MAX_HEIGHT)
        return;
    switch(type) {
        case EMPTY:
            setCell(gui, x, y, NORMAL);
            gtk_image_set_from_pixbuf(GTK_IMAGE(gui->cells[y][x]), gui->emptyCellPixbuf);
            gtk_widget_hide(gui->texts[y][x]);
            gtk_label_set_text(GTK_LABEL(gui->texts[y][x]), "   ");
            gtk_label_set_pattern(GTK_LABEL(gui->texts[y][x]), "");
            if(gui->selectedX == x && gui->selectedY == y) {
                gui->selectedX = 0;
                gui->selectedY = 0;
            }
            gui->board->cells[y][x] = '0';
            break;
        case NORMAL:
            gtk_image_set_from_pixbuf(GTK_IMAGE(gui->cells[y][x]), gui->normalCellPixbuf);
            gtk_widget_show(gui->texts[y][x]);

            gtk_widget_hide(gui->selectedBorderTop[y][x]);
            gtk_widget_hide(gui->selectedBorderRight[y][x]);
            gtk_widget_hide(gui->selectedBorderBottom[y][x]);
            gtk_widget_hide(gui->selectedBorderLeft[y][x]);
            for(int i=0; i<4; i++)
                gtk_widget_hide(gui->selectedBorderCorner[i][y][x]);
            if(gui->board->cells[y][x] == '0')
                gui->board->cells[y][x] = '1';
            break;
        case SELECTED_HORIZONTAL:
            setCell(gui, x, y, NORMAL);
            gtk_widget_show(gui->selectedBorderTop[y][x]);
            gtk_widget_show(gui->selectedBorderBottom[y][x]);
            for(int i=0; i < 4; i++)
                gtk_widget_show(gui->selectedBorderCorner[i][y][x]);
            break;
        case SELECTED_VERTICAL:
            setCell(gui, x, y, NORMAL);
            gtk_widget_show(gui->selectedBorderRight[y][x]);
            gtk_widget_show(gui->selectedBorderLeft[y][x]);
            for(int i=0; i < 4; i++)
                gtk_widget_show(gui->selectedBorderCorner[i][y][x]);
            break;
        case SELECTED_CORNER_HORIZONTAL_START:
            setCell(gui, x, y, NORMAL);
            gtk_widget_show(gui->selectedBorderTop[y][x]);
            gtk_widget_show(gui->selectedBorderBottom[y][x]);
            gtk_widget_show(gui->selectedBorderLeft[y][x]);
            for(int i=0; i < 4; i++)
                gtk_widget_show(gui->selectedBorderCorner[i][y][x]);
            break;
        case SELECTED_CORNER_VERTICAL_START:
            setCell(gui, x, y, NORMAL);
            gtk_widget_show(gui->selectedBorderRight[y][x]);
            gtk_widget_show(gui->selectedBorderLeft[y][x]);
            gtk_widget_show(gui->selectedBorderTop[y][x]);
            for(int i=0; i < 4; i++)
                gtk_widget_show(gui->selectedBorderCorner[i][y][x]);
            break;
        case SELECTED_CORNER_HORIZONTAL_END:
            setCell(gui, x, y, NORMAL);
            gtk_widget_show(gui->selectedBorderTop[y][x]);
            gtk_widget_show(gui->selectedBorderBottom[y][x]);
            gtk_widget_show(gui->selectedBorderRight[y][x]);
            for(int i=0; i < 4; i++)
                gtk_widget_show(gui->selectedBorderCorner[i][y][x]);
            break;
        case SELECTED_CORNER_VERTICAL_END:
            setCell(gui, x, y, NORMAL);
            gtk_widget_show(gui->selectedBorderRight[y][x]);
            gtk_widget_show(gui->selectedBorderLeft[y][x]);
            gtk_widget_show(gui->selectedBorderBottom[y][x]);
            for(int i=0; i < 4; i++)
                gtk_widget_show(gui->selectedBorderCorner[i][y][x]);
            break;
        case SELECTED_WHOLE:
            setCell(gui, x, y, NORMAL);
            gtk_widget_show(gui->selectedBorderRight[y][x]);
            gtk_widget_show(gui->selectedBorderLeft[y][x]);
            gtk_widget_show(gui->selectedBorderTop[y][x]);
            gtk_widget_show(gui->selectedBorderBottom[y][x]);
            for(int i=0; i < 4; i++)
                gtk_widget_show(gui->selectedBorderCorner[i][y][x]);
            break;
        }
}

cellType getCellState(mainGui *gui, int x, int y) {
    if(x < 1 || y < 1 || x > gui->board->size_x || y > gui->board->size_y)
        return EMPTY;
    if(gui->board->cells[y][x] != '0')
        return NORMAL;
    else
        return EMPTY;
}

void addBorder(mainGui *gui, int x, int y, borderType type) {
    gui->cells[y][x] = gtk_image_new();
    switch(type) {
        case VERTICAL:
            gtk_image_set_from_pixbuf(GTK_IMAGE(gui->cells[y][x]), gui->verticalBorderPixbuf);
            gtk_widget_set_halign(gui->cells[y][x], GTK_ALIGN_END);
            break;
        case HORIZONTAL:
            gtk_image_set_from_pixbuf(GTK_IMAGE(gui->cells[y][x]), gui->horizontalBorderPixbuf);
            gtk_widget_set_valign(gui->cells[y][x], GTK_ALIGN_END);
            break;
        case CORNER1:
            gtk_image_set_from_pixbuf(GTK_IMAGE(gui->cells[y][x]), gui->cornerBorderPixbuf);
            gtk_widget_set_valign(gui->cells[y][x], GTK_ALIGN_END);
            gtk_widget_set_halign(gui->cells[y][x], GTK_ALIGN_END);
            break;
        case CORNER2:
            gtk_image_set_from_pixbuf(GTK_IMAGE(gui->cells[y][x]), gui->cornerBorderPixbuf);
            gtk_widget_set_valign(gui->cells[y][x], GTK_ALIGN_END);
            gtk_widget_set_halign(gui->cells[y][x], GTK_ALIGN_START);
            break;
        case CORNER3:
            gtk_image_set_from_pixbuf(GTK_IMAGE(gui->cells[y][x]), gui->cornerBorderPixbuf);
            gtk_widget_set_valign(gui->cells[y][x], GTK_ALIGN_START);
            gtk_widget_set_halign(gui->cells[y][x], GTK_ALIGN_START);
        case CORNER4:
            gtk_image_set_from_pixbuf(GTK_IMAGE(gui->cells[y][x]), gui->cornerBorderPixbuf);
            gtk_widget_set_valign(gui->cells[y][x], GTK_ALIGN_START);
            gtk_widget_set_halign(gui->cells[y][x], GTK_ALIGN_END);
            break;
    }
    gtk_grid_attach(GTK_GRID(gui->grid), gui->cells[y][x], x, y, 1, 1);
    gtk_widget_show(gui->cells[y][x]);
}

void createBoard(mainGui *gui) {
    if(gui->grid != NULL)
        gtk_widget_destroy(gui->grid);

    gui->selectedX = 0;
    gui->selectedY = 0;

    gui->wordSelectedStartY = 0;
    gui->wordSelectedEndY = 0;
    gui->wordSelectedStartX = 0;
    gui->wordSelectedEndX = 0;
    gui->selectedOrientation = NONE;

    gui->grid = gtk_grid_new();
    gint start_x = MAIN_WINDOW_WIDTH/2 - gui->board->size_x*(CELL_SIZE+2)/2; //we add 2 for border
    gint start_y = MAIN_WINDOW_HEIGHT/2 - gui->board->size_y*(CELL_SIZE+2)/2;
    gtk_layout_put(GTK_LAYOUT(gui->layout), gui->grid, start_x, start_y);
    gtk_widget_show(gui->grid);
    for(int i=1; i<=gui->board->size_y; i++) {
        addBorder(gui, 0, i, VERTICAL);
        addBorder(gui, gui->board->size_x+1, i, VERTICAL);
    }
    for(int i=1; i<=gui->board->size_x; i++) {
        addBorder(gui, i, 0, HORIZONTAL);
        addBorder(gui, i, gui->board->size_y+1, HORIZONTAL);
    }
    addBorder(gui, 0, 0, CORNER1);
    addBorder(gui, gui->board->size_x+1, 0, CORNER2);
    addBorder(gui, gui->board->size_x+1, gui->board->size_y+1, CORNER3);
    addBorder(gui, 0, gui->board->size_y+1, CORNER4);

    for(int i=1; i<=gui->board->size_y; i++)
        for(int j=1; j<=gui->board->size_x; j++)
            addCell(gui, j, i);

    g_timeout_add(300, (GSourceFunc)selectedRefreshTimeoutEvent, gui);
    connectBoardSignals(gui);
}

void refreshBoard(mainGui *gui) {
    for(int i=1; i <= gui->board->size_x; i++)
        for(int j=1; j <= gui->board->size_y; j++)
            if(getCellState(gui, i, j) != EMPTY)
                setCell(gui, i, j, NORMAL);

    gui->wordSelectedStartY = 0;
    gui->wordSelectedEndY = 0;
    gui->wordSelectedStartX = 0;
    gui->wordSelectedEndX = 0;
    gui->selectedOrientation = NONE;
    gtk_widget_set_sensitive(gui->promptButton, FALSE);
}

void selectWordHorizontal(mainGui *gui, int x, int y) {
    gint start_x=x; gint end_x=x;

    while(start_x >= 1 && getCellState(gui, start_x, y) != EMPTY)
        start_x--;
    if(getCellState(gui, start_x, y) == EMPTY)
        start_x++;

    while(end_x <= gui->board->size_x && getCellState(gui, end_x, y) != EMPTY)
        end_x++;
    if(getCellState(gui, end_x, y) == EMPTY)
        end_x--;

    if(start_x != end_x) {
        setCell(gui, start_x, y, SELECTED_CORNER_HORIZONTAL_START);
        for(int i=start_x+1; i < end_x; i++)
            setCell(gui, i, y, SELECTED_HORIZONTAL);
        setCell(gui, end_x, y, SELECTED_CORNER_HORIZONTAL_END);
    } else setCell(gui, x, y, SELECTED_WHOLE);

    gui->wordSelectedStartY = y;
    gui->wordSelectedEndY = y;
    gui->wordSelectedStartX = start_x;
    gui->wordSelectedEndX = end_x;
    gui->selectedOrientation = HOR;
}

void selectWordVertical(mainGui *gui, int x, int y) {
    gint start_y = y; gint end_y=y;

    while(start_y >= 1 && getCellState(gui, x, start_y) != EMPTY)
        start_y--;
    if(getCellState(gui, x, start_y) == EMPTY)
                start_y++;

    while(end_y <= gui->board->size_y && getCellState(gui, x, end_y) != EMPTY)
        end_y++;
    if(getCellState(gui, x, end_y) == EMPTY)
        end_y--;

    if(start_y != end_y) {
        setCell(gui, x, start_y, SELECTED_CORNER_VERTICAL_START);
        for(int i=start_y+1; i < end_y; i++)
            setCell(gui, x, i, SELECTED_VERTICAL);
        setCell(gui, x, end_y, SELECTED_CORNER_VERTICAL_END);
    } else setCell(gui, x, y, SELECTED_WHOLE);

    gui->wordSelectedStartY = start_y;
    gui->wordSelectedEndY = end_y;
    gui->wordSelectedStartX = x;
    gui->wordSelectedEndX = x;
    gui->selectedOrientation = VERT;
}

void setMenuButtonsToggledWithout(mainGui *gui, GtkWidget *widget) {
    g_signal_handler_disconnect(gui->blackCellButton, gui->blackCellButtonToggledEventId);
    g_signal_handler_disconnect(gui->selectCellHorizontalButton, gui->selectCellHorizontalButtonToggledEventId);
    g_signal_handler_disconnect(gui->selectCellVerticalButton, gui->selectCellVerticalButtonToggledEventId);

    GtkWidget *tmp;
    for(int i=MAIN_WINDOW_TOGGLE_BUTTONS_START; i<=MAIN_WINDOW_TOGGLE_BUTTONS_END; i++)
        if((tmp=GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(gui->toolBar), i))) != widget || !gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(widget)))
            gtk_toggle_tool_button_set_active(GTK_TOGGLE_TOOL_BUTTON(tmp), FALSE);
        else
            gtk_toggle_tool_button_set_active(GTK_TOGGLE_TOOL_BUTTON(widget), TRUE);

    connectBoardMenuSignals(gui);
}

void getFocusedText(mainGui *gui, int *x, int *y) {
    int found=0;
    for(int i=1; i <= gui->board->size_y; i++) {
        for(int j=1; j <= gui->board->size_x; j++)
            if(gtk_widget_has_focus(gui->texts[i][j])) {
                *x=j; *y=i; found=1; break;
            }
        if(found)
            break;
    }
}

void loadBoard(mainGui *gui) {
    for(int i=1; i <= gui->board->size_y; i++) {
        for(int j=1; j <= gui->board->size_x; j++) {
            if(gui->board->cells[i][j] == '0')
                setCell(gui, j, i, EMPTY);
            else
                setCell(gui, j, i, NORMAL);

            if(gui->board->cells[i][j] > '1') {
                gchar tmp[2];
                tmp[0] = gui->board->cells[i][j];
                tmp[1] = 0;
                gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), tmp);
            } else {
                switch(gui->board->cells[i][j]) {
                    case 0: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ą"); break;
                    case 1: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ć"); break;
                    case 2: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ę"); break;
                    case 3: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ł"); break;
                    case 4: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ń"); break;
                    case 5: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ó"); break;
                    case 6: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ś"); break;
                    case 7: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ż"); break;
                    case 8: gtk_label_set_text(GTK_LABEL(gui->texts[i][j]), "Ź"); break;
                }
            }
        }
    }
}

int selectedRefreshTimeoutEvent(mainGui *gui) {
    if(gui->grid == NULL)
        return 0;
    if(gui->selectedX != 0 && gui->selectedY != 0) {
        if(gui->underlined == 1) {
            gtk_label_set_pattern(GTK_LABEL(gui->texts[gui->selectedY][gui->selectedX]), "");
            gui->underlined = 0;
        } else {
            gtk_label_set_pattern(GTK_LABEL(gui->texts[gui->selectedY][gui->selectedX]), "___");
            gui->underlined = 1;
        }
    }
    return 1;
}

void cellClickedEvent(GtkWidget *widget, GdkEventButton *event, mainGui *gui) {
    gint x, y;
    gtk_container_child_get(GTK_CONTAINER(gui->grid), widget, "left-attach", &x, "top-attach", &y, NULL);

    refreshBoard(gui);
    if(gui->selectedX != 0 && gui->selectedY != 0)
        gtk_label_set_pattern(GTK_LABEL(gui->texts[gui->selectedY][gui->selectedX]), "");
    gui->selectedX = 0;
    gui->selectedY = 0;

    if(gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(gui->blackCellButton))) {
        if(gui->modified == 0) {
            gui->modified = 1;
            char tmp[100];
            sprintf(tmp, "%s [%s*] - xWord", gui->board->title, gui->currentPath);
            gtk_window_set_title(GTK_WINDOW(gui->window), tmp);
        }
        if(getCellState(gui, x, y) == EMPTY)
            setCell(gui, x, y, NORMAL);
        else
            setCell(gui, x, y, EMPTY);
    }
    else
    if(gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(gui->selectCellVerticalButton))) {
        gtk_widget_grab_focus(gui->texts[y][x]);
        if(getCellState(gui, x, y) != EMPTY) {
            selectWordVertical(gui, x, y);
            gtk_toggle_tool_button_set_active(GTK_TOGGLE_TOOL_BUTTON(gui->selectCellVerticalButton), FALSE);
            gtk_widget_set_sensitive(gui->promptButton, TRUE);
        }
    }
    else
    if(gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(gui->selectCellHorizontalButton))) {
        gtk_widget_grab_focus(gui->texts[y][x]);
        if(getCellState(gui, x, y) != EMPTY) {
            selectWordHorizontal(gui, x, y);
            gtk_toggle_tool_button_set_active(GTK_TOGGLE_TOOL_BUTTON(gui->selectCellHorizontalButton), FALSE);
            gtk_widget_set_sensitive(gui->promptButton, TRUE);
        }
    }
    else {
        if(getCellState(gui, x, y) != EMPTY) {
            gui->selectedX = x;
            gui->selectedY = y;
        }
    }
}

void textClickedEvent(GtkWidget *widget, GdkEventButton *event, mainGui *gui) {
    refreshBoard(gui);
    if(gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(gui->blackCellButton)) ||
       gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(gui->selectCellHorizontalButton)) ||
       gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(gui->selectCellVerticalButton))) {
        cellClickedEvent(widget, event, gui);
    }
}

void keyPressedEvent(GtkWidget *widget, GdkEventKey *event, mainGui *gui) {
    int x, y;
    if(gui->selectedX == 0 || gui->selectedY == 0)
        return;

    refreshBoard(gui);

    x = gui->selectedX; y = gui->selectedY;
    int next_x = x;
    int next_y = y;
    switch(event->keyval) {
        case GDK_KEY_Up:
            next_y--;
            break;
        case GDK_KEY_Down:
            next_y++;
            break;
        case GDK_KEY_Left:
            next_x--;
            break;
        case GDK_KEY_Right:
            next_x++;
            break;
        case GDK_KEY_BackSpace:
            gtk_label_set_text(GTK_LABEL(gui->texts[y][x]), "   ");
            setCell(gui, x, y, NORMAL);
            gui->board->cells[y][x] = '1';
            break;
    }

    if(!(next_x >= 1 && next_y >= 1 && next_x <= gui->board->size_x && next_y <= gui->board->size_y && getCellState(gui, next_x, next_y) != EMPTY)) {
        next_x = x; next_y = y;
    }

    if(gui->selectedX != 0 && gui->selectedY != 0 && (next_x != x || next_y != y))
        gtk_label_set_pattern(GTK_LABEL(gui->texts[gui->selectedY][gui->selectedX]), "");

    gui->selectedX = next_x;
    gui->selectedY = next_y;


    switch(event->keyval) {
        case GDK_KEY_Aogonek:
        case GDK_KEY_aogonek:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ą");
            gui->board->cells[next_y][next_x] = 0;
            break;
        case GDK_KEY_Cacute:
        case GDK_KEY_cacute:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ć");
            gui->board->cells[next_y][next_x] = 1;
            break;
        case GDK_KEY_Eogonek:
        case GDK_KEY_eogonek:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ę");
            gui->board->cells[next_y][next_x] = 2;
            break;
        case GDK_KEY_Lstroke:
        case GDK_KEY_lstroke:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ł");
            gui->board->cells[next_y][next_x] = 3;
            break;
        case GDK_KEY_Nacute:
        case GDK_KEY_nacute:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ń");
            gui->board->cells[next_y][next_x] = 4;
        break;
        case GDK_KEY_Oacute:
        case GDK_KEY_oacute:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ó");
            gui->board->cells[next_y][next_x] = 5;
        break;
        case GDK_KEY_Sacute:
        case GDK_KEY_sacute:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ś");
            gui->board->cells[next_y][next_x] = 6;
        break;
        case GDK_KEY_Zabovedot:
        case GDK_KEY_zabovedot:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ż");
            gui->board->cells[next_y][next_x] = 7;
        break;
        case GDK_KEY_Zacute:
        case GDK_KEY_zacute:
            gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), "Ź");
            gui->board->cells[next_y][next_x] = 8;
        break;
    }


    if(((event->keyval >= 65 && event->keyval <= 90) || (event->keyval >= 97 && event->keyval <= 122))) {
        gchar tmp[2];
        tmp[0] = g_ascii_toupper(event->keyval);
        tmp[1] = 0;
        gtk_label_set_text(GTK_LABEL(gui->texts[next_y][next_x]), tmp);
        setCell(gui, next_x, next_y, NORMAL);
        gui->board->cells[next_y][next_x] = tmp[0];
        if(gui->modified == 0) {
            gui->modified = 1;
            char tmp[100];
            sprintf(tmp, "%s [%s*] - xWord", gui->board->title, gui->currentPath);
            gtk_window_set_title(GTK_WINDOW(gui->window), tmp);
        }
    }

    gtk_widget_grab_focus(gui->focusTarget);
}

void connectBoardSignals(mainGui *gui) {
    for(int i=1; i<=gui->board->size_y; i++) {
        for(int j=1; j<=gui->board->size_x; j++) {
            g_signal_connect(gui->eventBoxes[i][j], "button_press_event", G_CALLBACK(cellClickedEvent), gui);
            g_signal_connect(gui->texts[i][j], "button_press_event", G_CALLBACK(textClickedEvent), gui);
        }
    }
    if(gui->keyPressedEventId == 0)
        gui->keyPressedEventId = g_signal_connect(gui->window, "key_press_event", G_CALLBACK(keyPressedEvent), gui);
}

void newButtonClickedEvent(GtkWidget *widget, mainGui *gui) {
    closeButtonClickedEvent(widget, gui);

    windowNewGui *dialog = newWindowNew();
    windowNewRun(dialog, GTK_WINDOW(gui->window));
    int response = dialog->response;
    if(response == 0)
        return;

    if(gui->board == NULL)
        gui->board = create();
    strcpy(gui->board->title, dialog->result->title);
    gui->board->size_x = dialog->result->size_x;
    gui->board->size_y = dialog->result->size_y;
    clearBoard(gui->board);
    createBoard(gui);

    char tmp[100];
    sprintf(tmp, "%s [] - xWord", gui->board->title);
    gtk_window_set_title(GTK_WINDOW(gui->window), tmp);
    free(dialog);

    gtk_widget_set_sensitive(gui->saveButton, TRUE);
    gtk_widget_set_sensitive(gui->saveAsButton, TRUE);
    gtk_widget_set_sensitive(gui->clearButton, TRUE);
    gtk_widget_set_sensitive(gui->blackCellButton, TRUE);
    gtk_widget_set_sensitive(gui->selectCellVerticalButton, TRUE);
    gtk_widget_set_sensitive(gui->selectCellHorizontalButton, TRUE);
    gtk_widget_set_sensitive(gui->promptButton, TRUE);
}

void openButtonClickedEvent(GtkWidget *widget, mainGui *gui) {
    closeButtonClickedEvent(widget, gui);

    GtkWidget *dialog = gtk_file_chooser_dialog_new("Otwórz krzyżówkę",
                                                    GTK_WINDOW(gui->window),
                                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "_Anuluj",
                                                    GTK_RESPONSE_CANCEL,
                                                    "_Otwórz",
                                                    GTK_RESPONSE_ACCEPT,
                                                    NULL);
    GtkFileFilter *fileFilter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(fileFilter, "*.xw");
    gtk_file_filter_set_name(fileFilter, "(*.xw) projekt xWord");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), fileFilter);

    gint response;
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    if(response == GTK_RESPONSE_ACCEPT) {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        strcpy(gui->currentPath, filename);
        if(gui->board == NULL)
            gui->board = create();
        if(boardLoadFromFile(gui->board, filename) == 0) {
            createBoard(gui);
            loadBoard(gui);

            char tmp[100];
            sprintf(tmp, "%s [ %s ] - xWord", gui->board->title, gui->currentPath);
            gtk_window_set_title(GTK_WINDOW(gui->window), tmp);
        }
        g_free(filename);

        gtk_widget_set_sensitive(gui->saveButton, TRUE);
        gtk_widget_set_sensitive(gui->saveAsButton, TRUE);
        gtk_widget_set_sensitive(gui->clearButton, TRUE);
        gtk_widget_set_sensitive(gui->blackCellButton, TRUE);
        gtk_widget_set_sensitive(gui->selectCellVerticalButton, TRUE);
        gtk_widget_set_sensitive(gui->selectCellHorizontalButton, TRUE);
        gtk_widget_set_sensitive(gui->promptButton, TRUE);
    }
    gtk_widget_destroy(dialog);
}

void saveButtonClickedEvent(GtkWidget *widget, mainGui *gui) {
        if(gui->currentPath[0] != '\0') {
            if(boardSaveToFile(gui->board, gui->currentPath) == 0) {
                char tmp[100];
                sprintf(tmp, "%s [ %s ] - xWord", gui->board->title, gui->currentPath);
                gtk_window_set_title(GTK_WINDOW(gui->window), tmp);
                gui->modified = 0;
            }
            else {
                GtkWidget *error= gtk_message_dialog_new(GTK_WINDOW(gui->window),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Wystąpił błąd podczas zapisywania do pliku.");
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }
        } else {
            saveAsButtonClickedEvent(widget, gui);
        }
}

void saveAsButtonClickedEvent(GtkWidget *widget, mainGui *gui) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Zapisz krzyżówkę",
                                                    GTK_WINDOW(gui->window),
                                                    GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "_Anuluj",
                                                    GTK_RESPONSE_CANCEL,
                                                    "_Zapisz",
                                                    GTK_RESPONSE_ACCEPT,
                                                    NULL);
    GtkFileFilter *fileFilter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(fileFilter, "*.xw");
    gtk_file_filter_set_name(fileFilter, "(*.xw) projekt xWord");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), fileFilter);

    gint response;
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    if(response == GTK_RESPONSE_ACCEPT) {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if(boardSaveToFile(gui->board, filename) == 0) {
            char tmp[100];
            strcpy(gui->currentPath, filename);
            sprintf(tmp, "%s [ %s ] - xWord", gui->board->title, filename);
            gtk_window_set_title(GTK_WINDOW(gui->window), tmp);
            gui->modified = 0;
        } else {
            GtkWidget *error= gtk_message_dialog_new(GTK_WINDOW(gui->window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "Wystąpił błąd podczas zapisywania do pliku.");
            gtk_dialog_run(GTK_DIALOG(error));
            gtk_widget_destroy(error);
        }
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void closeButtonClickedEvent(GtkWidget *widget, mainGui *gui) {
    if(gui->grid != NULL) {
        if(gui->modified == 1) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gui->window),
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_WARNING,
                                                       GTK_BUTTONS_NONE,
                                                       "Aktualny plik został zmodyfikowany. Czy chcesz zapisać zmiany?");
            gtk_dialog_add_button(GTK_DIALOG(dialog), "Nie", GTK_RESPONSE_NO);
            gtk_dialog_add_button(GTK_DIALOG(dialog), "Tak", GTK_RESPONSE_YES);

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));
            if(response == GTK_RESPONSE_YES)
                saveButtonClickedEvent(widget, gui);
            gtk_widget_destroy(dialog);
        }

        gui->currentPath[0] = '\0';
        gtk_window_set_title(GTK_WINDOW(gui->window), "xWord");
        gtk_widget_destroy(gui->grid);
        gui->grid = NULL;
        gui->selectedX = 0;
        gui->selectedY = 0;
        free(gui->board);
        gui->board = NULL;
        gui->modified = 0;

        gtk_widget_set_sensitive(gui->saveButton, FALSE);
        gtk_widget_set_sensitive(gui->saveAsButton, FALSE);
        gtk_widget_set_sensitive(gui->clearButton, FALSE);
        gtk_widget_set_sensitive(gui->blackCellButton, FALSE);
        gtk_widget_set_sensitive(gui->selectCellVerticalButton, FALSE);
        gtk_widget_set_sensitive(gui->selectCellHorizontalButton, FALSE);
        gtk_widget_set_sensitive(gui->promptButton, FALSE);
    }
}

void blackCellButtonToggledEvent(GtkWidget *widget, mainGui *gui) {
    setMenuButtonsToggledWithout(gui, widget);
}

void selectCellHorizontalButtonToggledEvent(GtkWidget *widget, mainGui *gui) {
    setMenuButtonsToggledWithout(gui, widget);
}

void selectCellVerticalButtonToggledEvent(GtkWidget *widget, mainGui *gui) {
    setMenuButtonsToggledWithout(gui, widget);
}

void promptButtonClickedEvent(GtkWidget *widget, mainGui *gui) {
    if(gui->selectedOrientation == NONE)
        return;

    //arrays of polish characters codes - utf8
    char polishFirst[9]  = {0xC4, 0xC4, 0xC4, 0xC5, 0xC5, 0xC3, 0xC5, 0xC5, 0xC5};
    char polishSecond[9] = {0x84, 0x86, 0x98, 0x81, 0x83, 0x93, 0x9A, 0xB9, 0xBB};

    int j=0;
    int length=0;
    char word[64]; //max length of word in crossword equals 20
    if(gui->selectedOrientation == HOR) {
        for(int i=gui->wordSelectedStartX; i <= gui->wordSelectedEndX; i++) {
            length = gui->wordSelectedEndX - gui->wordSelectedStartX + 1;
            if(gui->board->cells[gui->wordSelectedStartY][i] > 10 &&
               gui->board->cells[gui->wordSelectedStartY][i] != '0' &&
               gui->board->cells[gui->wordSelectedStartY][i] != '1')
                word[j++] = gui->board->cells[gui->wordSelectedStartY][i];
            if(gui->board->cells[gui->wordSelectedStartY][i] >= 0 &&
                gui->board->cells[gui->wordSelectedStartY][i] < 9) {
                word[j++] = polishFirst[gui->board->cells[gui->wordSelectedStartY][i]];
                word[j++] = polishSecond[gui->board->cells[gui->wordSelectedStartY][i]];
            }
            if(gui->board->cells[gui->wordSelectedStartY][i] == '1')
                word[j++] = '.';
        }
        word[j++] = 0;
    }
    else
    if(gui->selectedOrientation == VERT) {
        length = gui->wordSelectedEndY - gui->wordSelectedStartY + 1;
        for(int i=gui->wordSelectedStartY; i <= gui->wordSelectedEndY; i++) {
            if(gui->board->cells[i][gui->wordSelectedStartX] > 10 &&
               gui->board->cells[i][gui->wordSelectedStartX] != '0' &&
               gui->board->cells[i][gui->wordSelectedStartX] != '1')
                word[j++] = gui->board->cells[i][gui->wordSelectedStartX];
            if(gui->board->cells[i][gui->wordSelectedStartX] >= 0 &&
                gui->board->cells[i][gui->wordSelectedStartX] < 9) {
                word[j++] = polishFirst[gui->board->cells[i][gui->wordSelectedStartX]];
                word[j++] = polishSecond[gui->board->cells[i][gui->wordSelectedStartX]];
            }
            if(gui->board->cells[i][gui->wordSelectedStartX] == '1')
                word[j++] = '.';
        }
        word[j++] = 0;
    }

    PromptWindowGui *dialog = newPromptWindow(GTK_WINDOW(gui->window), word, gui->selectedOrientation, length);
    gtk_dialog_run(GTK_DIALOG(dialog->window));
    strcpy(word, dialog->wordResult);
    if(dialog->response == 0) {
        free(dialog);
        return;
    } else
        free(dialog);

    if(gui->selectedOrientation == VERT) {
        j=0;
        int pos=gui->wordSelectedStartY;
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
                    gtk_label_set_text(GTK_LABEL(gui->texts[pos][gui->wordSelectedStartX]), tmp);
                    gui->board->cells[pos][gui->wordSelectedStartX] = tmp[0];
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
                gtk_label_set_text(GTK_LABEL(gui->texts[pos][gui->wordSelectedStartX]), tmp);
                gui->board->cells[pos][gui->wordSelectedStartX] = polishCharSecond;
            }
            j++;
            pos++;
        }
    } else {
        j=0;
        int pos=gui->wordSelectedStartX;
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
                    gtk_label_set_text(GTK_LABEL(gui->texts[gui->wordSelectedStartY][pos]), tmp);
                    gui->board->cells[gui->wordSelectedStartY][pos] = tmp[0];
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
                gtk_label_set_text(GTK_LABEL(gui->texts[gui->wordSelectedStartY][pos]), tmp);
                gui->board->cells[gui->wordSelectedStartY][pos] = polishCharSecond;
            }
            j++;
            pos++;
        }
    }
    refreshBoard(gui);
}

void connectMainMenuSignals(mainGui *gui) {
    g_signal_connect(G_OBJECT(gui->newButton), "clicked", G_CALLBACK(newButtonClickedEvent), gui);
    g_signal_connect(G_OBJECT(gui->openButton), "clicked", G_CALLBACK(openButtonClickedEvent), gui);
    g_signal_connect(G_OBJECT(gui->saveButton), "clicked", G_CALLBACK(saveButtonClickedEvent), gui);
    g_signal_connect(G_OBJECT(gui->saveAsButton), "clicked", G_CALLBACK(saveAsButtonClickedEvent), gui);
    g_signal_connect(G_OBJECT(gui->clearButton), "clicked", G_CALLBACK(closeButtonClickedEvent), gui);
    g_signal_connect(G_OBJECT(gui->promptButton), "clicked", G_CALLBACK(promptButtonClickedEvent), gui);
}

void connectBoardMenuSignals(mainGui *gui) {
    gui->blackCellButtonToggledEventId = g_signal_connect(G_OBJECT(gui->blackCellButton), "toggled", G_CALLBACK(blackCellButtonToggledEvent), gui);
    gui->selectCellHorizontalButtonToggledEventId = g_signal_connect(G_OBJECT(gui->selectCellHorizontalButton), "toggled", G_CALLBACK(selectCellHorizontalButtonToggledEvent), gui);
    gui->selectCellVerticalButtonToggledEventId = g_signal_connect(G_OBJECT(gui->selectCellVerticalButton), "toggled", G_CALLBACK(selectCellVerticalButtonToggledEvent), gui);
}

void connectMainWindowSignals(mainGui *gui) {
    g_signal_connect(G_OBJECT(gui->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    connectMainMenuSignals(gui);
    connectBoardMenuSignals(gui);
}

mainGui *newMainGui() {
    return malloc(sizeof(mainGui));
}

void run(mainGui *gui) {
    createMainWindow(gui);
    connectMainWindowSignals(gui);
}
