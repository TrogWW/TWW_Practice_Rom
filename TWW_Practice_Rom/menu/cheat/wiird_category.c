#ifndef WIIRDCATEGORY_C_INCLUDED
#define WIIRDCATEGORY_C_INCLUDED

#include "wiird_category.h"
#include "wiird_code.c"

void wiird_category__new(wiird_category *this, int offset){
    if(this->category_name != 0){
        this->category_name = ((int)this->category_name) + offset;
    }
    if(this->code_count > 0){
        this->code_list = ((int)this->code_list) + offset;
    }
    for (int i = 0; i < this->code_count; i++)
    {
        wiird_code__new(&this->code_list[i], offset);
    }
}

#endif
