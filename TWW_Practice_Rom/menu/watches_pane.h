#ifndef WATCHES_PANE_H_INCLUDED
#define WATCHES_PANE_H_INCLUDED

#include "base_pane.h"
#include "textbox/textbox.h"
#include "watch/watch_category_list.h"


typedef struct watches_pane watches_pane;
typedef struct watches_pane_vtbl {
    void (*draw)(watches_pane *this);
    void (*hide)(watches_pane *this);
    void (*update_cursor)(watches_pane *this);
    void (*open)(watches_pane *this);
    void (*close)(watches_pane *this);
} watches_pane_vtbl;

struct watches_pane {
    base_pane base;
    base_pane *parent;
    watch_category_list *category_list;
};
watches_pane__set_data(watches_pane *this, void *data);
watches_pane* watches_pane__new(watches_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY);
void watches_pane__draw(watches_pane *this);
void watches_pane__hide(watches_pane *this);
void watches_pane__update_cursor(watches_pane *this);
void watches_pane__open(watches_pane *this);
void watches_pane__close(watches_pane *this);

#endif