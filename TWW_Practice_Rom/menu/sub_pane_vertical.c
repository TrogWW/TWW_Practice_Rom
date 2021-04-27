//sub_pane_vertical.c implementation
#ifndef SUB_PANE_VERTICAL_C_INCLUDED
#define SUB_PANE_VERTICAL_C_INCLUDED
#include "../menu/sub_pane_vertical.h"
#include "textbox/textbox.c"
static sub_pane_vertical_vtbl sub_pane_vertical____vt = {
    sub_pane_vertical_draw,
    sub_pane_vertical_update_cursor
};


void sub_pane_vertical_draw(sub_pane_vertical *this){
    /*TO DO*/
}
void sub_pane_vertical_update_cursor(sub_pane_vertical *this){
    /*TO DO*/
}

sub_pane_vertical* sub_pane_vertical__new(sub_pane_vertical *this, base_pane *parent, float xAxisOffset, float yAxisOffset, char* titleText, text_color_pallete *pallete, JUTFont *font){
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
    this->base.width = this->parent->width;
    sub_pane_setRelative_xAxisOffset(this, xAxisOffset);
    sub_pane_setRelative_yAxisOffset(this, yAxisOffset);

    GzTextBox__new(&this->base.title, this, 0.0f, 0.0f, titleText, pallete, font);
    return this;
}

void sub_pane_setRelative_xAxisOffset(sub_pane_vertical *this, float xAxisOffset){
    this->base.xAxisOffset = this->parent->xAxisOffset + xAxisOffset;
}
void sub_pane_setRelative_yAxisOffset(sub_pane_vertical *this, float yAxisOffset){
    this->base.yAxisOffset = this->parent->yAxisOffset + yAxisOffset;
}
#endif