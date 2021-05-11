#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

typedef struct room {
    int index;
    char *display_name;
    int spawn_count;
    int *spawn_ids;  
} room;

int room__new(room *this, int offset);

#endif