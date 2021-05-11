#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

typedef struct event {
    char *event_name;
    char *display_name;
    int room_index;
    int spawn_id;
    int demo_archive_number;
    int layer_id_count;
    int *layer_ids;
} event;


int event__new(event *this, int offset);

#endif