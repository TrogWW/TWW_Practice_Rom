#ifndef DVDTHD_PHASE_HANDLER_C_INCLUDED
#define DVDTHD_PHASE_HANDLER_C_INCLUDED

#include "DvdThd_PhaseHandler.h"

DvdThd_PhaseHandlerList PHASE_HANDLER_LIST;

DvdThd_PhaseHandlerList__append(DvdThd_PhaseHandlerList *this, DvdThd_PhaseHandler *phase_handler){
    JSUPtrLink *new_link = (JSUPtrLink*)JKernel__operator_new(sizeof(JSUPtrLink));
    JSUPtrLink__JSUPtrLink(new_link, phase_handler);
    JSUPtrList__append(&this->list, new_link);
}
DvdThd_PhaseHandlerList__execute(DvdThd_PhaseHandlerList *this){
    JSUPtrLink *current_link = this->list.mpHead;

    while(current_link != 0 && current_link->mpData != 0){
        DvdThd_PhaseHandler *current_phase_handler = (DvdThd_PhaseHandler *)current_link->mpData;
        
        d_com_lib_game__dComLbG_PhaseHandler(&current_phase_handler->request_of_phase, current_phase_handler->phase_list, current_phase_handler->object);

        JSUPtrLink *temp_link = current_link;
        current_link = current_link->mpNext;
        if(current_phase_handler->complete){
            //OSReport(MSL_C_PPCEABI_bare_H__printf("DvdThd_PhaseHandlerList__execute: REMOVING PHASE HANDLER\n"));
            JSUPtrList__remove(&this->list, temp_link);
        }
    }
}
DvdThd_PhaseHandler__new(DvdThd_PhaseHandler *this, int (*phase_list[])(void *), void *object){
    this->phase_list = phase_list;
    this->object = object;
    this->complete = false;
}

#endif