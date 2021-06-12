#ifndef WATCHES_DISPLAY_H_INCLUDED
#define WATCHES_DISPLAY_H_INCLUDED

#include "../base_pane.h"


typedef struct watches_display_pane watches_display_pane;

typedef struct watches_display_pane_vtbl {
    void (*draw)(watches_display_pane *this);
    void (*hide)(watches_display_pane *this);
    void (*update_cursor)(watches_display_pane *this);
    void (*open)(watches_display_pane *this);
    void (*close)(watches_display_pane *this);
} watches_display_pane_vtbl;

struct watches_display_pane {
    base_pane base;
    J2DScreen *screen;
    J2DWindow *info_window;
    menu_ddlst watches_display_ddlst_item;  //object that will inherit dDlst_base_c
    JSUPtrList watches_list;    //linked list of watches_display_textbox displaying watches
};

typedef struct watches_display_textbox {
    watch_item *watch;
    GzTextBox *textbox;
} watches_display_textbox;

watches_display_pane *watches_display_pane___new(watches_display_pane *this, J2DScreen *screen);
void watches_display_pane__draw(watches_display_pane *this);
void watches_display_pane__hide(watches_display_pane *this);
void watches_display_pane__update_cursor(watches_display_pane *this);
void watches_display_pane__open(watches_display_pane *this);
void watches_display_pane__close(watches_display_pane *this);


void watches_display_pane__update_dDlst(watches_display_pane *this);
void watches_display_pane__add_watch(watches_display_pane *this, watch_item *watch);
void watches_display_pane__create_list(watches_display_pane *this, watch_category_list *watches_list);

#endif