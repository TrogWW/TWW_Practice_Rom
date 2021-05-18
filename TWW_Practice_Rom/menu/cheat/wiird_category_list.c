#ifndef WIIRDCATEGORYLIST_C_INCLUDED
#define WIIRDCATEGORYLIST_C_INCLUDED

#include "wiird_category_list.h"
#include "wiird_category.c"

void wiird_category_list__new(wiird_category_list *this, int offset){
    if(this->category_count > 0){
        this->categories = ((int)this->categories) + offset;
    }
    for (int i = 0; i < this->category_count; i++)
    {
        wiird_category__new(&this->categories[i], offset);
    }
}

#endif