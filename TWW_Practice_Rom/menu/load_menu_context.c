#ifndef LOAD_MENU_CONTEXT_C_INCLUDED
#define LOAD_MENU_CONTEXT_C_INCLUDED
#include "load_menu_context.h"
#define RES_NAME "gzmenu"

PhaseState load_menu(load_menu_context *this){
        //undefined mDoDvdThd_toMainRam_c__create(char * pFilePath, byte direction, JKRHeap * pHeap);
    //uVar1 = mDoDvdThd_toMainRam_c::create("/res/Menu/Menu1.dat",0,(JKRHeap *)0x0);
    int response = mDoDvdThd_toMainRam_c__create("/res/Menu/Menu1.dat",0,(JKRHeap *)0x0);

    OSReport(MSL_C_PPCEABI_bare_H__printf("stage_list__loadFromDVD: response: %X\n",response));
    if (mDoExt_font0 == (JUTFont *)0x0) {
        return 0;
    }
    PhaseState phaseState = dComIfG_resLoad(&this->mPhaseRequest, RES_NAME);
    if (phaseState != cPhs_COMPLEATE_e) {
        // Not finished loading yet, check again next frame.
        return phaseState;
    }

    // Load our resource archive and store a pointer to it
    dRes_info_c* mObjectInfo = g_dComIfG_gameInfo.mResCtrl.mObjectInfo;
    dRes_info_c* resInfo = dRes_control_c__getResInfo(RES_NAME, mObjectInfo, 0x40);
    if(resInfo == 0){
        OSReport("gzMenu: Failed to get res info!");
        return cPhs_ERROR_e;
    }
    this->mMenuResArc = resInfo->mpArchive;
    return cPhs_COMPLEATE_e;
}
#endif