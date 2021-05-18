#ifndef WIIRDCATEGORY_H_INCLUDED
#define WIIRDCATEGORY_H_INCLUDED

#include "wiird_code.h"

typedef struct wiird_category {
    char *category_name;
    int code_count;
    wiird_code *code_list;
} wiird_category;
void wiird_category__new(wiird_category *this, int offset);

#endif
