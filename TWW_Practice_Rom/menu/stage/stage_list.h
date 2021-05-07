#ifndef STAGE_LIST_H_INCLUDED
#define STAGE_LIST_H_INCLUDED

#include "stage.h"

typedef struct stage_list{
    int stage_count;
    stage **stages;
} stage_list;
void stage_list__new(stage_list *this, void *data);
#endif