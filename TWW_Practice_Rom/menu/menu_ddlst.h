#ifndef LOAD_MENU_DDLST_H_INCLUDED
#define LOAD_MENU_DDLST_H_INCLUDED

#pragma region _input_defines
    #ifndef _WW_DEFINES_H
        #define _WW_DEFINES_H "../WW_Hacking_API/vanilla_defines/ww_defines.h"
        #include _WW_DEFINES_H
    #endif
    #ifndef _WW_FUNCTIONS_H
        #define _WW_FUNCTIONS_H "../WW_Hacking_API/vanilla_defines/ww_functions.h"
        #include _WW_FUNCTIONS_H
    #endif
#pragma endregion _input_defines

#include "base_pane.h"
typedef struct menu_ddlst{
    dDlst_base_c base;  //inherit dDlst_base_c
    base_pane *menu;
} menu_ddlst;

void menu_ddlst___new(menu_ddlst *this, base_pane *menu);
void menu_ddlst_draw(menu_ddlst *this);

#endif