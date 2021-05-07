#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

#include "room.h"

typedef struct stage {
    char *stage_name;
    int room_count;
    room **rooms;
} stage;

int stage__new(stage *this, void *data);
#endif