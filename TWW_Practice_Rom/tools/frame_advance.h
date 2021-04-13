#pragma region _frame_advance_defines
#ifndef _SETTINGS_H
    #define _SETTINGS_H "../settings.h"
    #include _SETTINGS_H
#endif
#ifndef _WW_DEFINES_H
    #define _WW_DEFINES_H "../../WW_Hacking_API/vanilla_defines/ww_defines.h"
    #include _WW_DEFINES_H
#endif
#ifndef _WW_FUNCTIONS_H
    #define _WW_FUNCTIONS_H "../../WW_Hacking_API/vanilla_defines/ww_functions.h"
    #include _WW_FUNCTIONS_H
#endif
#ifndef _INPUT_H
    #define _INPUT_H "../input.h"
    #include _INPUT_H
#endif
#ifndef _MEMORY_H
    #define _MEMORY_H "../memory.h"
    #include _MEMORY_H
#endif
#pragma endregion _frame_advance_defines

void _frame_advance_advance_frame(){
    m_Do_audio__mDoAud_Execute();
    f_ap_game__fapGm_Execute();
}

typedef struct Frame_Advance {
    bool enabled;
    int toggleFrame;
    bool advanceFrame;
} Frame_Advance;

Frame_Advance frame_advance = {
  .enabled = false,
  .toggleFrame = 0,
  .advanceFrame = false
};

void _frame_advance_exec(Settings* settings){
    /*Read game input*/
    m_Do_controller_pad__mDoCPd_Read();

    short currentInput = _input_current_digital();
    int currentFrame = *FRAME_COUNT_PTR;
    short toggle_frame_advance_combo = settings->toggle_frame_advance[0] + settings->toggle_frame_advance[1];
    if(currentInput == toggle_frame_advance_combo){
        if(frame_advance.toggleFrame + 10 <= currentFrame){
            if(frame_advance.enabled){
                frame_advance.enabled = false;
            }
            else{
                frame_advance.enabled = true;
            }
            frame_advance.toggleFrame = currentFrame;
        }
    }
    if(frame_advance.enabled){
        if(currentInput & D_PAD_DOWN){
            if(frame_advance.advanceFrame){
                /*JUTGamePad__read(0);*/        /*This does not work...need a way to buffer digital inputs*/
                _frame_advance_advance_frame();
                frame_advance.advanceFrame = false;
                frame_advance.toggleFrame = 0;
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

