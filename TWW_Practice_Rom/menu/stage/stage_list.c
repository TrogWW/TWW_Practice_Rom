#ifndef STAGE_LIST_C_INCLUDED
#define STAGE_LIST_C_INCLUDED


#include "stage_list.h"
#include "../../helpers/stringhelpers.c"
#include "stage.c"

void stage_list__new(stage_list *this, void *data){
    this->stage_count = *((int*)data);
    OSReport(MSL_C_PPCEABI_bare_H__printf("stage_list__new: this->stage_count = %d\n",this->stage_count));
    this->stages = (stage*)JKernel__operator_new(sizeof(int) * this->stage_count);
    int current_address = (int)data;
    current_address = current_address + 4;
    for(int i = 0; i < this->stage_count; i++){
        this->stages[i] = (stage*)JKernel__operator_new(sizeof(stage));
        OSReport(MSL_C_PPCEABI_bare_H__printf("stage_list__new: current_address = %X\n",(void *)current_address));
        current_address = stage__new(this->stages[i], current_address);
    }
}
#endif