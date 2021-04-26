// menu_pane.h inherits base_pane, this is the root pane
#ifndef MENUPANE_H_INCLUDED
#define MENUPANE_H_INCLUDED
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
#include "screen_capture.h"

typedef struct menu_pane_vtbl menu_pane_vtbl;
typedef struct menu_pane menu_pane;
struct menu_pane_vtbl {
    void (*draw)(menu_pane const *this);
    void (*update_cursor)(menu_pane const *this);
};
struct menu_pane {
    base_pane base;
    dDlst_base_c dDlst_base;  //inherit dDlst_base_c
    bool active;
    J2DScreen screen;
    screen_capture capture;
    base_pane *sub_panes[6]; //TODO define size
};
void menu_pane___new(menu_pane *this, JKRArchive *menuArc);
void menu_pane_draw(menu_pane const *this);
void menu_pane_update_cursor(menu_pane const *this);
void menu_pane__update_dDlst(menu_pane const *this);
#endif