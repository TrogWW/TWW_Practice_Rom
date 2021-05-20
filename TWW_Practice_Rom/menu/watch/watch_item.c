#ifndef WATCHITEM_C_INCLUDED
#define WATCHITEM_C_INCLUDED

#include "watch_item.h"

/*
typedef struct watch_item {
    char *display_name;
    int is_active;
    char *flag;
    int address_offset_count;
    int *address_offsets;
} watch_item;
*/
void watch_item__new(watch_item *this, int offset){
    if(this->display_name != 0){
        this->display_name = ((int)this->display_name) + offset;
    }
    if(this->flag != 0){
        this->flag = ((int)this->flag) + offset;
    }
    if(this->address_offset_count > 0){
        this->address_offsets = ((int)this->address_offsets) + offset;
    }
}

#endif