#ifndef WATCHCATEGORY_C_INCLUDED
#define WATCHCATEGORY_C_INCLUDED

#include "watch_category.h"
#include "watch_item.c"

/*
typedef struct watch_category {
    char *category;
    int watch_count;
    watch_item *watches;
} watch_category;
*/
void watch_category__new(watch_category *this, int offset){
    if(this->category != 0){
        this->category = ((int)this->category) + offset;
    }
    if(this->watch_count > 0){
        this->watches = ((int)this->watches) + offset;
    }
    for (int i = 0; i < this->watch_count; i++)
    {
        watch_item__new(&this->watches[i], offset);
    }
}
#endif