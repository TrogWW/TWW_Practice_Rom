#ifndef LOAD_MENU_CONTEXT_H_INCLUDED
#define LOAD_MENU_CONTEXT_H_INCLUDED
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


typedef struct load_menu_context {
    request_of_phase_process_class* mPhaseRequest;
    PhaseState phase;
    JKRArchive* mMenuResArc; // Pointer to our resource archive (BLO, images)
} load_menu_context;

PhaseState load_menu(load_menu_context *this);
#endif
