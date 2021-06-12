// display_pane.h inherits base_pane, this is the container for in game display elements
#ifndef DISPLAYPANE_H_INCLUDED
#define DISPLAYPANE_H_INCLUDED

#include "../base_pane.h"

#define DISPLAY_ELEMENTS_SIZE 1
//typedef struct display_pane_vtbl display_pane_vtbl;
typedef struct display_pane display_pane;

typedef struct display_pane_vtbl {
    void (*draw)(display_pane *this);
    void (*hide)(display_pane *this);
    void (*update_cursor)(display_pane *this);
    void (*open)(display_pane *this);
    void (*close)(display_pane *this);
} display_pane_vtbl;

struct display_pane {
    base_pane base;
    menu_ddlst menu_ddlst_item;  //object that will inherit dDlst_base_c
    bool active;
    base_pane *display_panes[DISPLAY_ELEMENTS_SIZE];
};
display_pane *display_pane___new(display_pane *this, J2DScreen *screen);
void display_pane__draw(display_pane *this);
void display_pane__hide(display_pane *this);
void display_pane__update_cursor(display_pane *this);
void display_pane__open(display_pane *this);
void display_pane__close(display_pane *this);
#endif