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
#include "menu/load_menu_context.c"
#include "menu/menu_pane.c"

load_menu_context load_menu_ctx;
menu_pane main_pane;

void _menu_exec(Settings* settings){
    if(load_menu_ctx.mMenuResArc == 0){
        PhaseState phase = load_menu((load_menu_context*)&load_menu_ctx);
        if(phase == cPhs_ERROR_e){
            OSReport("gzMenu: Error loading gzMenu arc!");
        }
    }
    if(load_menu_ctx.mMenuResArc != 0){
        if(main_pane.base.vptr == 0){
            OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: load_menu_ctx.mMenuResArc pointer = %d\n",load_menu_ctx.mMenuResArc));
            menu_pane___new(&main_pane, load_menu_ctx.mMenuResArc);
        }
        if(main_pane.active == false){
            if(DIGITAL_INPUTS[X].pressed && DIGITAL_INPUTS[D_PAD_LEFT].pressed || 
               DIGITAL_INPUTS[X].held && DIGITAL_INPUTS[D_PAD_LEFT].pressed ||
               DIGITAL_INPUTS[X].pressed && DIGITAL_INPUTS[D_PAD_LEFT].held){
                main_pane.active = true;
            }
        }
        else{
            if(DIGITAL_INPUTS[B].pressed){
                main_pane.active = false;
                menu_pane_close(&main_pane);
            }
        }
        if(main_pane.active){
            menu_pane__update_dDlst(&main_pane);
        }
    }
}