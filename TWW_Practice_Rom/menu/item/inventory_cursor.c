#ifndef INVENTORY_CURSOR_C_INCLUDED
#define INVENTORY_CURSOR_C_INCLUDED

#include "inventory_cursor.h"
#include "../base_pane.c"

#define CURSOR_IMAGE_SIZE 15.0f
#define CURSOR_ANIMATION_LENGTH 10
void inventory_cursor__new(inventory_cursor *this, base_pane *parent){
    if(this == 0){
        this = (inventory_cursor*)JKernel__operator_new(sizeof(inventory_cursor));
    }
    this->parent = parent;
    char *cursor_01 = "cursor_00_01.bti";
    char *cursor_02 = "cursor_00_02.bti";
    for(int i = 0; i < 4; i++){
        J2DPicture__J2DPicture_3(&this->cursor_01[i], cursor_01);
    }
    for(int i = 0; i < 4; i++){
        J2DPicture__J2DPicture_3(&this->cursor_02[i], cursor_02);
    }
    this->size = 45.0f;
    this->show_cursor_1 = true;
}
void inventory_cursor__draw(inventory_cursor* this, float xPos, float yPos){
    float xAxisOffset = xPos;//base_pane_xOffset(this->parent, xPos);
    float yAxisOffset = yPos;//base_pane_yOffset(this->parent, yPos);
    J2DPicture *curr_cursor;
    if(this->show_cursor_1){
        curr_cursor = &this->cursor_01;
    }
    else{
        curr_cursor = &this->cursor_02;
    }
    J2DPicture__draw(&curr_cursor[0],xAxisOffset,yAxisOffset,CURSOR_IMAGE_SIZE,CURSOR_IMAGE_SIZE,false,false,false);
    J2DPicture__draw(&curr_cursor[1],xAxisOffset + this->size,yAxisOffset,CURSOR_IMAGE_SIZE,CURSOR_IMAGE_SIZE,true,false,false);
    J2DPicture__draw(&curr_cursor[2],xAxisOffset,yAxisOffset + this->size,CURSOR_IMAGE_SIZE,CURSOR_IMAGE_SIZE,false,true,false);
    J2DPicture__draw(&curr_cursor[3],xAxisOffset + this->size,yAxisOffset + this->size,CURSOR_IMAGE_SIZE,CURSOR_IMAGE_SIZE,true,true,false);
    this->frame = this->frame + 1;
    if(this->frame >= CURSOR_ANIMATION_LENGTH){
        this->frame = 0;
        if(this->show_cursor_1){
            this->show_cursor_1 = false;
        }
        else{
            this->show_cursor_1 = true;
        }
    }
}
#endif