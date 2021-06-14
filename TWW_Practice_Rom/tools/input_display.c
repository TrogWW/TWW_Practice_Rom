#ifndef INPUT_DISPLAY_C_INCLUDED
#define INPUT_DISPLAY_C_INCLUDED

#include "input_display.h"

input_display INPUT_DISPLAY = {
    .init = {
        d_pad_left_display_init,
        d_pad_right_display_init,
        d_pad_down_display_init,
        d_pad_up_display_init,
        z_display_init,
        r_display_init,
        l_display_init,
        x_display_init,
        y_display_init,
        a_display_init,
        b_display_init,
        start_display_init
    },
    .draw = {
        d_pad_left_display_draw,
        d_pad_right_display_draw,
        d_pad_down_display_draw,
        d_pad_up_display_draw,
        z_display_draw,
        r_display_draw,
        l_display_draw,
        x_display_draw,
        y_display_draw,
        a_display_draw,
        b_display_draw,
        start_display_draw
    }
};


bool input_display_initalized = false;  //flag to know when okay to start drawing input display
void input_display__new(input_display *this){
    stick_display_init();
    for(int i = 0; i < INPUT_SIZE; i++){
        this->init[i]();
    }
    input_display_initalized = true;
}
void input_display__draw(input_display *this){
    if(input_display_initalized == false){
        return;
    }
    stick_display_draw();
    for(int i = 0; i < INPUT_SIZE; i++){
        if(DIGITAL_INPUTS[i].pressed || DIGITAL_INPUTS[i].held){
            this->draw[i]();
        }
    }
}
float display_yOffset = 450.0f;
float display_iconSize = 25.0f;
float display_xPadding = 5.0f;
float display_startOffset = 200.0f;

J2DTextBox *stick_display_textbox;
char stick_text[40];
float stick_display_xOffset = 50.0f;
void stick_display_init(){
    stick_display_textbox = (J2DTextBox *)JKernel__operator_new(sizeof(J2DTextBox));
    J2DTextBox__J2DTextBox(stick_display_textbox,"rock_24_20_4i_usa.bfn", &stick_text);
}
void stick_display_draw(){
    //set font size
    stick_display_textbox->mFontWidth = DEFAULT_FONT_WIDTH * 0.8;
    stick_display_textbox->mFontHeight = DEFAULT_FONT_HEIGHT * 0.8;

    //set font pallete
    stick_display_textbox->mColorGradient[0] = *TEXT_PALLETE_WHITE.topColorGradiant;
    stick_display_textbox->mColorGradient[1] = *TEXT_PALLETE_WHITE.bottomColorGradiant;
    stick_display_textbox->mTextColor = *TEXT_PALLETE_WHITE.textColor;
    stick_display_textbox->mTextBgColor = *TEXT_PALLETE_WHITE.textBackgroundColor;

    byte *stick_ptr = (byte*)0x803F0F32;    //address to stick values
    int stick_value = (int)(stick_ptr[0]);
    int stick_value2 = (int)(stick_ptr[1]);
    int stick_value3 = (int)(stick_ptr[2]);
    int stick_value4 = (int)(stick_ptr[3]);

    MSL_C_PPCEABI_bare_H__sprintf(&stick_text, "A: %d, %d\nC: %d, %d", stick_value, stick_value2, stick_value3, stick_value4);


    J2DTextBox__setString(stick_display_textbox, &stick_text);

    J2DTextBox__draw(stick_display_textbox, stick_display_xOffset, display_yOffset, display_startOffset - stick_display_xOffset,2); //2 = hbinding left
}

//D-PAD TODO
//d_left = font_07_01.bti
//d_up = font_08_up.bti
void d_pad_left_display_init(){}
void d_pad_left_display_draw(){}


void d_pad_right_display_init(){}
void d_pad_right_display_draw(){}

void d_pad_down_display_init(){}
void d_pad_down_display_draw(){}

void d_pad_up_display_init(){}
void d_pad_up_display_draw(){}

J2DPicture *a_picture;
void a_display_init(){
    a_picture = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture));
    J2DPicture__J2DPicture_3(a_picture, "font_00.bti");
}
void a_display_draw(){
    J2DPicture__draw(a_picture, display_startOffset, display_yOffset, display_iconSize, display_iconSize, false, false,false);
}

J2DPicture *b_picture;
void b_display_init(){
    b_picture = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture));
    J2DPicture__J2DPicture_3(b_picture, "font_01.bti");
}
void b_display_draw(){
    J2DPicture__draw(b_picture, display_startOffset + (display_xPadding * 1) + (display_iconSize * 1), display_yOffset, display_iconSize, display_iconSize, false, false,false);
}

J2DPicture *x_picture;
void x_display_init(){
    x_picture = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture));
    J2DPicture__J2DPicture_3(x_picture, "font_02.bti");
}
void x_display_draw(){
    J2DPicture__draw(x_picture, display_startOffset + (display_xPadding * 2) + (display_iconSize * 2), display_yOffset, display_iconSize, display_iconSize, false, false,false);
}

J2DPicture *y_picture;
void y_display_init(){
    y_picture = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture));
    J2DPicture__J2DPicture_3(y_picture, "font_03.bti");
}
void y_display_draw(){
    J2DPicture__draw(y_picture, display_startOffset + (display_xPadding * 3) + (display_iconSize * 3), display_yOffset, display_iconSize, display_iconSize, false, false,false);
}

J2DPicture *l_picture;
void l_display_init(){
    l_picture = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture));
    J2DPicture__J2DPicture_3(l_picture, "font_04.bti");
}
void l_display_draw(){
    J2DPicture__draw(l_picture, display_startOffset + (display_xPadding * 4) + (display_iconSize * 4), display_yOffset, display_iconSize, display_iconSize, false, false,false);
}

J2DPicture *r_picture;
void r_display_init(){
    r_picture = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture));
    J2DPicture__J2DPicture_3(r_picture, "font_05.bti");
}
void r_display_draw(){
    J2DPicture__draw(r_picture, display_startOffset + (display_xPadding * 5) + (display_iconSize * 5), display_yOffset, display_iconSize, display_iconSize, false, false,false);
}

J2DPicture *z_picture;
void z_display_init(){
    z_picture = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture));
    J2DPicture__J2DPicture_3(z_picture, "font_06.bti");
}
void z_display_draw(){
    J2DPicture__draw(z_picture, display_startOffset + (display_xPadding * 6) + (display_iconSize * 6), display_yOffset, display_iconSize, display_iconSize, false, false,false);
}

J2DPicture *start_picture;
void start_display_init(){
    start_picture = (J2DPicture*)JKernel__operator_new(sizeof(J2DPicture));
    J2DPicture__J2DPicture_3(start_picture, "font_11.bti");
}
void start_display_draw(){
    J2DPicture__draw(start_picture, display_startOffset + (display_xPadding * 7) + (display_iconSize * 7), display_yOffset, display_iconSize, display_iconSize, false, false,false);
}
#endif