#include "../menu/textbox/textbox.h"
#include "../helpers/hexhelpers.h" //used for nthByte

void GzTextBox__new(GzTextBox* this, base_pane *parent, float xAxisOffset, float yAxisOffset, char* text, text_color_pallete *pallete, JUTFont *font){
    if(this == 0){
        this = (GzTextBox*)JKernel__operator_new(sizeof(GzTextBox));
    }
    if(this == 0){
        OSReport("GzTextBox__new: Not enough memory to create GzTextBox");
        return;
    }
    this->parent = parent;

    JUTResFont* resFont = mDoExt_resfont0;
    TBox2__float__ rect = {
        .mTL.x = 0.0f,
        .mTL.y = 0.0f,
        .mBR.x = 0.0f,
        .mBR.y = 0.0f
    };
    //J2DTextBox__J2DTextBox(J2DTextBox * this, char * param_1, char * param_2);

    J2DTextBox__J2DTextBox(&this->textBox,(char*)0,(char*)0);
    J2DTextBox__initiate(&this->textBox, resFont, text, 0,0);

    GzTextBox__setRelative_xAxisOffset(this, xAxisOffset);
    GzTextBox__setRelative_yAxisOffset(this, yAxisOffset); 

    this->width = this->parent.base.width;

    this->text = this->textBox.mpStringPtr;
    this->pallete = pallete;
    this->font = font;
    if(this->pallete = 0){ 
        this->pallete = &TEXT_PALLETE_GREY; //default pallete
    }
    if(this->font == 0){
        this->font = mDoExt_getMesgFont(); //default font
    }
}

void GzTextBox__draw(GzTextBox* this){
    this->textBox.field_0xd0 = (_GXColor)*this->pallete->topColorGradiant;
    this->textBox.field_0xd4 = (_GXColor)*this->pallete->bottomColorGradiant;
    this->textBox.field_0xf4 = (_GXColor)*this->pallete->textColor;
    this->textBox.field_0xf8 = (_GXColor)*this->pallete->textBackgroundColor;

    J2DTextBox__setFont(&this->textbox, this->font);
    J2DTextBox__draw(&this->textbox,this->xAxisOffset,this->yAxisOffset,this->width,2); //2 = hbinding left
}

void GzTextBox__setRelative_xAxisOffset(GzTextBox const *this, float xAxisOffset){
    this->xAxisOffset = this->parent.base.xAxisOffset + xAxisOffset;   
}
void GzTextBox__setRelative_yAxisOffset(GzTextBox const *this, float xAxisOffset){
    this->xAxisOffset = this->parent.base.xAxisOffset + xAxisOffset;
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
    color->b = (byte)MSL_C_PPCEABI_bare_H__floor(a * amount);
}
