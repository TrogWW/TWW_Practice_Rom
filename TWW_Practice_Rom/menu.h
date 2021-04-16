
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



// Displaylist class for the menu's UI elements
typedef struct dDlst_menu_c {
    dDlst_base_c base;  //inherit dDlst_base_c
    J2DScreen* mMenuUI; // Pointer to the base UI element for the menu
    J2DPane* rootPane;
    J2DWindow* transparentBackground;
    J2DWindow* mainWindow;
    J2DWindow* warpWindow;
    dDlst_MENU_CAPTURE_c* screen_capture; // Pointer to the screen capture
} dDlst_menu_c;


void dDlst_menu_c__draw(dDlst_menu_c* this) {
    J2DScreen__draw(this->mMenuUI,0.0,0.0, &g_dComIfG_gameInfo.mp2DOrthoGraph->parent);    /*J2DScreen__draw(J2DScreen * this, float x, float y, J2DGrafContext * pCtx);*/
}

static void* dlst_vtbl[] = {
    NULL, NULL, // rtti placeholder
    dDlst_base_c__dDlst_base_c_destructor, // parent destructor
    dDlst_menu_c__draw,
};

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

    J2DScreen* menuScreen = (J2DScreen*)JKernel__operator_new(sizeof(J2DScreen));
    if (menuScreen != 0) {
        TBox2__float__ rect = {
            .mTL.x = 0.0f,
            .mTL.y = 0.0f,
            .mBR.x = 640.0f,
            .mBR.y = 480.0f
        };
        this->menu_dDlst.mMenuUI = menuScreen;

        //override virtual draw function from ddst_base_c
        this->menu_dDlst.base.vtbl = dlst_vtbl;

        // Create the parent J2DPane object for our UI elements.
        J2DPane__J2DPane(&this->menu_dDlst.mMenuUI->parent);
        this->menu_dDlst.mMenuUI->parent.mName = 0x524f4f54;//"ROOT";
        this->menu_dDlst.mMenuUI->parent.mPosTL = rect.mTL;
        this->menu_dDlst.mMenuUI->parent.mPosBR = rect.mBR;
        this->menu_dDlst.mMenuUI->field_0xcf = 0;
        
        // This is sort of a hack because this is a C toolkit. We need to manually set what vtable our
        // UI element uses. Even though mMenuUI is a J2DScreen object, and its parent is a J2DPane,
        // we set the parent to use J2DScreen's vtable since J2DScreen is a child class of J2DPane.
        this->menu_dDlst.mMenuUI->parent.vtbl = &J2DScreen____vt;
        this->menu_dDlst.mMenuUI = menuScreen;

        J2DScreen__set(this->menu_dDlst.mMenuUI, GZ_MENU_BLO, this->mMenuResArc);   /*undefined J2DScreen__set(J2DScreen * this, char * param_1, JKRArchive * param_2);*/
        this->menu_dDlst.rootPane = (J2DPane*)J2DScreen__search(this->menu_dDlst.mMenuUI, 0x524f4f54);
        if(this->menu_dDlst.rootPane == 0){
            OSReport("gzMenu: Failed to find root pane!");
            return cPhs_ERROR_e;
        }
        else{
            //REMOVED BG00 window from BLO for testing purposes
            //this->menu_dDlst.transparentBackground = (J2DWindow*)J2DPane__search((J2DPane*)this->menu_dDlst.rootPane,0x42473030); /*BG00*/
            /*

            if(this->menu_dDlst.transparentBackground == 0){
                OSReport("gzMenu: Failed to find transparent background window");
                return cPhs_ERROR_e;
            }
            */
            this->menu_dDlst.mainWindow = (J2DWindow*)J2DPane__search((J2DPane*)this->menu_dDlst.rootPane,0x4D41494E); //MAIN
            if(this->menu_dDlst.mainWindow == 0){
                OSReport("gzMenu: Failed to find main window");
                return cPhs_ERROR_e;
            }

            this->menu_dDlst.warpWindow = (J2DWindow*)J2DPane__search((J2DPane*)this->menu_dDlst.rootPane,0x57504D4E); /*WPMN*/
            if(this->menu_dDlst.warpWindow == 0){
                OSReport("gzMenu: Failed to find warp window");
                return cPhs_ERROR_e;
            }
            //make screen capture object
            this->menu_dDlst.screen_capture = (dDlst_MENU_CAPTURE_c*)JKernel__operator_new(sizeof(dDlst_MENU_CAPTURE_c));
            if(this->menu_dDlst.screen_capture == 0){
                OSReport("gzMenu: Failed to make screen capture!");
                return cPhs_ERROR_e;
            }
            return cPhs_COMPLEATE_e;
        }
    }
    else{
        OSReport("gzMenu: Failed to find main menu screen!");
        return cPhs_ERROR_e;
    }
}

PhaseState _menu_create(Menu* this){
    PhaseState phaseState = dComIfG_resLoad(&this->mPhaseRequest, RES_NAME);
    if (phaseState != cPhs_COMPLEATE_e) {
        // Not finished loading yet, check again next frame.
        OSReport("gzMenu: Res not loaded");
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

    return menu__CreateUI(this);
}

bool _menu_draw(Menu* this){


    dDlst_list_c__set(&g_dComIfG_gameInfo.mDlstList,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpa,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpaEnd,
                    &this->menu_dDlst);
    return true;
}
//TODO: Finish destroying menu after render. Not bothering right now since rendering still isn't working...
//Reopening menu after closing once will crash
void _menu_destroy(Menu* this){

    //Settings these flags will 'unpause' gameplay
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
            PhaseState state = _menu_create(&menu);
            if(state == cPhs_COMPLEATE_e){
                menu.enabled = true;
            }
            if(state != 0){
                menu.toggle_menu = currentFrame;    /*button combo will need to wait 30 frames until checked again*/
            }
        }
        else if(currentInput == destroy_menu_combo && menu.enabled == true){
            _menu_destroy(&menu);
            menu.toggle_menu = currentFrame;
            menu.enabled = false;
        }
    }
    if(menu.enabled == true){
        _menu_draw(&menu);
    }   
}
    //Settings these flags will 'pause' gameplay
    /*
    d_meter__dMenu_flagSet(1);
    d_meter__dMenu_setMenuStatus(2);
    d_meter__dMenu_setMenuStatusOld();*/