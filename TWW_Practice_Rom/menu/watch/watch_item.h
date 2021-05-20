#ifndef WATCHITEM_H_INCLUDED
#define WATCHITEM_H_INCLUDED


typedef struct watch_item {
    char *display_name;
    int is_active;
    char *flag;
    int address_offset_count;
    int *address_offsets;
} watch_item;

void watch_item__new(watch_item *this, int offset);

#endif