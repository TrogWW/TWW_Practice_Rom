#ifndef WATCHES_PANE_C_INCLUDED
#define WATCHES_PANE_C_INCLUDED

#include "watches_pane.h"
#include "watch/watch_category_list.c"
#include "textbox/textbox.c"
#include "textbox/text_color_pallete.h"
#include "../tools/wiird_loader_context.c"

static watches_pane_vtbl watches_pane____vt = {
    watches_pane__draw,
    watches_pane__hide,
    watches_pane__update_cursor,
    watches_pane__open,
    watches_pane__close
};

watches_pane__set_data(watches_pane *this, void *data){
    this->category_list = (watch_category_list *)data;
    watch_category_list__new(this->category_list, (int)data);
    OSReport(MSL_C_PPCEABI_bare_H__printf("watches_pane__set_data: this->category_list = %X | first category = %s \n",&this->category_list, this->category_list->watch_categories[0].category));
}
watches_pane* watches_pane__new(watches_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY){
    if(this == 0){
        this = (watches_pane*)JKernel__operator_new(sizeof(watches_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&watches_pane____vt;  //inherit base_pane class

    this->parent = parent;
    this->base.pane = pane;

    base_pane_set_title(&this->base, this->parent, relativeX, relativeY, "Watches", &TEXT_PALLETE_WHITE, 0);
    return this;
}
void watches_pane__draw(watches_pane *this){}
void watches_pane__hide(watches_pane *this){}
void watches_pane__update_cursor(watches_pane *this){}
void watches_pane__open(watches_pane *this){}
void watches_pane__close(watches_pane *this){}


#endif