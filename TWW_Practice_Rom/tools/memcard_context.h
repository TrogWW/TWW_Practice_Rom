#ifndef MEMCARD_CONTEXT_H_INCLUDED
#define MEMCARD_CONTEXT_H_INCLUDED

#define SAVESTATE_MEMCARD 1
#define SAVESTATE_FILENAME "twwstate"
#define SAVESTATE_SIZE 0x40000//0x18000

#include "../DvdThd_PhaseHandler.h"

typedef struct memcard__data_context {
    void *data;
    int data_size;
    int data_offset;
} memcard__data_context;

typedef struct memcard__data_context_list {
    int memcard_offset;
    int context_len;
    memcard__data_context *data_context;
} memcard__data_context_list;

typedef struct memcard_context {
    DvdThd_PhaseHandler memcard_handler;
    card_file file;
    byte *work_area;
    card_savebuffer *buffer;
    int save_count;
    memcard__data_context_list data_context_list;
} memcard_context;


int memcard_context__mount(memcard_context *this);
int memcard_context__open(memcard_context *this);
int memcard_context__close(memcard_context *this);
int memcard_context__create(memcard_context *this);
int memcard_context__read(memcard_context *this);
int memcard_context__write(memcard_context *this);

void memcard_context__save_data(memcard_context *this, memcard__data_context_list* context_list);
void memcard_context__read_data(memcard_context *this, memcard__data_context_list* context_list);
#endif