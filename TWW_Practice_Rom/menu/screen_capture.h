#ifndef SCREEN_CAPTURE_H_INCLUDED
#define SCREEN_CAPTURE_H_INCLUDED

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



typedef struct screen_capture {
    dDlst_base_c base;  //inherit dDlst_base_c
    dDlst_MENU_CAPTURE_c dDlst_screen_capture; // screen capture object
} screen_capture;


void screen_capture___new(screen_capture *this);
void screen_capture___destroy(screen_capture *this);
void screen_capture___draw(screen_capture *this);

#endif