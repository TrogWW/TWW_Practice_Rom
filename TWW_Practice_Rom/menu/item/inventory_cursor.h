#ifndef INVENTORY_CURSOR_H_INCLUDED
#define INVENTORY_CURSOR_H_INCLUDED

#include "../base_pane.h"

typedef struct inventory_cursor {
    base_pane *parent;
    J2DPicture cursor_01[4];
    J2DPicture cursor_02[4];
    int frame;
    bool show_cursor_1;
    float size;
} inventory_cursor;

void inventory_cursor__new(inventory_cursor* this, base_pane *parent);
void inventory_cursor__draw(inventory_cursor* this, float xPos, float yPos);
#endif