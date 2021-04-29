// menu_pane.c inherits base_pane, implementation
#ifndef MENU_PANE_C_INCLUDED
#define MENU_PANE_C_INCLUDED
#include "menu_pane.h"
#include "base_pane.c"
#include "sub_pane_vertical.c"
#include "textbox/text_color_pallete.h"
#include "textbox/textbox.c"
#include "menu_ddlst.c"
#include "screen_capture.c"
#include "warp_pane.c"

#define GZ_MENU_BLO "gz-menu.blo"
#define root_TEXT 0x524f4f54
#define ROOT_TEXT 0x524f4f54
//#define WARP_TEXT 0x726f6f74

#define MAIN_TEXT 0x4D41494E
#define WPMN_TEXT 0x57504D4E
#define CHTS_TEXT 0x43485453
#define FLGS_TEXT 0x464c4753
#define WTCH_TEXT 0x57544348
#define DEBG_TEXT 0x44454247
#define STNG_TEXT 0x53544E47

static menu_pane_vtbl menu_pane____vt = {
    menu_pane_draw,
    menu_pane_hide,
    menu_pane_update_cursor
};

menu_pane* menu_pane___new(menu_pane *this, JKRArchive *menuArc){
    //stage_scls_info_class *sceneList =  (stage_scls_info_class *)getSceneList(0);
    //OSReport(MSL_C_PPCEABI_bare_H__printf("menu_pane___new: sceneList= %d\n",sceneList));

    //dStage__ObjectNameTable * d_stage__dStage_searchName(char * pName);

    //    dRes_info_c* mStageInfo = g_dComIfG_gameInfo.mResCtrl.mStageInfo;
    //    dRes_info_c* resInfo = dRes_control_c__getResInfo(RES_NAME, mStageInfo, 0x40);
    //    dRes_control_c__getRes("Stage", "stage.dzs", resInfo, 0x40);


    //d_stage::dStage_infoCreate(void) is also promising
    //    dRes_control_c::getRes("Stage","stage.dzs",d_com_inf_game::g_dComIfG_gameInfo.mResCtrl.mStageInfo,0x40);


    //itemicon.arc = item images
    //itemres.arc = check_00.bti = square selector
    //clctres.arc = other menu images (like triforce background)
    //menures.arc = other useful images (like hearts)
    //irmap.arc = ir_num_cross = X inside checkbox? + cool stuff like ir_cloth_piece01 for background


    if(this == 0){
        this = (menu_pane*)JKernel__operator_new(sizeof(menu_pane));
    }
    
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&menu_pane____vt;

    TBox2__float__ rect = {
        .mTL.x = 0.0f,
        .mTL.y = 0.0f,
        .mBR.x = 640.0f,
        .mBR.y = 480.0f
    };
    J2DPane__J2DPane(&this->screen.parent);
    this->screen.parent.mName = root_TEXT;
    this->screen.parent.mPosTL = rect.mTL;
    this->screen.parent.mPosBR = rect.mBR;
    this->screen.field_0xcf = 0;
    this->screen.field_0xd0 = COLOR_NONE;
    this->screen.mbClipToParent = 0;
    // This is sort of a hack because this is a C toolkit. We need to manually set what vtable our
    // UI element uses. Even though mMenuUI is a J2DScreen object, and its parent is a J2DPane,
    // we set the parent to use J2DScreen's vtable since J2DScreen is a child class of J2DPane.
    this->screen.parent.vtbl = &J2DScreen____vt;
    J2DScreen__set(&this->screen, GZ_MENU_BLO, menuArc);
    


    //OSReport(MSL_C_PPCEABI_bare_H__printf("menu_pane___new: this->secondary_window = %d\n",this->secondary_window));

    J2DPane* main_window = (J2DPane*)J2DScreen__search(&this->screen, MAIN_TEXT);
    this->base.pane = main_window;

    this->active = false;
    this->base.cursor_active = true;
    //this->base.xAxisOffset = 65.0f;
    //this->base.yAxisOffset = 80.0f;
    //this->base.width = 100.0f;

    J2DPane* warp_window = (J2DPane*)J2DScreen__search(&this->screen, WPMN_TEXT);
    J2DPane* cheats_window = (J2DPane*)J2DScreen__search(&this->screen, CHTS_TEXT);
    J2DPane* flags_window = (J2DPane*)J2DScreen__search(&this->screen, FLGS_TEXT);
    J2DPane* watches_window = (J2DPane*)J2DScreen__search(&this->screen, WTCH_TEXT);
    J2DPane* debug_window = (J2DPane*)J2DScreen__search(&this->screen, DEBG_TEXT);
    J2DPane* settings_window = (J2DPane*)J2DScreen__search(&this->screen, STNG_TEXT);
    
    float xPadding = 10.0f;
    float yPadding = 10.0f;
    float height = base_pane_height(&this->base);
    
    height = height - (2 * yPadding);
    
    float yOffset = height / 6.0f;

    OSReport(MSL_C_PPCEABI_bare_H__printf("menu_pane___new: height = %f | yOffset = %f\n",height, yOffset));

    this->sub_panes[0] = warp_pane__new(this->sub_panes[0], this, warp_window, xPadding, yPadding + (yOffset * 0));//, 10.0f, 0.0f, "Warp", &TEXT_PALLETE_WHITE, 0);
    this->sub_panes[1] = sub_pane_vertical__new(this->sub_panes[1], this, cheats_window, xPadding, yPadding + (yOffset * 1), "Cheats", &TEXT_PALLETE_GREY, 0);
    this->sub_panes[2] = sub_pane_vertical__new(this->sub_panes[2], this, flags_window, xPadding, yPadding + (yOffset * 2), "Flags", &TEXT_PALLETE_GREY, 0);
    this->sub_panes[3] = sub_pane_vertical__new(this->sub_panes[3], this, watches_window, xPadding, yPadding + (yOffset * 3), "Watches", &TEXT_PALLETE_GREY, 0);
    this->sub_panes[4] = sub_pane_vertical__new(this->sub_panes[4], this, debug_window, xPadding, yPadding + (yOffset * 4), "Debug", &TEXT_PALLETE_GREY, 0);
    this->sub_panes[5] = sub_pane_vertical__new(this->sub_panes[5], this, settings_window, xPadding, yPadding + (yOffset * 5), "Settings", &TEXT_PALLETE_GREY, 0);


    screen_capture___new(&this->capture);
    menu_ddlst___new(&this->menu_ddlst_item, this);
    return this;
}

void menu_pane_draw(menu_pane *this){
    menu_pane_update_cursor(this);
    J2DGrafContext* pCtx = (J2DGrafContext*)g_dComIfG_gameInfo.mp2DOrthoGraph;
    J2DGrafContext__setPort((J2DGrafContext*)g_dComIfG_gameInfo.mp2DOrthoGraph);

    //draw pane background
    J2DScreen__draw(&this->screen,0.0,0.0, pCtx);


    //draw sub pane titles
    for(int i = 0; i < 6; i++){
        if(this->base.cursor == i){
            this->sub_panes[i]->title.pallete = &TEXT_PALLETE_WHITE;
            this->sub_panes[i]->vptr->draw(this->sub_panes[i]);     
        }
        else{
            this->sub_panes[i]->title.pallete = &TEXT_PALLETE_GREY;
            this->sub_panes[i]->vptr->hide(this->sub_panes[i]);   
        }
        base_pane *sub_pane = this->sub_panes[i];
        GzTextBox__draw(&sub_pane->title);
    }
    //draw active sub pane
    //base_pane *active_sub_pane = this->sub_panes[this->base.cursor];

    //active_sub_pane->vptr->draw(active_sub_pane);
}

void menu_pane_hide(menu_pane *this){
    dDlst_MENU_CAPTURE_c__dDlst_MENU_CAPTURE_c_destructor(&this->capture.dDlst_screen_capture);
    d_menu_window__dMs_capture_c = 0;
    d_meter__dMenu_flagSet(0);
    d_meter__dMenu_setMenuStatus(1);
    d_meter__dMenu_setMenuStatusOld();
}

void menu_pane_update_cursor(menu_pane *this){
    if(this->base.cursor_active){
        if(DIGITAL_INPUTS[D_PAD_UP].pressed){
            this->base.cursor = this->base.cursor - 1;
            if(this->base.cursor < 0){
                this->base.cursor = 5; //screen wrap cursor
            }
        }
        else if(DIGITAL_INPUTS[D_PAD_DOWN].pressed){
            this->base.cursor = this->base.cursor + 1;
            if(this->base.cursor >= 6){
                this->base.cursor = 0;
            }
        }
        else if(DIGITAL_INPUTS[D_PAD_RIGHT].pressed){
            this->base.cursor_active = false;
        }
    }
    else{
        base_pane *active_sub_pane = this->sub_panes[this->base.cursor];
        active_sub_pane->vptr->update_cursor(active_sub_pane);
    }
}

void menu_pane__update_dDlst(menu_pane *this){
    d_meter__dMenu_flagSet(1);  //this is a flag the menu code checks to see if it should render screen capture. also pauses the game
    if(d_menu_window__dMs_capture_c == 0){
        //this is a pointer to a screen capture object.
        //set this value to our screen capture
        d_menu_window__dMs_capture_c = &this->capture;          
    }
    dDlst_list_c__set(&g_dComIfG_gameInfo.mDlstList,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpa,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpaEnd,
                    &this->menu_ddlst_item);

    d_meter__dMenu_flagSet(1);
    d_meter__dMenu_setMenuStatus(2);
    d_meter__dMenu_setMenuStatusOld();  
}
#endif