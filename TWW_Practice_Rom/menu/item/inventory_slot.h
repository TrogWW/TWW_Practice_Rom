#ifndef INVENTORY_SLOT_H_INCLUDED
#define INVENTORY_SLOT_H_INCLUDED

#include "inventory_base.h"
#include "../base_pane.h"

typedef struct inventory_slot{
    inventory_base base;   
    char slot_index;
} inventory_slot;

typedef struct inventory_slot_vtbl {
    void (*init)(inventory_slot *this, base_pane *pane);
    void (*update_data)(inventory_slot *this);
    void (*update_inventory)(inventory_slot *this);
    void (*draw)(inventory_slot *this, float scale);
    void (*execute)(inventory_slot *this);
} inventory_slot_vtbl;

void inventory_slot__init(inventory_slot *this, base_pane *pane);
void inventory_slot__update_data(inventory_slot *this);
void inventory_slot__update_inventory(inventory_slot *this);

#endif