#ifndef AREALIST_C_INCLUDED
#define AREALIST_C_INCLUDED

#include "area_list.h"
#include "area.c"

void area_list__new(area_list *this, int offset){
    if(this->area_count > 0){
        this->areas = ((int)this->areas) + offset;
    }
    for (int i = 0; i < this->area_count; i++)
    {
        area__new(&this->areas[i], offset);
    }
}

#endif
