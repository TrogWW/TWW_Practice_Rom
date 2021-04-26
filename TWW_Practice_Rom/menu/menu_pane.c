// menu_pane.c inherits base_pane, implementation
#include "../menu/menu_pane.h"
#include "textbox/text_color_pallete.h"

#define GZ_MENU_BLO "gz-menu.blo"
#define root_TEXT 0x524f4f54
#define ROOT_TEXT 0x524f4f54
#define WARP_TEXT 0x726f6f74

static menu_pane_vtbl menu_pane____vt = {
    menu_pane_draw,
    menu_pane_update_cursor
};

static void* dlst_vtbl[] = {
    NULL, NULL, // rtti placeholder
    dDlst_base_c__dDlst_base_c_destructor, // parent destructor
    menu_pane_draw
};

void menu_pane___new(menu_pane *this, JKRArchive *menuArc){
    if(this == 0){
        this = (menu_pane*)JKernel__operator_new(sizeof(menu_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&menu_pane____vt;

    //implement virtual function 'draw' for dDlst_base_c
    this->dDlst_base.vtbl = dlst_vtbl;

    J2DPane__J2DPane(&this->screen->parent);
    this->screen->parent.mName = root_TEXT;
    this->screen->parent.mPosTL = rect.mTL;
    this->screen->parent.mPosBR = rect.mBR;
    this->screen->field_0xcf = 0;
    this->screen->field_0xd0 = COLOR_NONE;
    this->screen->mbClipToParent = 0;
    // This is sort of a hack because this is a C toolkit. We need to manually set what vtable our
    // UI element uses. Even though mMenuUI is a J2DScreen object, and its parent is a J2DPane,
    // we set the parent to use J2DScreen's vtable since J2DScreen is a child class of J2DPane.
    this->screen->parent.vtbl = &J2DScreen____vt;

    J2DScreen__set(this->screen, GZ_MENU_BLO, menuArc);

    this->active = false;
    this->base.xAxisOffset = 80.0f;
    this->base.yAxisOffset = 40.0f;
    this->base.width = 100.0f;
    //float yPadding = 40.0f;
    sub_pane_vertical__new((sub_pane_vertical*)&this->sub_panes[0], this, 10.0f, 0.0f, "Warp", &TEXT_PALLETE_WHITE, 0);
    sub_pane_vertical__new((sub_pane_vertical*)&this->sub_panes[1], this, 10.0f, 40.0f, "Cheats", &TEXT_PALLETE_GREY, 0);
    sub_pane_vertical__new((sub_pane_vertical*)&this->sub_panes[2], this, 10.0f, 80.0f, "Flags", &TEXT_PALLETE_GREY, 0);
    sub_pane_vertical__new((sub_pane_vertical*)&this->sub_panes[3], this, 10.0f, 120.0f, "Watches", &TEXT_PALLETE_GREY, 0);
    sub_pane_vertical__new((sub_pane_vertical*)&this->sub_panes[4], this, 10.0f, 160.0f, "Debug", &TEXT_PALLETE_GREY, 0);
    sub_pane_vertical__new((sub_pane_vertical*)&this->sub_panes[5], this, 10.0f, 200.0f, "Settings", &TEXT_PALLETE_GREY, 0);
}

void menu_pane_draw(menu_pane const *this){
    J2DGrafContext* pCtx = (J2DGrafContext*)g_dComIfG_gameInfo.mp2DOrthoGraph;
    J2DGrafContext__setPort((J2DGrafContext*)g_dComIfG_gameInfo.mp2DOrthoGraph);

    //draw pane background
    J2DScreen__draw(this->screen,0.0,0.0, pCtx);

    //draw sub pane titles
    for(int i = 0; i < 6; i++){
        if(this->base.cursor == i){
            this->sub_panes[i].base.title.pallete = &TEXT_PALLETE_WHITE;     
        }
        else{
            this->sub_panes[i].base.title.pallete = &TEXT_PALLETE_GREY;
        }
        GzTextBox__draw(this->sub_panes[i].base.title);
    }
    //draw active sub pane
    base_pane *active_sub_pane = this->sub_panes[this->base.cursor];
    active_sub_pane->base.vptr->draw(active_sub_pane);
}
void menu_pane_update_cursor(menu_pane const *this){
    //insert logic here
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
        active_sub_pane->base.vptr->update_cursor(active_sub_pane);
    }
}

void menu_pane__update_dDlst(menu_pane const *this){
    d_meter__dMenu_flagSet(1);  //this is a flag the menu code checks to see if it should render screen capture. also pauses teh game
    if(d_menu_window__dMs_capture_c == 0){
        //this is a pointer to a screen capture object.
        //set this value to our screen capture
        d_menu_window__dMs_capture_c = &this->capture;          
    }
    dDlst_list_c__set(&g_dComIfG_gameInfo.mDlstList,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpa,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpaEnd,
                    this);

    d_meter__dMenu_flagSet(1);
    d_meter__dMenu_setMenuStatus(2);
    d_meter__dMenu_setMenuStatusOld();  
}