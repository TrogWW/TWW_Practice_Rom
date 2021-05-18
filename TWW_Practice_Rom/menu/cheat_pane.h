#ifndef CHEAT_PANE_H_INCLUDED
#define CHEAT_PANE_H_INCLUDED

#define CODES_LIMIT 12
#define CATEGORIES_LIMIT 6

#include "base_pane.h"
#include "textbox/textbox.h"
#include "cheat/wiird_category_list.h"


typedef struct cheat_pane cheat_pane;
typedef struct cheat_pane_vtbl {
    void (*draw)(cheat_pane *this);
    void (*hide)(cheat_pane *this);
    void (*update_cursor)(cheat_pane *this);
    void (*open)(cheat_pane *this);
    void (*close)(cheat_pane *this);
} cheat_pane_vtbl;

struct cheat_pane {
    base_pane base;
    base_pane *parent;
    wiird_category_list *category_list;
    int curr_category_index;
    bool category_window_enabled;
    GzTextBox cheats[CODES_LIMIT];
    GzTextBox categories[CATEGORIES_LIMIT];
};
cheat_pane__set_cheat_data(cheat_pane *this, void *data);
cheat_pane* cheat_pane__new(cheat_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY);
void cheat_pane__draw(cheat_pane *this);
void cheat_pane__hide(cheat_pane *this);
void cheat_pane__update_cursor(cheat_pane *this);
void cheat_pane__open(cheat_pane *this);
void cheat_pane__close(cheat_pane *this);

#endif