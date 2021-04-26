//sub_pane_vertical.c implementation
#include "../menu/sub_pane_vertical.h"

static sub_pane_vertical_vtbl sub_pane_vertical____vt = {
    sub_pane_vertical_draw,
    sub_pane_vertical_update_cursor
};


void sub_pane_vertical_draw(sub_pane_vertical const *this){

}
void sub_pane_vertical_update_cursor(sub_pane_vertical const *this){

}
void sub_pane_vertical__new(sub_pane_vertical *this, base_pane *parent, float xAxisOffset, float yAxisOffset, char* titleText, text_color_pallete *pallete, JUTFont *font){
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

    sub_pane_setRelative_xAxisOffset(this, xAxisOffset);
    sub_pane_setRelative_yAxisOffset(this, yAxisOffset);

    GzTextBox__new(&this->base.title, this->parent, 0.0f, 0.0f, titleText, pallete, font);
}

void sub_pane_setRelative_xAxisOffset(sub_pane_vertical const *this, float xAxisOffset){
    this->base.xAxisOffset = this->parent.base.xAxisOffset + xAxisOffset;
}
void sub_pane_setRelative_yAxisOffset(sub_pane_vertical const *this, float yAxisOffset){
    this->base.yAxisOffset = this->parent.base.yAxisOffset + yAxisOffset;
}