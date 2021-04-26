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

#include "settings.h"
#include "input.h"
#include "menu/load_menu_context.h"
#include "menu/menu_pane.h"

load_menu_context load_menu_ctx = {
    .mPhaseRequest = 0,
    .phase = 0,
    .mMenuResArc = 0
};

menu_pane *main_pane = 0;

void _menu_exec(Settings* settings){
    if(load_menu_ctx.phase != cPhs_COMPLEATE_e){
        load_menu((load_menu_context*)&load_menu_ctx);
        if(load_menu_ctx.phase == cPhs_ERROR_e){
            OSReport("gzMenu: Error loading gzMenu arc!");
        }
    }
    if(load_menu_ctx.phase == cPhs_COMPLEATE_e){
        if(main_pane == 0){
            menu_pane___new(&main_pane, load_menu_ctx.mMenuResArc);
        }
        if(main_pane->active == false){
            if(DIGITAL_INPUTS[X].pressed && DIGITAL_INPUTS[D_PAD_LEFT].pressed){
                main_pane->active = true;
            }
        }
        else{
            if(DIGITAL_INPUTS[B].pressed){
                main_pane->active = false;
            }
        }
        if(main_pane->active){
            menu_pane__update_dDlst(main_pane);
        }
    }
}