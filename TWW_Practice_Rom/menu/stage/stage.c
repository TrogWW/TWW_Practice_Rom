#ifndef STAGE_C_INCLUDED
#define STAGE_C_INCLUDED

#include "stage.h"
#include "room.c"

int stage__new(stage *this, void *data){
    this->stage_name = (int)data;
    this->room_count = *((int*)(data + 0x10));
    OSReport(MSL_C_PPCEABI_bare_H__printf("stage__new: data = %X | this->stage_name = %s | this->room_count = %d\n",data, this->stage_name, this->room_count));
    this->rooms = (room*)JKernel__operator_new(sizeof(int) * this->room_count);

    int current_address = (int)data;
    current_address = current_address + 0x14;
    for(int i = 0; i < this->room_count; i++){
        this->rooms[i] = (room*)JKernel__operator_new(sizeof(room));
        OSReport(MSL_C_PPCEABI_bare_H__printf("stage__new: current_address = %X\n",current_address));
        current_address = room__new(this->rooms[i], (void *)current_address);
    }
    return current_address;
}

#endif