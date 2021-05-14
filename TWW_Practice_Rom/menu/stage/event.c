#ifndef EVENT_C_INCLUDED
#define EVENT_C_INCLUDED

#include "event.h"

/*
typedef struct event {
    char *event_name;
    char *display_name;
    int room_index;
    int spawn_id;
    int demo_archive_number;
    int layer_id_count;
    int *layer_ids;
} event;

*/
int event__new(event *this, int offset){
    this->event_name = ((int)this->event_name) + offset;
    if(this->display_name != 0){
        this->display_name = ((int)this->display_name) + offset;
    }
    if(this->layer_id_count > 0){
        this->layer_ids = ((int)this->layer_ids) + offset;  
    }
    //OSReport(MSL_C_PPCEABI_bare_H__printf("event__new: event_name = %s | this->room_index = %d | this->spawn_id = %d | this->demo_archive_number = %d | this->layer_id_count = %d | this->layer_ids = %X\n",
        //this->event_name, this->room_index, this->spawn_id, this->demo_archive_number,this->layer_id_count,this->layer_ids));
}
#endif