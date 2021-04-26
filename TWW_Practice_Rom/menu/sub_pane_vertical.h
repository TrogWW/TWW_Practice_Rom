// menu_pane.h inherits base_pane, this is the root pane

#ifndef SUB_PANE_VERTICAL_H_INCLUDED
#define SUB_PANE_VERTICAL_H_INCLUDED
#include "base_pane.h"

typedef struct sub_pane_vertical_vtbl sub_pane_vertical_vtbl;
typedef struct sub_pane_vertical sub_pane_vertical;
struct sub_pane_vertical_vtbl {
    void (*draw)(sub_pane_vertical const *this);
    void (*update_cursor)(sub_pane_vertical const *this);
};
struct sub_pane_vertical {
    base_pane base;
    base_pane *parent;
    //field *fields[];
};
void sub_pane_vertical__new(sub_pane_vertical *this, base_pane *parent, float xAxisOffset, float yAxisOffset, char* titleText, text_color_pallete *pallete, JUTFont *font);
void sub_pane_vertical_draw(sub_pane_vertical const *this);
void sub_pane_vertical_update_cursor(sub_pane_vertical const *this);
void sub_pane_setRelative_xAxisOffset(sub_pane_vertical const *this, float xAxisOffset);
void sub_pane_setRelative_yAxisOffset(sub_pane_vertical const *this, float xAxisOffset);
#endif
