
#ifndef TEXT_COLOR_PALLETE_H_INCLUDED
#define TEXT_COLOR_PALLETE_H_INCLUDED
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

typedef struct text_color_pallete {
    _GXColor* topColorGradiant;
    _GXColor* bottomColorGradiant;
    _GXColor* textColor;
    _GXColor* textBackgroundColor;
} text_color_pallete;

_GXColor COLOR_WHITE = {  .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff };
_GXColor COLOR_GREY = {  .r = 0xb3, .g = 0xb3, .b = 0xb3, .a = 0xff };
_GXColor COLOR_NONE = { .r = 0x00, .g = 0x00, .b = 0x00, .a = 0x00 };

text_color_pallete TEXT_PALLETE_WHITE = { &COLOR_WHITE, &COLOR_WHITE, &COLOR_WHITE, &COLOR_NONE };
text_color_pallete TEXT_PALLETE_GREY = { &COLOR_GREY, &COLOR_GREY, &COLOR_GREY, &COLOR_NONE };

#endif