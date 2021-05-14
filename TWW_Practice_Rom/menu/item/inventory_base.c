#ifndef INVENTORY_BASE_C_INCLUDED
#define INVENTORY_BASE_C_INCLUDED

#include "inventory_base.h"

static inventory_base_vtbl inventory_base____vt = {
    inventory_base__init,
    inventory_base__update_data,
    inventory_base__update_inventory,
    inventory_base__draw,
    inventory_base__execute
};

void inventory_base__init(inventory_base *this, base_pane *pane){
    this->vptr = &inventory_base____vt;
    this->parent = pane;
    this->pictures = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture) * (this->item_count - 1));
    for(int i = 1; i < this->item_count; i++){
        char *bti_image = inventory_base__getIconFilenameByIndex(this,i);
        J2DPicture__J2DPicture_3(&this->pictures[i- 1], bti_image);
        //OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_slot__initData: bti_image = %s | curr_pic = %X | %X\n",bti_image, &this->pictures[i - 1], &g_dComIfG_gameInfo.mPlay));
    }
    
}
void inventory_base__update_data(inventory_base *this){}
void inventory_base__update_inventory(inventory_base *this){}
void inventory_base__draw(inventory_base *this, float scale){
    int picture_index = 0;
    int current_item = this->items[this->item_index];
    //char *bti_image = 0;
    J2DPicture *curr_picture = 0;
    if(current_item == 0){
        picture_index = 0;
    }
    else{
        picture_index = ((int)this->item_index) - 1;
    }
    float scaleOffset = ((IMAGE_WIDTH * scale) - IMAGE_WIDTH) / 2;
    if(current_item == 0){
        this->pictures[picture_index].mColorBase = COLOR_ITEM_DISABLED;
    }
    else{
        this->pictures[picture_index].mColorBase = COLOR_WHITE;
    }
    J2DPicture__draw(&this->pictures[picture_index], this->x_offset - scaleOffset, this->y_offset - scaleOffset, IMAGE_WIDTH * scale, IMAGE_HEIGHT * scale,false,false,false);
}
void inventory_base__execute(inventory_base *this){
    if(DIGITAL_INPUTS[Y].pressed){
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x815, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
        this->item_index = this->item_index - 1;
        if(this->item_index < 0){
            this->item_index = this->item_count - 1;
        }       
    }
    else if(DIGITAL_INPUTS[X].pressed){
        JAIZelBasic__seStart(JAIZelBasic__zel_basic, 0x815, 0, 0,0, 1.0, 1.0, -1.0, -1.0, 0);
        this->item_index = this->item_index + 1;
        if(this->item_index >= this->item_count){
            this->item_index = 0;
        }
    }
}


char* inventory_base__getIconFilenameByIndex(inventory_base *this, int index){
    if(index < this->item_count){
        dItem_data_item_resource *item_resource = &dItem_data__item_resource[(char)this->items[index]];
        return item_resource->mIconFilename;
    }
    else{
        return 0;
    }
}
char* inventory_base__getIconFilename(inventory_base *this){
    dItem_data_item_resource *item_resource = &dItem_data__item_resource[(char)this->items[this->item_index]];
    return item_resource->mIconFilename;
}

#endif
