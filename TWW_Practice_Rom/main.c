#define _WW_DEFINES_H "../WW_Hacking_API/vanilla_defines/ww_defines.h"
#define _WW_FUNCTIONS_H "../WW_Hacking_API/vanilla_defines/ww_functions.h"

#include _WW_DEFINES_H
#include _WW_FUNCTIONS_H
#include "menu.h"
#include "tools/frame_advance.h"


void _main_loop(){
    Settings *menu_settings = menu.menu_settings;
    if(menu_settings->frame_advance_enabled){
        _frame_advance_exec(menu_settings);
    }
    _menu_exec(menu_settings);
}
