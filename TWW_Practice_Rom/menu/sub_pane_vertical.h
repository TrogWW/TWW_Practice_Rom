// menu_pane.h inherits base_pane, this is the root pane

#ifndef SUB_PANE_VERTICAL_H_INCLUDED
#define SUB_PANE_VERTICAL_H_INCLUDED
#include "base_pane.h"

typedef struct sub_pane_vertical_vtbl sub_pane_vertical_vtbl;
typedef struct sub_pane_vertical sub_pane_vertical;
struct sub_pane_vertical_vtbl {
    void (*draw)(sub_pane_vertical *this);
    void (*hide)(sub_pane_vertical *this);
    void (*update_cursor)(sub_pane_vertical *this);
    void (*open)(sub_pane_vertical *this);
    void (*close)(sub_pane_vertical *this);
};
struct sub_pane_vertical {
    base_pane base;
    base_pane *parent;
    J2DPane *pane;
    //field *fields[];
};
sub_pane_vertical* sub_pane_vertical__new(sub_pane_vertical *this, base_pane *parent, J2DWindow *pane, float xAxisOffset, float yAxisOffset, char* titleText, text_color_pallete *pallete, JUTFont *font);
void sub_pane_vertical__draw(sub_pane_vertical *this);
void sub_pane_vertical__hide(sub_pane_vertical *this);
void sub_pane_vertical__update_cursor(sub_pane_vertical *this);
void sub_pane_vertical__open(sub_pane_vertical *this);
void sub_pane_vertical__close(sub_pane_vertical *this);

#endif
