#ifndef ROOM_C_INCLUDED
#define ROOM_C_INCLUDED

#include "room.h"
int room__new(room *this, void *data){
    this->index = *((int*)data);
    this->spawn_count = *((int*)(data + 4));
    this->spawn_ids = (int*)(data + 8);
    OSReport(MSL_C_PPCEABI_bare_H__printf("room__new: this->index = %d | this->spawn_count = %d | this->spawn_ids = %X\n",this->index,this->spawn_count,this->spawn_ids));
    return data + 8 + (4 * this->spawn_count);
}

#endif