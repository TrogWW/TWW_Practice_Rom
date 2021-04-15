
#ifndef _SETTINGS_H
    #define _SETTINGS_H "settings.h"
    #include _SETTINGS_H
#endif
#ifndef _MEMORY_H
    #define _MEMORY_H "memory.h"
    #include _MEMORY_H
#endif
#define GZ_MENU_BLO "gz-menu.blo"
#define RES_NAME "gzmenu"
// Displaylist class for the clock's UI elements
typedef struct dDlst_menu_c {
  /*virtual void draw() override;*/
    dDlst_base_c base;  //inherit dDlst_base_c
    J2DScreen* mMenuUI; // Pointer to the base UI element for the clock
    J2DPane* rootPane;
    dDlst_MENU_CAPTURE_c* screen_capture; // Pointer to the screen capture
} dDlst_menu_c;

void dDlst_menu_c__draw(dDlst_menu_c* this) {
    /*mpClockUI->draw(0.0, 0.0, &g_dComIfG_gameInfo.mp2DOrthoGraph);*/
    J2DScreen__draw(this->mMenuUI,0.0,0.0, &g_dComIfG_gameInfo.mp2DOrthoGraph); /*J2DScreen__draw(J2DScreen * this, float x, float y, J2DGrafContext * pCtx);*/
}

typedef struct Menu {
    request_of_phase_process_class* mPhaseRequest;
    JKRArchive* mMenuResArc; // Pointer to our resource archive (BLO, images)
    dDlst_menu_c menu_dDlst;

    bool enabled;
    int toggle_menu;
    Settings* menu_settings;  
} Menu;

Menu menu = {
    .mPhaseRequest = 0,
    .mMenuResArc = 0,
    .menu_dDlst = 0,
    .enabled = false,
    .toggle_menu = 0,
    .menu_settings = &settings
};

PhaseState menu__CreateUI(Menu* this) {
    dDlst_MENU_CAPTURE_c* screen_capture = (dDlst_MENU_CAPTURE_c*)JKernel__operator_new(sizeof(dDlst_MENU_CAPTURE_c));
    if(screen_capture == 0){
        OSReport("gzMenu: Failed to make screen capture!");
        return cPhs_ERROR_e;
    }
    J2DScreen * menuScreen = (J2DScreen*)JKernel__operator_new(sizeof(J2DScreen));
    if (menuScreen != 0) {
        this->menu_dDlst.mMenuUI->parent.vtbl = &J2DScreen____vt;
        J2DScreen__set(menuScreen, GZ_MENU_BLO, this->mMenuResArc);   /*undefined J2DScreen__set(J2DScreen * this, char * param_1, JKRArchive * param_2);*/
        J2DPane* rootPane = (J2DPane*)J2DScreen__search(menuScreen, 0x524f4f54);
        if(rootPane == 0){
            OSReport("gzMenu: Failed to find root pane!");
            return cPhs_ERROR_e;
        }
        else{
            this->menu_dDlst.screen_capture = screen_capture;
            this->menu_dDlst.mMenuUI = menuScreen;
            this->menu_dDlst.rootPane = rootPane;
            return cPhs_COMPLEATE_e;
        }
    }
    else{
        OSReport("gzMenu: Failed to find main menu screen!");
        return cPhs_ERROR_e;
    }
}

PhaseState _menu_create(Menu* this){
    PhaseState phaseState = dComIfG_resLoad(this->mPhaseRequest, RES_NAME);
    if (phaseState != cPhs_COMPLEATE_e) {
        // Not finished loading yet, check again next frame.
        return phaseState;
    }

    // Load our resource archive and store a pointer to it
    dRes_info_c* resInfo = dRes_control_c__getResInfo(RES_NAME, g_dComIfG_gameInfo.mResCtrl.mObjectInfo, 0x40);

    this->mMenuResArc = resInfo->mpArchive;

    return menu__CreateUI(this);
}

bool _menu_draw(Menu* this){
    /*void dDlst_list_c__set(dDlst_list_c * this, dDlst_base_c * * * pLst, dDlst_base_c * * * * pEnd, dDlst_base_c * pPacket);*/
    dDlst_list_c__set(&g_dComIfG_gameInfo.mDlstList, &g_dComIfG_gameInfo.mDlstList.mp2DOpa, &g_dComIfG_gameInfo.mDlstList.mp2DOpaEnd,&this->menu_dDlst);
    /*g_dComIfG_gameInfo.mDlstList.set(&g_dComIfG_gameInfo.mDlstList.mp2DOpa,&g_dComIfG_gameInfo.mDlstList.mp2DOpaEnd,&this->menu_dDlst);*/
    return true;
}
void _menu_destroy(Menu* this){
    /*d_meter__dMenu_flagSet(0);
    d_meter__dMenu_setMenuStatus(1);
    d_meter__dMenu_setMenuStatusOld();*/
    dDlst_MENU_CAPTURE_c__dDlst_MENU_CAPTURE_c_destructor(this->menu_dDlst.screen_capture);
    J2DScreen__J2DScreen_destructor(this->menu_dDlst.mMenuUI);
}
void _menu_exec(Settings* settings){
    short currentInput = _input_current_digital();
    short activate_menu_combo = settings->toggle_menu_combo[0] + settings->toggle_menu_combo[1];
    short destroy_menu_combo = B;

    int currentFrame = *FRAME_COUNT_PTR;
    if(menu.toggle_menu + 30 <= currentFrame){ /*Check if enough time has passed since last menu press*/
        if(currentInput == activate_menu_combo && menu.enabled == false){
            menu.toggle_menu = currentFrame;    /*button combo will need to wait 30 frames until checked again*/
            PhaseState state = _menu_create(&menu);
            if(state == cPhs_COMPLEATE_e){
                menu.enabled = true;
            }
        }
        else if(currentInput == destroy_menu_combo && menu.enabled == true){
            _menu_destroy(&menu);
            menu.toggle_menu = currentFrame;
            menu.enabled = false;
        }
    }
    if(menu.enabled == true){
        /*dDlst_MENU_CAPTURE_c__draw(menu.screen_capture);*/
        _menu_draw(&menu);
    }   
}

   /*dDlst_MENU_CAPTURE_c__draw(screen_capture);

    menu.screen_capture = screen_capture;
    menu.scene = scene;
    d_meter__dMenu_flagSet(1);
    d_meter__dMenu_setMenuStatus(2);
    d_meter__dMenu_setMenuStatusOld();*/