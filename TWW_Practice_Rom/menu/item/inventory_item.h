

#ifndef INVENTORY_ITEM_H_INCLUDED
#define INVENTORY_ITEM_H_INCLUDED

#include "../base_pane.h"

typedef struct inventory_item {
    base_pane *parent;
    int picture_count;
    int current_index;
    J2DPicture *pictures;
    float xAxisOffset;
    float yAxisOffset;
    float width;
    float height;
} inventory_item;

void inventory_item__new(inventory_item* this, base_pane *parent, float xAxisOffset, float yAxisOffset, char **bti_images, int picture_count);
void inventory_item__draw(inventory_item* this, float scale);

#endif