#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

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

#include "text_color_pallete.h"
#include "../base_pane.h"

typedef struct GzTextBox {
    J2DTextBox textbox;
    JUTResFont* font;
    base_pane *parent;
    float xAxisOffset;
    float yAxisOffset;
    float width;
    char* text;
    text_color_pallete *pallete;
} GzTextBox;



void GzTextBox__new(GzTextBox* this, base_pane *parent, float xAxisOffset, float yAxisOffset, char* text, text_color_pallete *pallete, JUTResFont *font);
void GzTextBox__draw(GzTextBox* this);
void GzTextBox__setAbsoluteX(GzTextBox *this, float xAxisOffset);
void GzTextBox__setAbsoluteY(GzTextBox *this, float xAxisOffset);
void GzTextBox__changeTextColorInt(_GXColor* color, int value);
void GzTextBox__changeTextColorPercentage(_GXColor* color, float amount);

#endif