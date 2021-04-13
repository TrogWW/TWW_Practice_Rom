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

enum Digital_Input {
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

byte nthByte(int number, int n){
    return (number >> (8*n)) & 0xff;
}
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