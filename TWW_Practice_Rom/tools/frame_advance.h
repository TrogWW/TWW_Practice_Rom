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
#include "../input.h"
#include "../settings.h"

typedef struct Frame_Advance {
    bool enabled;
    bool advanceFrame;
} Frame_Advance;

Frame_Advance frame_advance = {
  .enabled = false,
  .advanceFrame = false
};

void _draw_tools(){
    input_display__draw(&INPUT_DISPLAY);
    zh_counter__draw(&ZH_COUNTER);
    swim_predictor__draw(&SWIM_PREDICTOR);
    if(WATCHES_DISPLAY_UI.watches_list.mCount > 0){
        if(main_pane.active == false){
            watches_display_pane__update_dDlst(&WATCHES_DISPLAY_UI); 
        }
    }
}

void _frame_advance_advance_frame(){
    if(frame_advance.enabled == false){
        _menu_exec(&settings);
    }
    _draw_tools();
    m_Do_audio__mDoAud_Execute();
    f_ap_game__fapGm_Execute();

}



void _frame_advance_exec(Settings* settings){
    if(Two_Inputs_Pressed(&DIGITAL_INPUTS[Z],&DIGITAL_INPUTS[D_PAD_LEFT])){
        if(frame_advance.enabled == true){
            frame_advance.enabled = false;
        }
        else{
            frame_advance.enabled = true;
        }
    }
    if(frame_advance.enabled == true){
        Input_CButton(); //buffers inputs from CButton
        if(DIGITAL_INPUTS[D_PAD_DOWN].pressed){
            _frame_advance_advance_frame();
        }
    }
    else{
        _frame_advance_advance_frame();
    }    
}

#endif