#ifndef WIIRDCODE_C_INCLUDED
#define WIIRDCODE_C_INCLUDED

#include "wiird_code.h"

void wiird_code__new(wiird_code *this, int offset){
    if(this->code_name != 0){
        this->code_name = ((int)this->code_name) + offset;
    }
    if(this->code_arr_count > 0){
        this->code_arr = ((int)this->code_arr) + offset;
    }
}
#endif