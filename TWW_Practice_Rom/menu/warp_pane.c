#ifndef WARPPANE_C_INCLUDED
#define WARPPANE_C_INCLUDED

#include "warp_pane.h"
#include "base_pane.c"
#include "stage/stage_list.c"

static warp_pane_vtbl warp_pane____vt = {
    warp_pane__draw,
    warp_pane__hide,
    warp_pane_update__cursor
};

warp_pane* warp_pane__new(warp_pane *this, base_pane *parent, J2DPane *pane, float relativeX, float relativeY){
    if(this == 0){
        this = (warp_pane*)JKernel__operator_new(sizeof(warp_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&warp_pane____vt;

    this->parent = parent;
    this->base.pane = pane;
    //base_pane *this, base_pane *relative_pane, float relativeX, float relativeY, char *titleText, text_color_pallete *pallete, JUTResFont *font
    base_pane_set_title(&this->base, this->parent, relativeX, relativeY, "Warp", &TEXT_PALLETE_WHITE, 0);

    
    stage_list__new(&this->warp_list);
    stage_list__loadFromDVD(&this->warp_list);

    return this;
}
void warp_pane__draw(warp_pane *this){
    this->base.pane->mbDraw = true;
}
void warp_pane__hide(warp_pane *this){
    this->base.pane->mbDraw = false;
}
void warp_pane_update__cursor(warp_pane *this){

}
#endif