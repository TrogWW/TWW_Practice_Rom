#ifndef INVENTORYPANE_C_INCLUDED
#define INVENTORYPANE_C_INCLUDED

#include "inventory_pane.h"
#include "base_pane.c"
#include "item/inventory_slot.c"
#include "item/sword_shield_slot.c"
#include "item/inventory_cursor.c"


inventory_base *inventory_slots[INVENTORY_SIZE] = {  
    &slot0,
    &slot1,
    &slot2,
    &slot3,
    &slot4,
    &slot5,
    &slot6,
    &slot7,
    &slot8,
    &slot9,
    &slot10,
    &slot11,
    &slot12,
    &slot13,
    &slot14,
    &slot15,
    &slot16,
    &slot17,
    &slot18,
    &slot19,
    &slot20,
    &ss_slot0,
    &ss_slot1
   // &ss_items2
};

static inventory_pane_vtbl inventory_pane____vt = {
    inventory_pane__draw,
    inventory_pane__hide,
    inventory_pane__update_cursor,
    inventory_pane__open,
    inventory_pane__close
};
inventory_pane* inventory_pane__new(inventory_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY){
    if(this == 0){
        this = (inventory_pane*)JKernel__operator_new(sizeof(inventory_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&inventory_pane____vt;

    this->parent = parent;
    this->base.pane = pane;

    base_pane_set_title(&this->base, this->parent, relativeX, relativeY, "Inventory", &TEXT_PALLETE_WHITE_70, 0);

    for(int i = 0; i < INVENTORY_SIZE; i++){
        inventory_slots[i]->vptr->init(inventory_slots[i], &this->base);
    }
    J2DPicture__J2DPicture_3(&this->arrow, "font_10.bti");
    J2DPicture__J2DPicture_3(&this->r_button, "font_05.bti");

    inventory_cursor__new(&this->cursor, this);
   // OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_pane__new: this->picture = %X\n",&this->picture));
    return this;
}
void inventory_pane__update_item_slots(inventory_pane *this){
    for(int i = 0; i < INVENTORY_SIZE; i++){
        inventory_slots[i]->vptr->update_data(inventory_slots[i]);
        //inventory_slot__setIndex(&inventory_slots[i]);
    }
}
void inventory_pane__draw(inventory_pane *this){
    //d_item__execItemGet(dItem_data__ItemNo__MasterSwordHalfPower);
    // for(int i = 0; i < 200; i++){
    //     d_item__execItemGet(i);
    // }

   // dItem_data_item_resource *item_resource = &dItem_data__item_resource[dItem_data__ItemNo__LightArrow];
    //OSReport(MSL_C_PPCEABI_bare_H__printf("item_resource = %X\n",item_resource));
    //inventory_pane__set_item_slots(this);
    this->base.pane->parent.mbDraw = true;
    //J2DPicture__draw(&this->picture,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    for(int i = 0; i < INVENTORY_SIZE; i++){
        inventory_base *slot = inventory_slots[i];
        slot->vptr->update_inventory(slot);
        //inventory_slot__execGetItem(&inventory_slots[i]);
        if(this->base.cursor_active && i == this->base.cursor){
            slot->vptr->draw(slot, 1.25);
            //inventory_slot__draw(&inventory_slots[i], 1.25);
        }
        else{
            slot->vptr->draw(slot, 1.0);
            //inventory_slot__draw(&inventory_slots[i], 1.0);
        }
        
    }
    if(this->base.cursor_active){
        inventory_base *active_slot = inventory_slots[this->base.cursor];
        inventory_cursor__draw(&this->cursor, active_slot->x_offset - 10.0f, active_slot->y_offset - 10.0f);
    }
    int last_column = 4;
    int last_row = INVENTORY_ROWS - 1; 
    float finalX = 10.0f + (this->xSpacing * last_column);
    float finalY = 10.0f + (this->ySpacing * last_row);
    finalX = base_pane_xOffset(&this->base, finalX) + 45.0f;
    finalY = base_pane_yOffset(&this->base, finalY) + 15.0f;
    //OSReport(MSL_C_PPCEABI_bare_H__printf("finalX = %f | finalY = %f\n",finalX, finalY));
    J2DPicture__draw(&this->r_button,finalX,finalY,30.0f,30.0f,false,false,false);
    J2DPicture__draw(&this->arrow,finalX + 35.0f,finalY + 5.0f,20.0f,20.0f,true,true,true);
    //OSReport(MSL_C_PPCEABI_bare_H__printf("&this->picture = %X\n",&this->picture));
}
void inventory_pane__hide(inventory_pane *this){
    this->base.pane->parent.mbDraw = false;
}
void inventory_pane__update_cursor(inventory_pane *this){
    //inventory_pane__set_item_slots(this);
    if(DIGITAL_INPUTS[D_PAD_UP].pressed){
        this->base.cursor = this->base.cursor - INVENTORY_COLS;
        //JAISound * * JAIZelBasic__seStart(JAIZelBasic * this, ulong soundId, cXyz * param_2, ulong param_3, sbyte param_4, float param_5, float param_6, float param_7, float param_8, byte param_9);
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x80e, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
    }
    if(DIGITAL_INPUTS[D_PAD_DOWN].pressed){
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x80e, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
        this->base.cursor = this->base.cursor + INVENTORY_COLS;
    }
    if(DIGITAL_INPUTS[D_PAD_LEFT].pressed){
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x80e, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
        if(this->base.cursor % INVENTORY_COLS == 0){
            this->parent->cursor_active = true;
            this->base.cursor = 0;
            this->base.cursor_active = false;
            return;
        }
        this->base.cursor = this->base.cursor - 1;
    }
    if(DIGITAL_INPUTS[D_PAD_RIGHT].pressed){
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x80e, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
        this->base.cursor = this->base.cursor + 1;
    }

    if(this->base.cursor < 0){
        int last_row_size = INVENTORY_SIZE % INVENTORY_COLS;

        this->base.cursor = INVENTORY_SIZE + this->base.cursor + (INVENTORY_COLS - last_row_size);
        if(this->base.cursor >= INVENTORY_SIZE){
            this->base.cursor = this->base.cursor - INVENTORY_COLS;
        }
    }
    else if(this->base.cursor >= INVENTORY_SIZE){
        this->base.cursor = this->base.cursor - INVENTORY_SIZE;
    }
    if(this->base.cursor_active){
        inventory_base *current_item = inventory_slots[this->base.cursor];
        current_item->vptr->execute(current_item);
        if(DIGITAL_INPUTS[R].pressed){
            JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x8b5, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
        }
    }
}
void inventory_pane__open(inventory_pane *this){
    inventory_pane__update_item_slots(this);       //set inventory item values
}
void inventory_pane__close(inventory_pane *this){
    this->base.pane->parent.mbDraw = false;
}

#endif