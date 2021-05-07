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
#include "menu_ddlst.h"

#define SUB_PANE_SIZE 7
//typedef struct menu_pane_vtbl menu_pane_vtbl;
typedef struct menu_pane menu_pane;
typedef struct menu_pane_vtbl {
    void (*draw)(menu_pane *this);
    void (*hide)(menu_pane *this);
    void (*update_cursor)(menu_pane *this);
    void (*open)(menu_pane *this);
    void (*close)(menu_pane *this);
} menu_pane_vtbl;
struct menu_pane {
    base_pane base;
    menu_ddlst menu_ddlst_item;  //object that will inherit dDlst_base_c
    bool active;
    J2DScreen screen;
    screen_capture capture;
    base_pane *sub_panes[SUB_PANE_SIZE];

    mDoDvdThd_toMainRam_c * menu_dat_thd;
    request_of_phase_process_class load_menu_dat_request;
};
menu_pane *menu_pane___new(menu_pane *this, JKRArchive *menuArc);
int menu_pane__phase_1(menu_pane *this);
int menu_phase__phase_2(menu_pane *this);
void menu_pane__draw(menu_pane *this);
void menu_pane__hide(menu_pane *this);
void menu_pane__update_cursor(menu_pane *this);
void menu_pane__open(menu_pane *this);
void menu_pane__load_dat(menu_pane *this);
void menu_pane__close(menu_pane *this);
void menu_pane__update_dDlst(menu_pane *this);
#endif