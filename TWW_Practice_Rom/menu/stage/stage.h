#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

#include "room.h"
#include "event.h"

typedef struct stage {
    char *stage_name;
    char *display_name;
    int room_count;
    room *rooms;
    int event_count;
    event *events;
} stage;

int stage__new(stage *this, int offset);
#endif