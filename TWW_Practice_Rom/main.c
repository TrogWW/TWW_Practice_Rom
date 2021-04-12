#include "../WW_Hacking_API/vanilla_defines/ww_defines.h"
#include "../WW_Hacking_API/vanilla_defines/ww_functions.h"

# define PLAYER_PTR  (daPy_lk_c**)0x803CA410
# define FRAME_COUNT_PTR (int*)0x803E8144

# define STICK_LEFT (1 << 0)
# define STICK_RIGHT (1 << 1)
# define STICK_DOWN (1 << 2)
# define STICK_UP (1 << 3)

# define D_PAD_LEFT_PRESSED (1 << 0)
# define D_PAD_RIGHT_PRESSED (1 << 1)
# define D_PAD_DOWN_PRESSED (1 << 2)
# define D_PAD_UP_PRESSED (1 << 3)
# define Z_PRESSED (1 << 4)
# define R_PRESSED (1 << 5)
# define L_PRESSED (1 << 6)
# define A_PRESSED (1 << 8) /*(1 << 7) is unused*/
# define B_PRESSED (1 << 9)
# define X_PRESSED (1 << 10)
# define Y_PRESSED (1 << 11)
# define START_PRESSED (1 << 12)

typedef struct Frame_Advance {
    bool enabled;
    int toggleFrame;
    bool advanceFrame;
} Frame_Advance;

Frame_Advance* Create_Frame_Advance(bool value){
    Frame_Advance* new_Instance = (Frame_Advance*)JKRHeap__alloc(sizeof(Frame_Advance),0,0);
    new_Instance->enabled = value;
    new_Instance->toggleFrame = *FRAME_COUNT_PTR;
    new_Instance->advanceFrame = false;
    return new_Instance;
}

static Frame_Advance *frame_advance;
void _main_loop(){
    if(frame_advance == 0xdeadbabe){
        frame_advance = Create_Frame_Advance(false);
    }
    m_Do_controller_pad__mDoCPd_Read();
    JUTGamePad* gamePad = (JUTGamePad*)JUTGamePad__getGamePad(0);
    CButton* mButton = (CButton*)&gamePad->mButton;
    short currentInput = (short)mButton->field_0x0 & 0x0000FFFF;
    short checkButtonCombo = D_PAD_LEFT_PRESSED + Z_PRESSED;
    int currentFrame = *FRAME_COUNT_PTR;
    if(currentInput == checkButtonCombo){
        if(frame_advance->toggleFrame + 10 <= currentFrame){
            if(frame_advance->enabled){
                frame_advance->enabled = false;
            }
            else{
                frame_advance->enabled = true;
            }
            frame_advance->toggleFrame = currentFrame;
        }
    }
    if(frame_advance->enabled){
        if(currentInput & D_PAD_DOWN_PRESSED){
            if(frame_advance->advanceFrame){
                JUTGamePad__read(0);
                m_Do_audio__mDoAud_Execute();
                f_ap_game__fapGm_Execute();
                frame_advance->advanceFrame = false;
                frame_advance->toggleFrame = 0;
            }
        }
        else{
            frame_advance->advanceFrame = true;
        }
    }
    else{
        m_Do_audio__mDoAud_Execute();
        f_ap_game__fapGm_Execute();
    }    
}

