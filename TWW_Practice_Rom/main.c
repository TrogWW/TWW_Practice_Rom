#define _WW_DEFINES_H "../WW_Hacking_API/vanilla_defines/ww_defines.h"
#define _WW_FUNCTIONS_H "../WW_Hacking_API/vanilla_defines/ww_functions.h"
#define _WW_VARIABLES_H "../WW_Hacking_API/vanilla_defines/ww_variables.h"

#include _WW_DEFINES_H
#include _WW_FUNCTIONS_H
#include _WW_VARIABLES_H
#include "input.h"
#include "settings.h"
#include "menu_new.h"
#include "tools/frame_advance.h"

void _main_loop(){
    Update_Digital_Inputs();
    _menu_exec(&settings);

    if(settings.frame_advance_enabled){
        _frame_advance_exec(&settings);
    }
    else{
        _menu_exec(&settings);
    }
}
