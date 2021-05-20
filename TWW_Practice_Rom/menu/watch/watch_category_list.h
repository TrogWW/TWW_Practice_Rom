#ifndef WATCHCATEGORYLIST_H_INCLUDED
#define WATCHCATEGORYLIST_H_INCLUDED

#include "watch_category.h"

typedef struct watch_category_list {
    int watch_category_count;
    watch_category *watch_categories;
} watch_category_list;

void watch_category_list__new(watch_category_list *this, int offset);

#endif