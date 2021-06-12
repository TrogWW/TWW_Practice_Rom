#ifndef LOAD_MENU_CONTEXT_C_INCLUDED
#define LOAD_MENU_CONTEXT_C_INCLUDED
#include "load_menu_context.h"
#include "../DvdThd_PhaseHandler.c"
#include "menu_pane.c"
#include "display/watches_display.c"


#define RES_NAME "gzmenu"

menu_pane main_pane;        //the base pane that contains all sub panes


DvdThd_PhaseHandler load_menu_arc_handler;  //handler to load our arc
JKRArchive *load_menu_arc = 0;              //archive pointer to our blo
request_of_phase_process_class load_menu_phase; //current phase of loading the arc


static int (*load_menu_arc_phases[])(DvdThd_PhaseHandler *) = {
    load_menu_arc__phase_1, load_menu_arc__phase_2, load_menu_arc__phase_3
};
int load_menu_arc__phase_1(DvdThd_PhaseHandler *this){ 
    PhaseState phaseState = dComIfG_resLoad(&load_menu_phase, RES_NAME);
    if(phaseState != cPhs_COMPLEATE_e){
        return 0;   //0 = not complete
    }
    else{
        return 2;   //2 = next
    }
}
int load_menu_arc__phase_2(DvdThd_PhaseHandler *this){ 
    // Load our resource archive and store a pointer to it
    dRes_info_c* mObjectInfo = g_dComIfG_gameInfo.mResCtrl.mObjectInfo;
    dRes_info_c* resInfo = dRes_control_c__getResInfo(RES_NAME, mObjectInfo, 0x40);
    if(resInfo == 0){
        OSReport("gzMenu: Failed to get res info!");
        return cPhs_ERROR_e;
    }
    load_menu_arc = resInfo->mpArchive;
    return 2;  //2 = next
}
int load_menu_arc__phase_3(DvdThd_PhaseHandler *this){
    if (mDoExt_font0 == (JUTFont *)0x0) { //do not attempt to load until fonts are loaded. Will cause crash otherwise.
        return 0;   //0 = not complete
    }
    else{
        menu_pane___new(&main_pane, load_menu_arc);
        watches_display_pane___new(&WATCHES_DISPLAY_UI, &main_pane.screen);
        this->complete = true;
        return 4;  //0 = complete
    }
}

#endif