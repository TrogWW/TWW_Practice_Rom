#ifndef STAGE_C_INCLUDED
#define STAGE_C_INCLUDED

#include "stage.h"
#include "room.c"
#include "event.c"

int stage__new(stage *this, int offset){
    //OSReport(MSL_C_PPCEABI_bare_H__printf("stage__new: stage_name before = %X\n",this->stage_name));
    this->stage_name = ((int)this->stage_name) + offset;
    //OSReport(MSL_C_PPCEABI_bare_H__printf("stage__new: stage_name after = %X\n",this->stage_name));
    if(this->display_name != 0){
        this->display_name = ((int)this->display_name) + (offset + 4);
    }
    if(this->room_count > 0){
        this->rooms = ((int)this->rooms) + offset;
    }
    if(this->event_count > 0){
        this->events = ((int)this->events) + offset;
    }
    //OSReport(MSL_C_PPCEABI_bare_H__printf("stage__new: stage_name = %s | this->room_count = %d | this->event_count = %d\n",this->stage_name, this->room_count, this->event_count));
    for (int i = 0; i < this->room_count; i++)
    {
        room__new(&this->rooms[i], offset);
    }
    for(int i = 0; i < this->event_count; i++){
        event__new(&this->events[i], offset);
    }
}

#endif