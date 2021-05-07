#ifndef INVENTORY_ITEM_C_INCLUDED
#define INVENTORY_ITEM_C_INCLUDED

#include "inventory_item.h"
#include "../base_pane.c"


void inventory_item__new(inventory_item* this, base_pane *parent, float xAxisOffset, float yAxisOffset, char **bti_images, int picture_count){
    if(this == 0){
        this = (inventory_item*)JKernel__operator_new(sizeof(inventory_item));
    }
    this->parent = parent;
    this->pictures = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture) * picture_count);
    for(int i = 0; i < picture_count; i++){
        // OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_item__new *bti_images[%d] = %s\n",i,bti_images[i]));
        J2DPicture__J2DPicture_3(&this->pictures[i], bti_images[i]);
    }

    this->xAxisOffset = base_pane_xOffset(this->parent, xAxisOffset);
    this->yAxisOffset = base_pane_yOffset(this->parent, yAxisOffset);

    this->height = 40.0f;
    this->width = 40.0f;

    this->picture_count = picture_count + 1; //+1 to include 0 index = disabled
    return this;
}
//J2DPicture__draw(&this->picture,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
void inventory_item__draw(inventory_item* this, float scale){
    float scaleOffset = ((this->width * scale) - this->width) / 2;
    if(this->current_index == 0){
        this->pictures[0].field_0x104 = COLOR_ITEM_DISABLED;
        
        J2DPicture__draw(&this->pictures[0],this->xAxisOffset - scaleOffset,this->yAxisOffset - scaleOffset,this->width * scale,this->height * scale,false,false,false);
    }
    else{
        this->pictures[0].field_0x104 = COLOR_WHITE;
        J2DPicture__draw(&this->pictures[this->current_index - 1],this->xAxisOffset -scaleOffset,this->yAxisOffset - scaleOffset,this->width * scale,this->height * scale,false,false,false);
    }  
}
#endif
