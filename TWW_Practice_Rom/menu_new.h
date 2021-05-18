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
#include "DvdThd_PhaseHandler.c"
#include "tools/wiird_loader_context.c"

void _menu_exec(Settings* settings){

    if(code_list.load_wiird_code_handler.object == 0){
        DvdThd_PhaseHandler__new(&code_list.load_wiird_code_handler,&wiird_loader_phases, &code_list);
        DvdThd_PhaseHandlerList__append(&PHASE_HANDLER_LIST, &code_list.load_wiird_code_handler);
    }
    else{     
        if(code_list.load_wiird_code_handler.complete){
            wiird__execute();
        }
    }
    if(load_menu_arc_handler.object == 0){
        OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: loading menu\n"));
        DvdThd_PhaseHandler__new(&load_menu_arc_handler,&load_menu_arc_phases, &load_menu_arc_handler);
        DvdThd_PhaseHandlerList__append(&PHASE_HANDLER_LIST, &load_menu_arc_handler);
    }
    else{
        if(load_menu_arc_handler.complete){
            if(main_pane.active == false){
                if(Two_Inputs_Pressed(&DIGITAL_INPUTS[X], &DIGITAL_INPUTS[D_PAD_LEFT])){
                    menu_pane__open(&main_pane); 
                }
            }
            else{
                if(DIGITAL_INPUTS[B].pressed){                
                    menu_pane__close(&main_pane);
                }
            }
            if(main_pane.active){
                //memory card status?
                //mDoMemCd_Ctrl_c__getStatus(mDoMemCd_Ctrl_c * this, ulong param_1);g_mDoMemCd_control
                //int mem_status = mDoMemCd_Ctrl_c__getStatus(&m_Do_MemCard__g_mDoMemCd_control, 0);
                //OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: mem_status = %X\n",mem_status));
                menu_pane__update_dDlst(&main_pane);
            }
        }
    }

}