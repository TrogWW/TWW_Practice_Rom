#ifndef WARPPANE_H_INCLUDED
#define WARPPANE_H_INCLUDED

#include "base_pane.h"
#include "stage/stage_list.h"

typedef struct warp_pane warp_pane;
typedef struct warp_pane_vtbl {
    void (*draw)(warp_pane *this);
    void (*hide)(warp_pane *this);
    void (*update_cursor)(warp_pane *this);
} warp_pane_vtbl;

struct warp_pane {
    base_pane base;
    base_pane *parent;
    stage_list warp_list;
};

warp_pane* warp_pane__new(warp_pane *this, base_pane *parent, J2DPane *pane, float relativeX, float relativeY);
void warp_pane__draw(warp_pane *this);
void warp_pane__hide(warp_pane *this);
void warp_pane_update__cursor(warp_pane *this);
#endif