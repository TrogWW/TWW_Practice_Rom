#ifndef STAGE_C_INCLUDED
#define STAGE_C_INCLUDED

#include "stage.h"
void stage__get_entrances(stage *this){
    //uVar1 = mDoDvdThd_toMainRam_c::create("/res/Menu/Menu1.dat",0,(JKRHeap *)0x0);
    void *d_s_menu_request = (void *)JKernel__operator_new(1000);
    mDoDvdThd_toMainRam_c * menu1_data = 0;
    int phase = 0;
    while(phase != 2){
        phase = d_s_menu__phase_1(d_s_menu_request);     
    } 
    phase = 0;
    while(phase != 4){
        phase = d_s_menu__phase_2(d_s_menu_request);     
    } 
    OSReport(MSL_C_PPCEABI_bare_H__printf("stage__get_entrances: d_s_menu_request: %X\n",d_s_menu_request));  
    //dRes_control_c__setStageRes(dRes_control_c * this, char * param_1, JKRHeap * param_2);
    //dRes_control_c *res_control_c = (dRes_control_c *)JKernel__operator_new(sizeof(dRes_control_c));

}
void stage__new(stage *this, char *name){
    size_t name_len = MSL_C_PPCEABI_bare_H__strlen(name);
    this->stage_name = (char *)JKernel__operator_new(sizeof(char) * (name_len + 1));
    MSL_C_PPCEABI_bare_H__strcpy(this->stage_name, name);
    this->stage_name[name_len] = '\0';
    //this->stage_name = name;
    JSUPtrList__JSUPtrList(&this->rooms,true);

    //stage__get_entrances(this);

}
void stage_append_room(stage *this, char* room_num){
    JSUPtrLink *room_num_item = (JSUPtrLink *)JKernel__operator_new(sizeof(JSUPtrLink));
    JSUPtrLink__JSUPtrLink(room_num_item, room_num);
    JSUPtrList__append(&this->rooms,room_num_item);
}
#endif

//  PhaseState phaseState = dComIfG_resLoad(&this->mPhaseRequest, RES_NAME);
//     if (phaseState != cPhs_COMPLEATE_e) {
//         // Not finished loading yet, check again next frame.
//         return phaseState;
//     }

//     // Load our resource archive and store a pointer to it
//     dRes_info_c* mObjectInfo = g_dComIfG_gameInfo.mResCtrl.mObjectInfo;
//     dRes_info_c* resInfo = dRes_control_c__getResInfo(RES_NAME, mObjectInfo, 0x40);
//     if(resInfo == 0){
//         OSReport("gzMenu: Failed to get res info!");
//         return cPhs_ERROR_e;
//     }
//     this->mMenuResArc = resInfo->mpArchive;
//     return cPhs_COMPLEATE_e;