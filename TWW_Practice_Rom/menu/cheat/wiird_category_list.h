#ifndef WIIRDCATEGORYLIST_H_INCLUDED
#define WIIRDCATEGORYLIST_H_INCLUDED

#include "wiird_category.h"

typedef struct wiird_category_list{
    int category_count;
    wiird_category *categories;
} wiird_category_list;
void wiird_category_list__new(wiird_category_list *this, int offset);

#endif