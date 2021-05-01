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
struct MTX34 {
    float m[3][4]; // 0x30 bytes
};
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
    int offset = (int)this->pane + 224;
    
    float xPadding = this->pane->mMtx.m[0][3];
    TBox2__float__ *winBoxPos = (TBox2__float__ *)(offset);

    
    return xPadding + winBoxPos->mTL.x + xOffset; 
}
float base_pane_yOffset(base_pane *this, float yOffset){
    int offset = (int)this->pane + 224;
    TBox2__float__ *winBoxPos = (TBox2__float__ *)(offset);

    float yPadding = this->pane->mMtx.m[1][3];
    return yPadding + winBoxPos->mTL.y + yOffset; 
}
float base_pane_width(base_pane *this){
    int offset = (int)this->pane + 224;
    TBox2__float__ *winBoxPos = (TBox2__float__ *)(offset);
    //OSReport(MSL_C_PPCEABI_bare_H__printf("base_pane_width: this->pane = %X | this->pane + 0xE0 = %X\n",this->pane, winBoxPos));
    //OSReport(MSL_C_PPCEABI_bare_H__printf("base_pane__new (width): this->pane->mBR.x = %f | this->pane->mTL.x = %f\n",this->pane->mBR.x, this->pane->mTL.x));
    return winBoxPos->mBR.x - winBoxPos->mTL.x;
}
float base_pane_height(base_pane *this){
    int offset = (int)this->pane + 224;
    TBox2__float__ *winBoxPos = (TBox2__float__ *)(offset);
    OSReport(MSL_C_PPCEABI_bare_H__printf("base_pane__new (height): this->pane->mBR.y = %f | this->pane->mTL.y = %f\n",winBoxPos->mBR.y, winBoxPos->mTL.y));
    return winBoxPos->mBR.y - winBoxPos->mTL.y;
}

#endif