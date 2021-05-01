#ifndef WARPPANE_H_INCLUDED
#define WARPPANE_H_INCLUDED

#define WARP_FIELD_COUNT 6
#define WARP_LABEL_COUNT 6

#include "base_pane.h"
#include "textbox/textbox.h"
#include "stage/stage_list.h"

typedef struct warp_pane warp_pane;
typedef struct warp_pane_vtbl {
    void (*draw)(warp_pane *this);
    void (*hide)(warp_pane *this);
    void (*update_cursor)(warp_pane *this);
    void (*open)(warp_pane *this);
    void (*close)(warp_pane *this);
} warp_pane_vtbl;

struct warp_pane {
    base_pane base;
    base_pane *parent;
    stage_list warp_list;
    int stage_index;
    int room_index;
    int spawn_id;
    int layer_id;
    int hour;
    int dayOfWeek;
    GzTextBox labels[WARP_LABEL_COUNT];
    GzTextBox fields[WARP_FIELD_COUNT];
};

warp_pane* warp_pane__new(warp_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY);
void warp_pane__draw(warp_pane *this);
void warp_pane__hide(warp_pane *this);
void warp_pane_update__cursor(warp_pane *this);
void warp_pane__open(warp_pane *this);
void warp_pane__close(warp_pane *this);
void warp_pane__update_fields(warp_pane *this);
#endif