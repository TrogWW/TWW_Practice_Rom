#ifndef WIIRD_LOADER_CONTEXT_C_INCLUDED
#define WIIRD_LOADER_CONTEXT_C_INCLUDED

#include "wiird_loader_context.h"
#include "../DvdThd_PhaseHandler.c"

#define CODEHANDLER_DAT "/res/Menu/codehandler.dat"
#define WIIRD_ADDRESS 0x80001800
#define WIIRD_EXECUTE_ADDRESS 0x800018A8
#define WIIRD_CODELIST_ADDRESS 0x80001906
#define WIIRD_CODELIST_END_ADDRESS 0x80003000


wiird_code_list code_list;
void (*wiird__execute)(void) = (void (*)())WIIRD_ADDRESS;

static int (*wiird_loader_phases[])(wiird_code_list *) = {
    wiird_loader__phase_1, wiird_loader__phase_2
};

int wiird_loader__phase_1(wiird_code_list *this){ 
    OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_loader__phase_1: PHASE 1\n"));
    this->load_wiird_code_handler.data = mDoDvdThd_toMainRam_c__create(CODEHANDLER_DAT,0,(JKRHeap *)0x0);
    return 2;   //2 = next phase
}
int wiird_loader__phase_2(wiird_code_list *this){
    OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_loader__phase_2: PHASE 2\n")); 
    mDoDvdThd_toMainRam_c * data = (mDoDvdThd_toMainRam_c *)this->load_wiird_code_handler.data;
    if(data->parent.mStatus == 0){
        return 0; //0 = not complete
    }
    else{
        OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_loader__phase_2: FINISHED_LOADING this->menu_dat_thd->mpArchiveHeader = %X\n",data->mpArchiveHeader));
        //warp_pane__set_stage_data((warp_pane*)this->sub_panes[0], data->mpArchiveHeader);
        //mHeapSize
        //copy_bytes(byte * dst, byte * src, int length);
        copy_bytes((byte*)WIIRD_ADDRESS,(byte *)data->mpArchiveHeader,data->mHeapSize);
        mDoDvdThd_toMainRam_c__mDoDvdThd_toMainRam_c_destructor(data);

        // int *code_list = (int *)WIIRD_CODELIST_ADDRESS;
        // *code_list = (int)0;


        copy_bytes((void *)0x80001800, (void*)0x80000000, 6);
	    memset((void *)WIIRD_CODELIST_ADDRESS, 0, (int)((int)WIIRD_CODELIST_ADDRESS - (int)WIIRD_CODELIST_ADDRESS));
        this->load_wiird_code_handler.complete = true;
        return 4; //4 = complete
    }
}

#endif