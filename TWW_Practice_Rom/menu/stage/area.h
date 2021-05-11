#ifndef AREA_H_INCLUDED
#define AREA_H_INCLUDED

#include "stage.h"

typedef struct area {
    char *area_name;
    int stage_count;
    stage *stages;
} area;


int area__new(area *this, int offset);
#endif