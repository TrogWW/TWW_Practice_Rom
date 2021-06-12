#ifndef WATCHCATEGORY_H_INCLUDED
#define WATCHCATEGORY_H_INCLUDED

#include "watch_item.h"
typedef struct watch_category {
    char *category;
    int watch_count;
    watch_item *watches;
} watch_category;

void watch_category__new(watch_category *this, int offset);

#endif