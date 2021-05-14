// base_pane.c - Base class for menus implementation
#ifndef BASE_PANE_C_INCLUDED
#define BASE_PANE_C_INCLUDED
#include "base_pane.h"
#include "textbox/text_color_pallete.h"

static base_pane_vtbl base_pane____vt = {
    base_pane__draw,
    base_pane__hide,
    base_pane__update_cursor,
    base_pane__open,
    base_pane__close
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

void base_pane__draw(base_pane *this){
    //insert logic here
}
void base_pane__hide(base_pane *this){

}
void base_pane__update_cursor(base_pane *this){
    //insert logic here
}
void base_pane__open(base_pane *this){}
void base_pane__close(base_pane *this){}
void base_pane_set_title(base_pane *this, base_pane *relative_pane, float relativeX, float relativeY, char *titleText, text_color_pallete *pallete, JUTResFont *font){
    GzTextBox__new(&this->title, relative_pane, relativeX, relativeY, titleText, &TEXT_PALLETE_WHITE, font,1.1f);
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
    TBox2__float__ *winBoxPos = &this->pane->mWindowBox;
    
    float xPadding = this->pane->parent.mMtx.m[0][3];

    
    return xPadding + winBoxPos->mTL.x + xOffset; 
}
float base_pane_yOffset(base_pane *this, float yOffset){
    TBox2__float__ *winBoxPos = &this->pane->mWindowBox;

    float yPadding = this->pane->parent.mMtx.m[1][3];
    return yPadding + winBoxPos->mTL.y + yOffset; 
}
float base_pane_width(base_pane *this){
    TBox2__float__ *winBoxPos = &this->pane->mWindowBox;
    return winBoxPos->mBR.x - winBoxPos->mTL.x;
}
float base_pane_height(base_pane *this){
    TBox2__float__ *winBoxPos = &this->pane->mWindowBox;
    return winBoxPos->mBR.y - winBoxPos->mTL.y;
}

#endif