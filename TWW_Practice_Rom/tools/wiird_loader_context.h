#ifndef WIIRD_LOADER_CONTEXT_H_INCLUDED
#define WIIRD_LOADER_CONTEXT_H_INCLUDED

#include "../DvdThd_PhaseHandler.h"
#include "../menu/cheat/wiird_code.h"

typedef struct wiird_code_list {
    DvdThd_PhaseHandler load_wiird_code_handler;
    JSUPtrList code_list;
    byte *write_bytes_location

} wiird_code_list;

int wiird_loader__phase_1(wiird_code_list *this);
int wiird_loader__phase_2(wiird_code_list *this);
void wiird_code_list__add(wiird_code_list *this, wiird_code *code);

void wiird_code_list__write_bytes(wiird_code_list *this, byte *data, int length);
void wiird_code_list__write_code_list(wiird_code_list *this);

#endif