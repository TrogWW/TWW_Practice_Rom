#ifndef WATCHCATEGORYLIST_C_INCLUDED
#define WATCHCATEGORYLIST_C_INCLUDED

#include "watch_category_list.h"
#include "watch_category.c"

/*
typedef struct watch_category_list {
    int watch_category_count;
    watch_category *watch_categories;
} watch_category_list;
*/
void watch_category_list__new(watch_category_list *this, int offset){
    if(this->watch_category_count > 0){
        this->watch_categories = ((int)this->watch_categories) + offset;
    }
    for (int i = 0; i < this->watch_category_count; i++)
    {
        watch_category__new(&this->watch_categories[i], offset);
    }
}
#endif