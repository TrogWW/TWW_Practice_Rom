#ifndef SWORDSHIELD_SLOT_H_INCLUDED
#define SWORDSHIELD_SLOT_H_INCLUDED

#include "inventory_base.h"
#include "../base_pane.h"

typedef struct sword_shield_slot{
    inventory_base base;   
    int category;
} sword_shield_slot;

typedef struct sword_shield_slot_vtbl {
    void (*init)(sword_shield_slot *this, base_pane *pane);
    void (*update_data)(sword_shield_slot *this);
    void (*update_inventory)(sword_shield_slot *this);
    void (*draw)(sword_shield_slot *this, float scale);
    void (*execute)(sword_shield_slot *this);
} sword_shield_slot_vtbl;

void sword_shield_slot__init(sword_shield_slot *this, base_pane *pane);
void sword_shield_slot__update_data(sword_shield_slot *this);
void sword_shield_slot__update_inventory(sword_shield_slot *this);

#endif