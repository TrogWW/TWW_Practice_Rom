// base_pane.c - Base class for menus implementation
#ifndef BASE_PANE_C_INCLUDED
#define BASE_PANE_C_INCLUDED
#include "../menu/base_pane.h"

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
    this->xAxisOffset = 0.0f;
    this->yAxisOffset = 0.0f;
    this->width = 0.0f;
}

void base_pane_draw(base_pane *this){
    //insert logic here
}
void base_pane_hide(base_pane *this){

}
void base_pane_update_cursor(base_pane *this){
    //insert logic here
}
#endif