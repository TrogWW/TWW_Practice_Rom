#ifndef WARPPANE_H_INCLUDED
#define WARPPANE_H_INCLUDED

#define WARP_FIELD_COUNT 7
#define WARP_LABEL_COUNT 7

#include "base_pane.h"
#include "textbox/textbox.h"
#include "stage/area_list.h"

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
    area_list *warp_list;
    int area_index;
    int stage_index;
    int room_index;
    int spawn_id;
    int layer_id;
    int hour;
    int dayOfWeek;
    bool event_window_enabled;
    int event_index;
    GzTextBox labels[WARP_LABEL_COUNT];
    GzTextBox fields[WARP_FIELD_COUNT];
    GzTextBox event_label;
    GzTextBox event_field;
};

warp_pane* warp_pane__new(warp_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY);
void warp_pane__draw(warp_pane *this);
void warp_pane__hide(warp_pane *this);
void warp_pane__update_cursor(warp_pane *this);
void warp_pane__open(warp_pane *this);
void warp_pane__close(warp_pane *this);
void warp_pane__update_fields(warp_pane *this);
void warp_pane__update_event_fields(warp_pane *this);
room *warp_pane__current_room(warp_pane *this);
stage *warp_pane__current_stage(warp_pane *this);
area *warp_pane__current_area(warp_pane *this);
#endif