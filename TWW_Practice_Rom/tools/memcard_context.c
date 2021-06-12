#ifndef MEMCARD_CONTEXT_C_INCLUDED
#define MEMCARD_CONTEXT_C_INCLUDED

#include "memcard_context.h"
#include "../DvdThd_PhaseHandler.c"

memcard_context memcard = { .work_area = &m_Do_MemCard__MemCardWorkArea0, .buffer = &m_Do_MemCardRWmng__sTmpBuf };

memcard__data_context memcard_savestate_data[4] = { 
    {
        .data = (void *)0x803C4C08,
        .data_size = 23828
    },
    {
        .data = &d_a_player_main__l_debug_keep_pos,
        .data_size = 8192//sizeof(cXyz)
    },
    {
        .data = (void *)0x803F6F1E,
        .data_size = 2662
    },
    {
        .data = &g_dComIfG_gameInfo.mSvInfo,
        .data_size = sizeof(dSv_info_c)         //    /* 0x00 */ struct dSv_info_c mSvInfo; // 0x1258 bytes
    }  
};

memcard__data_context_list memcard_savestate_data_list = {
    .memcard_offset = 0,
    .context_len = 4,
    .data_context = &memcard_savestate_data
};

static int (*memcard_boot[])(memcard_context *) = {
    memcard_context__mount, memcard_context__open, memcard_context__close
};

static int (*memcard_write[])(memcard_context *) = {
    memcard_context__open, memcard_context__write, memcard_context__close
};

static int (*memcard_read[])(memcard_context *) = {
    memcard_context__open, memcard_context__read, memcard_context__close
};

int memcard_context__mount(memcard_context *this){ 
    //card_errors card__CARDMount(int card_slot, void * workarea, int detatch_cb);
    card_errors mount_status = card__CARDMount(SAVESTATE_MEMCARD, this->work_area, 0);
    OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__mount: mount_status = %X\n", mount_status));
    if(mount_status == card_errors__CARD_ERROR_READY){
        return 2; //2 = next phase
    }
    else{
        return 0;
    }
}
int memcard_context__open(memcard_context *this){ 
    //card_errors card__CARDOpen(int card_slot, char * filename, card_file * file);
    card_errors open_status = card__CARDOpen(SAVESTATE_MEMCARD, SAVESTATE_FILENAME, &this->file);
    OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__open: open_status = %X\n", open_status));
    if(open_status == card_errors__CARD_ERROR_READY){
        return 2; //2 = next phase
    }
    else if(open_status == card_errors__CARD_ERROR_NOFILE){
        return memcard_context__create(this);
    }
    else if(open_status == card_errors__CARD_ERROR_NOCARD){
        this->memcard_handler.complete = true;
        return cPhs_ERROR_e;
    }
    else{
        return 0;
    }
}
int memcard_context__close(memcard_context *this){ 
    //card_errors card__CARDClose(card_file * card_slot);
    card_errors close_status = card__CARDClose(&this->file);
    OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__close: close_status = %X\n", close_status));
    if(close_status == card_errors__CARD_ERROR_READY){
        this->memcard_handler.complete = true;
        return 4; //4 = complete
    }
    else{
        return 0;
    }
}
int memcard_context__create(memcard_context *this){ 
    //card_errors card__CARDCreate(int card_slot, char * filename, int size, card_file * file);
    card_errors create_status = card__CARDCreate(SAVESTATE_MEMCARD, SAVESTATE_FILENAME, SAVESTATE_SIZE, &this->file);
    OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__create: create_status = %X\n", create_status));
    if(create_status == card_errors__CARD_ERROR_READY){
        return 2; //2 = next phase
    }
    else{
        return 0;
    }
}
int memcard_context__read(memcard_context *this){ 
    card_errors read_status = 0;
    OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__write: this->data_context_list.context_len = %d\n", this->data_context_list.context_len));
    for(int i = 0; i < this->data_context_list.context_len; i++){
        memcard__data_context *curr_data_context = &this->data_context_list.data_context[i];
        int remaining_bytes = curr_data_context->data_size - curr_data_context->data_offset;
        while(remaining_bytes > 0){
            void *curr_data_offset = (void *)((int)curr_data_context->data + curr_data_context->data_offset);
            int curr_memcard_offset = this->data_context_list.memcard_offset;
            int len = remaining_bytes;
            if(remaining_bytes > sizeof(card_savebuffer)){
                len = sizeof(card_savebuffer);
            }

            OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__write: curr_data_offset = %X | curr_memcard_offset = %d | remaining_bytes = %d | len = %d\n", curr_data_offset,curr_memcard_offset,remaining_bytes,len));

            cLib_memSet(this->buffer, 0xff, sizeof(card_savebuffer)); //clear save buffer        
            read_status = card__CARDRead(&this->file, this->buffer, sizeof(card_savebuffer), curr_memcard_offset);


            OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__write: read_status = %X\n", read_status));
            if(read_status != card_errors__CARD_ERROR_READY){
                this->memcard_handler.complete = true;
                return cPhs_ERROR_e; 
            }
            else{
   
                copy_bytes(curr_data_offset, &this->buffer->mSaveData, len);
                remaining_bytes -= len;
                curr_data_context->data_offset += len;
                this->data_context_list.memcard_offset += sizeof(card_savebuffer);
            }
        }
    }
    if(read_status == card_errors__CARD_ERROR_READY){
        return 2;
    }
    else{
        this->memcard_handler.complete = true;
        return cPhs_ERROR_e;  
    }
    return read_status;
}
int memcard_context__write(memcard_context *this){ 
    card_errors write_status = 0;
    OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__write: this->data_context_list.context_len = %d\n", this->data_context_list.context_len));

    //int buffer_offset = 0;
    for(int i = 0; i < this->data_context_list.context_len; i++){
        memcard__data_context *curr_data_context = &this->data_context_list.data_context[i];
        int remaining_bytes = curr_data_context->data_size - curr_data_context->data_offset;
        while(remaining_bytes > 0){
            void *curr_data_offset = (void *)((int)curr_data_context->data + curr_data_context->data_offset);
            void *curr_buffer_offset = (void *)((int)this->buffer.mSaveData + curr_data_context->data_offset);

            int curr_memcard_offset = this->data_context_list.memcard_offset;
            int len = remaining_bytes;
            if(remaining_bytes > sizeof(card_savebuffer)){
                len = sizeof(card_savebuffer);
            }
            cLib_memSet(this->buffer, 0xff, sizeof(card_savebuffer)); //clear save buffer


            copy_bytes(&this->buffer->mSaveData, curr_data_offset, len);

            this->buffer->mSaveCount = this->save_count;

            OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__write: curr_data_offset = %X | curr_memcard_offset = %d | remaining_bytes = %d | len = %d\n", curr_data_offset,curr_memcard_offset,remaining_bytes,len));

            write_status = card__CARDWrite(&this->file, this->buffer, sizeof(card_savebuffer), curr_memcard_offset);
            OSReport(MSL_C_PPCEABI_bare_H__printf("memcard_context__write: write_status = %X\n", write_status));
            if(write_status != card_errors__CARD_ERROR_READY){
                this->memcard_handler.complete = true;
                return cPhs_ERROR_e; 
            }
            else{
                remaining_bytes -= len;
                curr_data_context->data_offset += len;
                this->data_context_list.memcard_offset += sizeof(card_savebuffer);
            }
        }
    }
    if(write_status == card_errors__CARD_ERROR_READY){
        return 2;
    }
    else{
        this->memcard_handler.complete = true;
        return cPhs_ERROR_e;  
    }
    return write_status;
}

void memcard_context__save_data(memcard_context *this, memcard__data_context_list* context_list){
    this->save_count += 1;
    copy_bytes(&this->data_context_list, context_list, sizeof(memcard__data_context_list));
    for(int i = 0; i < this->data_context_list.context_len; i++){
        memcard__data_context *curr_data_context = &this->data_context_list.data_context[i];
        curr_data_context->data_offset = 0;
    }
    DvdThd_PhaseHandler__new(&this->memcard_handler,&memcard_write, this);
    DvdThd_PhaseHandlerList__append(&PHASE_HANDLER_LIST, &this->memcard_handler);
}

void memcard_context__read_data(memcard_context *this, memcard__data_context_list* context_list){
    copy_bytes(&this->data_context_list, context_list, sizeof(memcard__data_context_list));
    for(int i = 0; i < this->data_context_list.context_len; i++){
        memcard__data_context *curr_data_context = &this->data_context_list.data_context[i];
        curr_data_context->data_offset = 0;
    }
    DvdThd_PhaseHandler__new(&this->memcard_handler,&memcard_read, this);
    DvdThd_PhaseHandlerList__append(&PHASE_HANDLER_LIST, &this->memcard_handler);
}

#endif