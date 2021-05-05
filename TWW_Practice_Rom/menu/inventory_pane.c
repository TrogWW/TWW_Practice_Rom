#ifndef INVENTORYPANE_C_INCLUDED
#define INVENTORYPANE_C_INCLUDED

#include "inventory_pane.h"
#include "base_pane.c"
#include "item/inventory_item.c"
#include "item/inventory_cursor.c"
// #define TIMG_TEXT 0x54494d47

// #define it13_TEXT 0x69743133
// #define ITEMICON_RES_NAME "itemicon"

#define INVENTORY_COLS 6
#define INVENTORY_ROWS 5

char **items[26] = {{"telescope.bti"}};
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

    //J2DPicture__J2DPicture_3(&this->picture, "telescope.bti");
    int curr_column = 0;
    int curr_row = -1;
    float xPadding = 20.0;
    float yPadding = 20.0;

    float totalWidth = base_pane_width(&this->base) - xPadding;;
    float totalHeight = base_pane_height(&this->base);

    this->xSpacing = totalWidth / INVENTORY_COLS;
    this->ySpacing = totalWidth / INVENTORY_ROWS;

    for(int i = 0; i < INVENTORY_SIZE; i++){
        //inventory_item__new(inventory_item* this, base_pane *parent, float xAxisOffset, float yAxisOffset, char *bti_images, int picture_count)
        

        curr_column = i % INVENTORY_COLS;
        if(curr_column == 0){
            curr_row = curr_row + 1;
        }
        float thisXPadding = xPadding + (this->xSpacing * curr_column);
        float thisYPadding = yPadding + (this->ySpacing * curr_row);  
        inventory_item__new(&this->inventory[i], this, thisXPadding, thisYPadding, items, 1);
    }
    J2DPicture__J2DPicture_3(&this->arrow, "font_10.bti");
    J2DPicture__J2DPicture_3(&this->r_button, "font_05.bti");

    inventory_cursor__new(&this->cursor, this);
   // OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_pane__new: this->picture = %X\n",&this->picture));
    return this;
}

void inventory_pane__draw(inventory_pane *this){
    this->base.pane->parent.mbDraw = true;
    //J2DPicture__draw(&this->picture,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    for(int i = 0; i < INVENTORY_SIZE; i++){
        if(this->base.cursor_active && i == this->base.cursor){
            inventory_item__draw(&this->inventory[i], 1.25);
        }
        else{
            inventory_item__draw(&this->inventory[i],1.0);
        }
        
    }
    if(this->base.cursor_active){
        int curr_column = this->base.cursor % INVENTORY_COLS;
        int curr_row = this->base.cursor / INVENTORY_COLS;
        
        inventory_cursor__draw(&this->cursor, 10.0f + (this->xSpacing * curr_column),10.0f + (this->ySpacing * curr_row));
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
        this->base.cursor = INVENTORY_SIZE + this->base.cursor;
    }
    else if(this->base.cursor >= INVENTORY_SIZE){
        this->base.cursor = this->base.cursor - INVENTORY_SIZE;
    }

    if(DIGITAL_INPUTS[X].pressed){
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x815, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
        inventory_item *current_item = &this->inventory[this->base.cursor];
        current_item->current_index = current_item->current_index - 1;
        if(current_item->current_index < 0){
            current_item->current_index = current_item->picture_count - 1;
        }
    }
    else if(DIGITAL_INPUTS[Y].pressed){
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x815, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
        inventory_item *current_item = &this->inventory[this->base.cursor];
        current_item->current_index = current_item->current_index + 1;
        if(current_item->current_index >= current_item->picture_count){
            current_item->current_index = 0;
        }
    }
    else if(DIGITAL_INPUTS[R].pressed){
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x8b5, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
    }
}
void inventory_pane__open(inventory_pane *this){

}
void inventory_pane__close(inventory_pane *this){

}
void inventory_pane__update_fields(inventory_pane *this){

}

#endif