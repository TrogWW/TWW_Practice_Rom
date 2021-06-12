#ifndef LOAD_MENU_DDLST_H_INCLUDED
#define LOAD_MENU_DDLST_H_INCLUDED

#include "base_pane.h"
typedef struct menu_ddlst{
    dDlst_base_c base;  //inherit dDlst_base_c
    base_pane *menu;
} menu_ddlst;

void menu_ddlst___new(menu_ddlst *this, base_pane *menu);
void menu_ddlst_draw(menu_ddlst *this);

#endif