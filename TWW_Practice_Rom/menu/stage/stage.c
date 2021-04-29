#ifndef STAGE_C_INCLUDED
#define STAGE_C_INCLUDED

#include "stage.h"
void stage__new(stage *this, char *name){
    size_t name_len = MSL_C_PPCEABI_bare_H__strlen(name);
    this->stage_name = (char *)JKernel__operator_new(sizeof(char) * (name_len + 1));
    MSL_C_PPCEABI_bare_H__strcpy(this->stage_name, name);
    this->stage_name[name_len] = '\0';
    //this->stage_name = name;
    JSUPtrList__JSUPtrList(&this->rooms,true);
}
void stage_append_room(stage *this, int room_num){
    JSUPtrLink *room_num_item = (JSUPtrLink *)JKernel__operator_new(sizeof(JSUPtrLink));
    JSUPtrLink__JSUPtrLink(room_num_item, room_num);
    JSUPtrList__append(&this->rooms,room_num_item);
}
#endif