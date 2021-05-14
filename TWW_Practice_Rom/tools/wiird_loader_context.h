#ifndef WIIRD_LOADER_CONTEXT_H_INCLUDED
#define WIIRD_LOADER_CONTEXT_H_INCLUDED

#include "../DvdThd_PhaseHandler.h"


typedef struct wiird_code_list {
    DvdThd_PhaseHandler load_wiird_code_handler;
} wiird_code_list;

int wiird_loader__phase_1(wiird_code_list *this);
int wiird_loader__phase_2(wiird_code_list *this);

#endif