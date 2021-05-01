#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
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

typedef struct DigitalInput {
    int input;
    bool pressed;
    bool held;
    bool long_held;
    int hold_count;
} DigitalInput;

DigitalInput DIGITAL_INPUTS[12] = {
    { .input = D_PAD_LEFT_PRESSED },
    { .input = D_PAD_RIGHT_PRESSED },
    { .input = D_PAD_DOWN_PRESSED },
    { .input = D_PAD_UP_PRESSED },
    { .input = Z_PRESSED },
    { .input = R_PRESSED },
    { .input = L_PRESSED },
    { .input = X_PRESSED },
    { .input = Y_PRESSED },
    { .input = A_PRESSED },
    { .input = B_PRESSED },
    { .input = START_PRESSED }
};
bool Two_Inputs_Pressed(DigitalInput *input1, DigitalInput *input2){
    if(input1->pressed && input2->pressed || 
               input1->held && input2->pressed ||
               input1->pressed && input2->held){
        return true;
    }
    else{
        return false;
    }
}
void Update_Digital_Input(DigitalInput *this, int currentInput){
    int result = (int)(this->input & currentInput);
    if(result != this->input){
        this->held = false;
        this->pressed = false;
        this->long_held = false;
        this->hold_count = 0;
    }
    else{
        if(this->pressed){
            this->pressed = false;
            this->held = true;
        }
        else if(this->held == false){
            this->pressed = true;
            this->held = false;
            this->long_held = false;
            this->hold_count = 0;
        }
    }
    if(this->held == true){
        this->hold_count = this->hold_count + 1;
    }
    if(this->hold_count >= 15){
        this->long_held = true;
    }
    else{
        this->long_held = false;
    }
}
void Update_Digital_Inputs(){
    m_Do_controller_pad__mDoCPd_Read();
    JUTGamePad* gamePad = (JUTGamePad*)JUTGamePad__getGamePad(0);
    CButton* mButton = (CButton*)&gamePad->mButton;
    int currentInput = (int)mButton->field_0x0 & 0x0000FFFF;
    for(int i = 0; i < 12; i++){
        Update_Digital_Input(&DIGITAL_INPUTS[i], currentInput);
    }
}

enum Inputs {
    D_PAD_LEFT = 0,
    D_PAD_RIGHT = 1,
    D_PAD_DOWN = 2,
    D_PAD_UP = 3,
    Z = 4,
    R = 5,
    L = 6,
    X = 7,
    Y = 8,
    A = 9,
    B = 10,
    START = 11
} Inputs;
/*enum Digital_Input {
    D_PAD_LEFT = D_PAD_LEFT_PRESSED,
    D_PAD_RIGHT = D_PAD_RIGHT_PRESSED,
    D_PAD_DOWN = D_PAD_DOWN_PRESSED,
    D_PAD_UP = D_PAD_UP_PRESSED,
    Z = Z_PRESSED,
    R = R_PRESSED,
    L = L_PRESSED,
    A = A_PRESSED,
    B = B_PRESSED,
    X = X_PRESSED,
    Y = Y_PRESSED,
    START = START_PRESSED
} Digital_Input;
*/
/*
short _input_current_digital(){
    JUTGamePad* gamePad = (JUTGamePad*)JUTGamePad__getGamePad(0);
    CButton* mButton = (CButton*)&gamePad->mButton;
    short currentInput = (short)mButton->field_0x0 & 0x0000FFFF;
    return currentInput;
}

byte _input_current_main_stick(){
    JUTGamePad* gamePad = (JUTGamePad*)JUTGamePad__getGamePad(0);
    CButton* mButton = (CButton*)&gamePad->mButton;
    byte currentInput = nthByte(mButton->field_0x0, 0);
    return currentInput;
}
byte _input_current_c_stick(){
    JUTGamePad* gamePad = (JUTGamePad*)JUTGamePad__getGamePad(0);
    CButton* mButton = (CButton*)&gamePad->mButton;
    byte currentInput = nthByte(mButton->field_0x0, 1);
    return currentInput;
}

bool _input_digital_pressed(short input){
    short currentInput =  _input_current_digital();
    return currentInput == input;
}

bool _input_main_stick_match(short input){
    short currentInput = _input_current_main_stick();
    return currentInput == input;
}

bool _input_c_stick_match(short input){
    short currentInput = _input_current_c_stick();
    return currentInput == input;
}
*/
#endif