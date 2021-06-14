#ifndef WIIRD_LOADER_CONTEXT_C_INCLUDED
#define WIIRD_LOADER_CONTEXT_C_INCLUDED

#include "wiird_loader_context.h"
#include "../DvdThd_PhaseHandler.c"
#include "../menu/cheat/wiird_category_list.h"
#include "../menu/cheat/wiird_category.h"
#include "../menu/cheat/wiird_code.h"

// #define CODEHANDLER_DAT "/res/Menu/wiirdcodehandler.dat"
// //#define CODES_DAT "/res/Menu/codes.dat"


#define CODEHANDLER_DAT "/res/Menu/wiirdcodehandler.dat"
#define WIIRD_ADDRESS 0x80001800
#define WIIRD_EXECUTE_ADDRESS 0x800018A8    //location of _start function
#define WIIRD_CODELIST_ADDRESS 0x80001906
#define WIIRD_CODELIST_START 0x800022A8     //where to write GCT file
#define WIIRD_CODELIST_END_ADDRESS 0x80003000      

// #define CODEHANDLER_DAT "/res/Menu/wiirdcodehandler_debug.dat"
// #define WIIRD_ADDRESS 0x80001800
// #define WIIRD_EXECUTE_ADDRESS 0x800018A8    //location of _start function
// #define WIIRD_CODELIST_ADDRESS 0x80001906
// #define WIIRD_CODELIST_START 0x800028B8     //where to write GCT file
// #define WIIRD_CODELIST_END_ADDRESS 0x80003000      

byte CODE_LIST_HEADER[8] = { 0x00, 0xD0, 0xC0, 0xDE,0x00, 0xD0, 0xC0, 0xDE };
byte CODE_LIST_FOOTER[8] = { 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

wiird_code_list code_list;
void (*wiird__execute)(void) = (void (*)())WIIRD_EXECUTE_ADDRESS;

static int (*wiird_loader_phases[])(wiird_code_list *) = {
    wiird_loader__phase_1, wiird_loader__phase_2
};

int wiird_loader__phase_1(wiird_code_list *this){ 
    this->load_wiird_code_handler.data = mDoDvdThd_toMainRam_c__create(CODEHANDLER_DAT,0,(JKRHeap *)0x0);
    //this->load_gct_codes_handler.data = mDoDvdThd_toMainRam_c__create(CODES_DAT,0,(JKRHeap *)0x0);
    return 2;   //2 = next phase
}
int wiird_loader__phase_2(wiird_code_list *this){
    mDoDvdThd_toMainRam_c * wiird_code_data = (mDoDvdThd_toMainRam_c *)this->load_wiird_code_handler.data;
    //mDoDvdThd_toMainRam_c * gct_code_data = (mDoDvdThd_toMainRam_c *)this->load_gct_codes_handler.data;
    if(wiird_code_data->parent.mStatus == 0){// || gct_code_data->parent.mStatus == 0){
        return 0; //0 = not complete
    }
    else{
        //OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_loader__phase_2: FINISHED_LOADING this->menu_dat_thd->mpArchiveHeader = %X\n",wiird_code_data->mpArchiveHeader));

        cLib_memSet((void *)WIIRD_ADDRESS, 0, (int)((int)WIIRD_CODELIST_END_ADDRESS - (int)WIIRD_ADDRESS)); //clear wiird memory region
        
        copy_bytes((byte*)WIIRD_ADDRESS,(byte *)wiird_code_data->mpArchiveHeader,wiird_code_data->mHeapSize);   //write wiird bin to memory
        //copy_bytes((byte*)WIIRD_CODELIST_START,(byte *)gct_code_data->mpArchiveHeader,gct_code_data->mHeapSize);    //write code file to memory

        mDoDvdThd_toMainRam_c__mDoDvdThd_toMainRam_c_destructor(wiird_code_data);
        //mDoDvdThd_toMainRam_c__mDoDvdThd_toMainRam_c_destructor(gct_code_data);
        this->load_wiird_code_handler.complete = true;
        return 4; //4 = complete
    }
}

void wiird_code_list__add(wiird_code_list *this, wiird_code *code){
   // OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_code_list__add: ADDING code->code_name %s | code->code_name %X | code->code_arr_count %d | code_list %X\n", code->code_name, code->code_name, code->code_arr_count, &this->code_list));
    JSUPtrLink *new_link = (JSUPtrLink*)JKernel__operator_new(sizeof(JSUPtrLink));
    JSUPtrLink__JSUPtrLink(new_link, code);
    JSUPtrList__append(&this->code_list, new_link);
}

void wiird_code_list__write_bytes(wiird_code_list *this, byte *data, int length){
    copy_bytes(this->write_bytes_location, data, length);
    this->write_bytes_location = this->write_bytes_location + length;
    if(this->write_bytes_location > (byte *)WIIRD_CODELIST_END_ADDRESS){
        OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_code_list__write_bytes: Not enough memory to write cheat codes.\n"));
    }
}
void wiird_code_list__write_code_list(wiird_code_list *this){
    cLib_memSet((void *)WIIRD_CODELIST_START, 0, (int)((int)WIIRD_CODELIST_END_ADDRESS - (int)WIIRD_CODELIST_START)); //clear code list memory region

    this->write_bytes_location = (byte *)WIIRD_CODELIST_START;
    wiird_code_list__write_bytes(this, CODE_LIST_HEADER, 8);

    JSUPtrLink *current_link = this->code_list.mpHead;
    while(current_link != 0 && current_link->mpData != 0){
        wiird_code *code = (wiird_code *)current_link->mpData;
        //OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_code_list__write_code_list: LINKED CODE code->code_name = %s | code->code_arr_count = %d | code = %X\n", code->code_name, code));
        wiird_code_list__write_bytes(this, (byte *)code->code_arr, (int)(code->code_arr_count * 4));
        current_link = current_link->mpNext;
    }
    wiird_code_list__write_bytes(this, CODE_LIST_FOOTER, 8);
}

void wiird_code_list__create_category_list(wiird_code_list *this, wiird_category_list *category_list){
    //void JSUPtrList__JSUPtrList_destructor(JSUPtrList * this);
    
    //OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_code_list__create_category_list: BEFORE this->code_list.mCount = %d | category_list->category_count = %d | category_list = %X\n", this->code_list.mCount, category_list->category_count, category_list));
    if(this->code_list.mCount > 0){
        JSUPtrList__JSUPtrList_destructor(&this->code_list);    //reset code list
    }
    JSUPtrList__JSUPtrList(&this->code_list, true); 
    
    for(int i = 0; i < category_list->category_count; i++){
        wiird_category *curr_category = &category_list->categories[i];
        //OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_code_list__create_category_list: curr_category->category_name = %s | curr_category = %X\n", curr_category->category_name, curr_category));
        for(int j = 0; j < curr_category->code_count; j++){
            wiird_code *curr_code = &curr_category->code_list[j];
            if(curr_code->is_active == 1){
                wiird_code_list__add(this, curr_code);
            }
        }
    }
    //OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_code_list__create_category_list: AFTER this->code_list.mCount = %d\n", this->code_list.mCount));
    wiird_code_list__write_code_list(this);
}
#endif