// MenuClassBase.h - Base class for menus
#ifndef BASEPANE_H_INCLUDED
#define BASEPANE_H_INCLUDED
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


typedef struct base_pane base_pane;
typedef struct base_pane_vtbl base_pane_vtbl;

#include "textbox/textbox.h"

struct base_pane {
    base_pane_vtbl *vptr;
    int cursor;             //cursor location
    bool cursor_active;     //whether or not cursor for this pane is manipulatable             
    //float xAxisOffset;
    //float yAxisOffset;
    //float width;
    GzTextBox title;        //textbox title
    J2DPane *pane;
};
struct base_pane_vtbl {
    void (*draw)(base_pane *this);
    void (*hide)(base_pane *this);
    void (*update_cursor)(base_pane *this);
};

void base_pane___new(base_pane *this);
void base_pane_draw(base_pane *this);
void base_pane_hide(base_pane *this);
void base_pane_update_cursor(base_pane *this);
void base_pane_set_title(base_pane *this, base_pane *relative_pane, float relativeX, float relativeY, char *titleText, text_color_pallete *pallete, JUTResFont *font);
float base_pane_xOffset(base_pane *this, float xOffset);
float base_pane_yOffset(base_pane *this, float yOffset);
float base_pane_width(base_pane *this);

#endif