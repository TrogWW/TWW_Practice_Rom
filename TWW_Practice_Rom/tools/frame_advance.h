#ifndef FRAME_ADVANCE_H_INCLUDED
#define FRAME_ADVANCE_H_INCLUDED
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
#include "../settings.h"

void _frame_advance_advance_frame(){
    m_Do_audio__mDoAud_Execute();
    f_ap_game__fapGm_Execute();
}

typedef struct Frame_Advance {
    bool enabled;
    bool advanceFrame;
} Frame_Advance;

Frame_Advance frame_advance = {
  .enabled = false,
  .advanceFrame = false
};

void _frame_advance_exec(Settings* settings){
    if(DIGITAL_INPUTS[Z].pressed && DIGITAL_INPUTS[D_PAD_LEFT].pressed){
        if(frame_advance.enabled == true){
            frame_advance.enabled = false;
        }
        else{
            frame_advance.enabled = true;
        }

    }
    if(frame_advance.enabled == true){
        if(DIGITAL_INPUTS[D_PAD_DOWN].pressed){
            if(frame_advance.advanceFrame == true){
                /*JUTGamePad__read(0);*/        /*This does not work...need a way to buffer digital inputs*/
                _frame_advance_advance_frame();
                frame_advance.advanceFrame = false;
            }
        }
        else{
            frame_advance.advanceFrame = true;
        }
    }
    else{
        _frame_advance_advance_frame();
    }    
}

#endif