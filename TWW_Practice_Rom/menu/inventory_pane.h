#ifndef INVENTORYPANE_H_INCLUDED
#define INVENTORYPANE_H_INCLUDED

#include "base_pane.h"
#include "item/inventory_cursor.h"
//#include "item/inventory_item.h"

#define INVENTORY_SIZE 23
#define INVENTORY_COLS 7
#define INVENTORY_ROWS 4

typedef struct inventory_pane inventory_pane;
typedef struct inventory_pane_vtbl {
    void (*draw)(inventory_pane *this);
    void (*hide)(inventory_pane *this);
    void (*update_cursor)(inventory_pane *this);
    void (*open)(inventory_pane *this);
    void (*close)(inventory_pane *this);
} inventory_pane_vtbl;

struct inventory_pane {
    base_pane base;
    base_pane *parent;
    //inventory_item inventory[INVENTORY_SIZE];
    inventory_cursor cursor;
    //J2DPicture title_collect;
    J2DPicture arrow; //font_10.bti
    J2DPicture r_button; //font_05.bti
    float xSpacing;
    float ySpacing;
};

inventory_pane* inventory_pane__new(inventory_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY);
void inventory_pane__draw(inventory_pane *this);
void inventory_pane__hide(inventory_pane *this);
void inventory_pane__update_cursor(inventory_pane *this);
void inventory_pane__open(inventory_pane *this);
void inventory_pane__close(inventory_pane *this);
void inventory_pane__update_item_slots(inventory_pane *this);
#endif
