#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

typedef struct stage {
    char *stage_name;
    JSUPtrList rooms;
} stage;

void stage__new(stage *this, char *name);
void stage_append_room(stage *this, char *room_num);
#endif