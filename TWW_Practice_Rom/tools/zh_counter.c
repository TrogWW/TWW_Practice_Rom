#ifndef ZH_COUNTER_C_INCLUDED
#define ZH_COUNTER_C_INCLUDED

#include "zh_counter.h"
float zh_width = 200.0f;
float zh_xOffset = 500.0f;
float zh_yOffset = 470.0f;
float zh_font_size = 0.6f;
zh_counter ZH_COUNTER;
bool zh_initialized = false;
void zh_counter__new(zh_counter *this){
     this->display = (J2DTextBox *)JKernel__operator_new(sizeof(J2DTextBox));
     J2DTextBox__J2DTextBox(this->display,"rock_24_20_4i_usa.bfn", &this->text);
     zh_initialized = true;
}
void zh_counter__draw(zh_counter *this){
    if(zh_initialized == false){
        return;
    }
    this->b_presses[this->curr_index] = DIGITAL_INPUTS[B].pressed;

    this->display->mFontWidth = DEFAULT_FONT_WIDTH * zh_font_size;
    this->display->mFontHeight = DEFAULT_FONT_HEIGHT * zh_font_size;

    //set font pallete
    this->display->mColorGradient[0] = *TEXT_PALLETE_WHITE.topColorGradiant;
    this->display->mColorGradient[1] = *TEXT_PALLETE_WHITE.bottomColorGradiant;
    this->display->mTextColor = *TEXT_PALLETE_WHITE.textColor;
    this->display->mTextBgColor = *TEXT_PALLETE_WHITE.textBackgroundColor;


    int b_press_count = 0;
    for(int i = 0; i < ZH_DATA_SIZE; i++){
        if(this->b_presses[i] == true){
            b_press_count += 1;
        }
    }
    float b_press_avg = ((float)b_press_count / (float)ZH_DATA_SIZE) * 30.0f;
    

    MSL_C_PPCEABI_bare_H__sprintf(&this->text, "ZH Rate: %f", b_press_avg);

    J2DTextBox__setString(this->display, &this->text);

    J2DTextBox__draw(this->display, zh_xOffset, zh_yOffset, zh_width,2); //2 = hbinding left

    this->curr_index += 1;
    if(this->curr_index > ZH_DATA_SIZE){
        this->curr_index = 0;
    }
}

#endif