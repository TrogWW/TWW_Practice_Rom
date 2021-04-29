//sub_pane_vertical.c implementation
#ifndef SUB_PANE_VERTICAL_C_INCLUDED
#define SUB_PANE_VERTICAL_C_INCLUDED

#include "sub_pane_vertical.h"
#include "base_pane.c"
#include "textbox/textbox.c"
static sub_pane_vertical_vtbl sub_pane_vertical____vt = {
    sub_pane_vertical_draw,
    sub_pane_vertical_hide,
    sub_pane_vertical_update_cursor
};


void sub_pane_vertical_draw(sub_pane_vertical *this){
    /*TO DO*/
    this->base.pane->mbDraw = true;
}
void sub_pane_vertical_hide(sub_pane_vertical *this){
    this->base.pane->mbDraw = false;
}
void sub_pane_vertical_update_cursor(sub_pane_vertical *this){
    /*TO DO*/
}

sub_pane_vertical* sub_pane_vertical__new(sub_pane_vertical *this, base_pane *parent, J2DPane *pane, float xAxisOffset, float yAxisOffset, char* titleText, text_color_pallete *pallete, JUTFont *font){
    if(this == 0){
        this = (sub_pane_vertical*)JKernel__operator_new(sizeof(sub_pane_vertical));
        if(this == 0){
            OSReport("GzTextBox__new: Not enough memory to create GzTextBox");
            return;
        }
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&sub_pane_vertical____vt;
    this->parent = parent;
    this->base.pane = pane;

    base_pane_set_title(&this->base, this->parent, xAxisOffset, yAxisOffset, titleText, &TEXT_PALLETE_GREY, 0);
    //GzTextBox__new(&this->base.title, this, 0.0f, 0.0f, titleText, pallete, font);
    return this;
}

#endif