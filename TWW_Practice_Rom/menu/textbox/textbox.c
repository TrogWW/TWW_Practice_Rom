#ifndef TEXTBOX_C_INCLUDED
#define TEXTBOX_C_INCLUDED
#include "textbox.h"
#include "../base_pane.c"
#include "../../helpers/hexhelpers.c" //used for nthByte

#define DEFAULT_FONT_WIDTH 21.0f
#define DEFAULT_FONT_HEIGHT 24.0f
void GzTextBox__new(GzTextBox* this, base_pane *parent, float xAxisOffset, float yAxisOffset, char* text, text_color_pallete *pallete, JUTResFont *font, float font_scale){
    if(this == 0){
        this = (GzTextBox*)JKernel__operator_new(sizeof(GzTextBox));
    }
    if(this == 0){
        OSReport("GzTextBox__new: Not enough memory to create GzTextBox");
        return;
    }
    this->parent = parent;

    // TBox2__float__ rect = {
    //     .mTL.x = 0.0f,
    //     .mTL.y = 0.0f,
    //     .mBR.x = 0.0f,
    //     .mBR.y = 0.0f
    // };
    J2DTextBox__J2DTextBox(&this->textbox,"rock_24_20_4i_usa.bfn",text);
    if(this->font != 0){
        J2DTextBox__setFont(&this->textbox, font);
    }
    this->font = this->textbox.mpFont;
    this->font_scale = font_scale;
    size_t str_len = MSL_C_PPCEABI_bare_H__strlen(this->textbox.mpStringPtr);

    this->text = (char*)JKernel__operator_new(sizeof(char) * (str_len + 1));
    cLib_memCpy(this->text, &this->textbox.mpStringPtr[0],str_len);
    this->text[str_len] = '\0';

    GzTextBox__setAbsoluteX(this, xAxisOffset);
    GzTextBox__setAbsoluteY(this, yAxisOffset); 

    this->width = base_pane_width(this->parent);
    this->pallete = pallete;
    if(this->pallete = 0){ 
        this->pallete = &TEXT_PALLETE_WHITE_70; //default pallete
    }
}

void GzTextBox__draw(GzTextBox* this, int hbinding){

    this->textbox.mFontWidth = DEFAULT_FONT_WIDTH * this->font_scale;
    this->textbox.mFontHeight = DEFAULT_FONT_HEIGHT * this->font_scale;

    this->textbox.mColorGradient[0] = (_GXColor)*this->pallete->topColorGradiant;
    this->textbox.mColorGradient[1] = (_GXColor)*this->pallete->bottomColorGradiant;
    this->textbox.mTextColor = (_GXColor)*this->pallete->textColor;
    this->textbox.mTextBgColor = (_GXColor)*this->pallete->textBackgroundColor;

    J2DTextBox__setString(&this->textbox, this->text);
    J2DTextBox__draw(&this->textbox,this->xAxisOffset,this->yAxisOffset,this->width,hbinding); //2 = hbinding left
}

void GzTextBox__setAbsoluteX(GzTextBox *this, float xAxisOffset){
    this->xAxisOffset = base_pane_xOffset(this->parent, xAxisOffset);  
}
void GzTextBox__setAbsoluteY(GzTextBox *this, float yAxisOffset){
    this->yAxisOffset = base_pane_yOffset(this->parent, yAxisOffset);  
}

void GzTextBox__changeTextColorInt(_GXColor* color, int value){
    color->r = nthByte(value, 0);
    color->g = nthByte(value, 1);
    color->b = nthByte(value, 2);
    color->a = nthByte(value, 3);
}
//speficy increase/decrease in color brightness. Ex: 1.5 = 50% brighter. 0.5 = 50% darker
void GzTextBox__changeTextColorPercentage(_GXColor* color, float amount){
    byte r = (byte)color->r;
    byte g = (byte)color->g;
    byte b = (byte)color->b;
    color->r = (byte)MSL_C_PPCEABI_bare_H__floor(r * amount);
    color->g = (byte)MSL_C_PPCEABI_bare_H__floor(g * amount);
    color->b = (byte)MSL_C_PPCEABI_bare_H__floor(b * amount);
}
/*
    _GXColor* topColorGradiant;
    _GXColor* bottomColorGradiant;
    _GXColor* textColor;
    _GXColor* textBackgroundColor;
*/
void GzTextBox__changeTextColorPallete(text_color_pallete *pallete, float amount){
    GzTextBox__changeTextColorPercentage(pallete->textColor, amount);
}

void SetTextboxPallete(J2DTextBox *display, text_color_pallete *pallete){
    display->mColorGradient[0] = *pallete->topColorGradiant;
    display->mColorGradient[1] = *pallete->bottomColorGradiant;
    display->mTextColor = *pallete->textColor;
    display->mTextBgColor = *pallete->textBackgroundColor;
}

void SetTextboxScale(J2DTextBox *display, float scale){
    display->mFontWidth = DEFAULT_FONT_WIDTH * scale;
    display->mFontHeight = DEFAULT_FONT_HEIGHT * scale;
}
#endif
