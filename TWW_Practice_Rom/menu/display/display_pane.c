#ifndef DISPLAYPANE_C_INCLUDED
#define DISPLAYPANE_C_INCLUDED

#include "display_pane.h"
#include "../base_pane.c"

#define INFO_TEXT 0x494e464f


static display_pane_vtbl display_pane____vt = {
    display_pane__draw,
    display_pane__hide,
    display_pane__update_cursor,
    display_pane__open,
    display_pane__close
};

display_pane *display_pane___new(display_pane *this, J2DScreen *screen){
    if(this == 0){
        this = (display_pane*)JKernel__operator_new(sizeof(display_pane));
    }
    
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&display_pane____vt;

    J2DWindow* info_window = (J2DWindow*)J2DScreen__search(screen, INFO_TEXT);
    this->base.pane = info_window;
    

    J2DWindow* watches_window = (J2DWindow*)J2DScreen__search(screen, RMID_TEXT);
    OSReport(MSL_C_PPCEABI_bare_H__printf("display_pane___new: watches_window = %X\n",watches_window));

    this->active = false;
    this->base.cursor_active = false;
    return this;
}
void display_pane__draw(display_pane *this){ }
void display_pane__hide(display_pane *this){ }
void display_pane__update_cursor(display_pane *this){ }
void display_pane__open(display_pane *this){ }
void display_pane__close(display_pane *this){ }

#endif