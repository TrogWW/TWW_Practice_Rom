// base_pane.c - Base class for menus implementation
#ifndef BASE_PANE_C_INCLUDED
#define BASE_PANE_C_INCLUDED
#include "base_pane.h"
#include "textbox/text_color_pallete.h"

static base_pane_vtbl base_pane____vt = {
    base_pane_draw,
    base_pane_hide,
    base_pane_update_cursor
};
void base_pane___new(base_pane *this){
    this->vptr = &base_pane____vt;
    this->cursor = 0;             //cursor location
    this->cursor_active = false;     //whether or not cursor for this pane is manipulatable
    //textbox title;        //textbox title                
    //this->xAxisOffset = 0.0f;
    //this->yAxisOffset = 0.0f;
    //this->width = 0.0f;
}

void base_pane_draw(base_pane *this){
    //insert logic here
}
void base_pane_hide(base_pane *this){

}
void base_pane_update_cursor(base_pane *this){
    //insert logic here
}
void base_pane_set_title(base_pane *this, base_pane *relative_pane, float relativeX, float relativeY, char *titleText, text_color_pallete *pallete, JUTResFont *font){
    GzTextBox__new(&this->title, relative_pane, relativeX, relativeY, titleText, &TEXT_PALLETE_WHITE, font);
}

/*
struct TBox2__float__ {
    struct cXy mTL; // 0x08 bytes
    struct cXy mBR; // 0x08 bytes
};
struct cXy {
    float x; // 0x04 bytes
    float y; // 0x04 bytes
};
*/
float base_pane_xOffset(base_pane *this, float xOffset){
    return this->pane->mPosTL.x + xOffset; 
}
float base_pane_yOffset(base_pane *this, float yOffset){
    return this->pane->mPosTL.y + yOffset; 
}
float base_pane_width(base_pane *this){
    //OSReport(MSL_C_PPCEABI_bare_H__printf("base_pane__new (width): this->pane->mPosBR.x = %f | this->pane->mPosTL.x = %f\n",this->pane->mPosBR.x, this->pane->mPosTL.x));
    return this->pane->mPosBR.x - this->pane->mPosTL.x;
}
float base_pane_height(base_pane *this){
    OSReport(MSL_C_PPCEABI_bare_H__printf("base_pane__new (height): this->pane->mPosBR.y = %f | this->pane->mPosTL.y = %f\n",this->pane->mPosBR.y, this->pane->mPosTL.y));
    return this->pane->mPosBR.y - this->pane->mPosTL.y;
}

#endif