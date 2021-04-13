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

#pragma region _frame_advance_defines
    # define PLAYER_PTR  (daPy_lk_c**)0x803CA410
    # define FRAME_COUNT_PTR (int*)0x803E8144
#pragma endregion _frame_advance_defines