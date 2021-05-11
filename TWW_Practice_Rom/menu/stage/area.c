#ifndef AREA_C_INCLUDED
#define AREA_C_INCLUDED

#include "area.h"
#include "stage.c"

int area__new(area *this, int offset){
    this->area_name = ((int)this->area_name) + offset;
    this->stages = ((int)this->stages) + offset;


    OSReport(MSL_C_PPCEABI_bare_H__printf("area__new: area_name = %s\n",this->area_name));
    for (int i = 0; i < this->stage_count; i++)
    {
        //stage *s = &this->stages[i];
        stage__new(&this->stages[i], offset);
    }
    
}

#endif