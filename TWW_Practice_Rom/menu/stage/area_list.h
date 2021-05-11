#ifndef AREALIST_H_INCLUDED
#define AREALIST_H_INCLUDED

#include "area.h"

typedef struct area_list{
    int area_count;
    area *areas;
} area_list;
void area_list__new(area_list *this, int offset);

#endif
