#ifndef STAGE_LIST_H_INCLUDED
#define STAGE_LIST_H_INCLUDED

#include "stage.h"

typedef struct stage_list{
    JSUPtrList stages;
} stage_list;
void stage_list__new(stage_list *this);
void stage_list__loadFromDVD(stage_list *this);
void stage_list__append_stage(stage_list *this, stage *s);

#endif