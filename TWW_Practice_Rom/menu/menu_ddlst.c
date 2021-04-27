#ifndef LOAD_MENU_DDLST_C_INCLUDED
#define LOAD_MENU_DDLST_C_INCLUDED
#include "menu_ddlst.h"

static void* dlst_vtbl[] = {
    NULL, NULL, // rtti placeholder
    dDlst_base_c__dDlst_base_c_destructor, // parent destructor
    menu_ddlst_draw
};

void menu_ddlst___new(menu_ddlst *this, base_pane *menu){
    if(this == 0){
        this = (menu_ddlst*)JKernel__operator_new(sizeof(menu_ddlst));
        if(this == 0){
            OSReport("menu_ddlst___new: Not enough memory to create menu_ddlst");
            return;
        }
    }
        //implement virtual function 'draw' for dDlst_base_c
    this->base.vtbl = dlst_vtbl;
    this->menu = menu; 
}
void menu_ddlst_draw(menu_ddlst *this){
    this->menu->vptr->draw(this->menu);
}

#endif