#ifndef WIIRDCODE_H_INCLUDED
#define WIIRDCODE_H_INCLUDED

typedef struct wiird_code {
    char *code_name;
    int is_active;
    int code_arr_count;
    int *code_arr;
} wiird_code;

void wiird_code__new(wiird_code *this, int offset);
#endif