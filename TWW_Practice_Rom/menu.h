
#ifndef _SETTINGS_H
    #define _SETTINGS_H "settings.h"
    #include _SETTINGS_H
#endif
#ifndef _MEMORY_H
    #define _MEMORY_H "memory.h"
    #include _MEMORY_H
#endif

typedef struct Menu {
    dDlst_MENU_CAPTURE_c* screen_capture;
    bool enabled;
    int toggle_menu;
    Settings* menu_settings;  
} Menu;

Menu menu = {
    .screen_capture = 0,
    .enabled = false,
    .toggle_menu = 0,
    .menu_settings = &settings
};
void _menu_create(){
   /* dDlst_MENU_CAPTURE_c** capture = dMs_capture_c;
    capture = (dDlst_MENU_CAPTURE_c**)JKernel__operator_new(8);

    *capture = (dDlst_MENU_CAPTURE_c*)&dDlst_base_c____vt;
    *capture = &dDlst_MENU_CAPTURE_c____vt;
    *(dDlst_MENU_CAPTURE_c*)(capture + 1) = 0;*/
   
    dDlst_MENU_CAPTURE_c* screen_capture = (dDlst_MENU_CAPTURE_c*)JKernel__operator_new(sizeof(dDlst_MENU_CAPTURE_c));
    dDlst_MENU_CAPTURE_c__draw(screen_capture);

    menu.screen_capture = screen_capture;
    d_meter__dMenu_flagSet(1);
    d_meter__dMenu_setMenuStatus(2);
    d_meter__dMenu_setMenuStatusOld();
}
void _menu_destroy(){
    d_meter__dMenu_flagSet(0);
    d_meter__dMenu_setMenuStatus(1);
    d_meter__dMenu_setMenuStatusOld();
    dDlst_MENU_CAPTURE_c__dDlst_MENU_CAPTURE_c_destructor(menu.screen_capture);
}
void _menu_exec(Settings* settings){
    short currentInput = _input_current_digital();
    short activate_menu_combo = settings->toggle_menu_combo[0] + settings->toggle_menu_combo[1];
    short destroy_menu_combo = B;

    int currentFrame = *FRAME_COUNT_PTR;
    if(menu.toggle_menu + 30 <= currentFrame){ /*Check if enough time has passed since last menu press*/
        if(currentInput == activate_menu_combo && menu.enabled == false){
            _menu_create();
            menu.toggle_menu = currentFrame;
            menu.enabled = true;
        }
        else if(currentInput == destroy_menu_combo && menu.enabled == true){
            _menu_destroy();
            menu.toggle_menu = currentFrame;
            menu.enabled = false;
        }
    }
    if(menu.enabled == true){
        dDlst_MENU_CAPTURE_c__draw(menu.screen_capture);
    }   
}