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


typedef struct GzMenu_Capture {
    dDlst_base_c base;  //inherit dDlst_base_c
    dDlst_MENU_CAPTURE_c screen_capture; // Pointer to the screen capture
} GzMenu_Capture;

void dDlst_gzMenu_Capture__draw(GzMenu_Capture* this){
    dDlst_MENU_CAPTURE_c__draw(&this->screen_capture); 
}

typedef struct GzTextBox {
    J2DTextBox textBox;
    JUTFont* font;
    float xAxisOffset;
    float yAxisOffset;
    float width;
    bool active;
    char* text;
    _GXColor* topColorGradiant;
    _GXColor* bottomColorGradiant;
    _GXColor* textColor;
    _GXColor* textBackgroundColor;
} GzTextBox;

void GzTextBox__draw(GzTextBox* this){
    this->textBox.field_0xd0 = (_GXColor)*this->topColorGradiant;
    this->textBox.field_0xd4 = (_GXColor)*this->bottomColorGradiant;
    this->textBox.field_0xf4 = (_GXColor)*this->textColor;
    this->textBox.field_0xf8 = (_GXColor)*this->textBackgroundColor;
        /* 0xD0 */ struct _GXColor field_0xd0; // 0x04 bytes
    /* 0xD4 */ struct _GXColor field_0xd4; // 0x04 bytes
    J2DTextBox__setFont(&this->textBox, this->font);
    //J2DTextBox__setString(&this->textBox, this->text);
    J2DTextBox__draw(&this->textBox,this->xAxisOffset,this->yAxisOffset,this->width,2); //2 = hbinding left
}

void GzTextBox__create(GzTextBox* this, float xAxisOffset, float yAxisOffset, float width, char* text, bool active){
    JUTResFont* resFont = mDoExt_resfont0;
    TBox2__float__ rect = {
        .mTL.x = 0.0f,
        .mTL.y = 0.0f,
        .mBR.x = 0.0f,
        .mBR.y = 0.0f
    };
    //J2DTextBox__J2DTextBox(J2DTextBox * this, char * param_1, char * param_2);

    J2DTextBox__J2DTextBox(&this->textBox,(char*)0,(char*)0);
    J2DTextBox__initiate(&this->textBox, resFont, text, 0,0);
    this->xAxisOffset = xAxisOffset;
    this->yAxisOffset = yAxisOffset;
    this->width = width;
    this->text = this->textBox.mpStringPtr;
    if(active == true){
        this->topColorGradiant = &COLOR_WHITE;
        this->bottomColorGradiant = &COLOR_WHITE;
        this->textColor = &COLOR_WHITE;
        this->textBackgroundColor = &COLOR_NONE;
    }
    else{
        this->topColorGradiant = &COLOR_GREY;
        this->bottomColorGradiant = &COLOR_GREY;
        this->textColor = &COLOR_GREY;
        this->textBackgroundColor = &COLOR_NONE;
    }
    this->active = active;
}


typedef struct GzMenu {
    dDlst_base_c base;  //inherit dDlst_base_c
    bool enabled;
    int toggle_menu;
    int cursor;
    GzTextBox mainTextBoxes[6];
    Settings* menu_settings;  
    request_of_phase_process_class* mPhaseRequest;
    PhaseState phase;
    JKRArchive* mMenuResArc; // Pointer to our resource archive (BLO, images)
    J2DScreen* screen; // Pointer to the base UI element for the menu
    GzMenu_Capture capture; // Pointer to the screen capture
    JUTFont* font;
} GzMenu;

GzMenu gzMenu = {
    .cursor = 0,
    .mPhaseRequest = 0,
    .mMenuResArc = 0,
    .screen = 0,
    .font = 0,
    .enabled = false,
    .phase = 0,
    .toggle_menu = 0,
    .menu_settings = &settings
};


void dDlst_gzMenu__draw(GzMenu* this) {
    //f_op_msg_mng::fopMsgM_setAlpha(&this->nm00_textbox);
    //undefined f_op_msg_mng__fopMsgM_setAlpha(fopMsgM_pane_class * param_1);



    J2DGrafContext* pCtx = (J2DGrafContext*)g_dComIfG_gameInfo.mp2DOrthoGraph;
    J2DGrafContext__setPort((J2DGrafContext*)g_dComIfG_gameInfo.mp2DOrthoGraph);
    J2DScreen__draw(this->screen,0.0,0.0, pCtx);    

   /*
    TBox2<float> *textBoundary = new JGeometry::TBox2<f>::TBox2<f>(double x1, double y1, double x2, double y2);

    J2DTextBox *textBox = new J2DTextBox::J2DTextBox(u64 tagName = 0x5445585431, TBox2<float> *boundary = textBoundary, ResFONT *resfont = (ResFONT *)"FONTbfn1", char *text = "blabla", short allocbyte = -1, J2DTextBoxHBinding hbinding, J2DTextBoxVBinding vbinding);

    textBox->setFontSize((TFontSize* fontSize);
    textBox->setCharSpace(double charSpace);
    textBox->setLineSpace(double lineSpace);
    textBox->setCharColor(TColor* charColor);
    textBox->setGradColor(TColor* gradientColor);
    textBox->setBlackWhite(TColor* black, TColor* white);
    textBox->draw(double posH, double posV, double width, J2DTextBoxHBinding hbinding);

    delete textBox;
    */
    //undefined J2DTextBox__initiate(J2DTextBox * this, ResFONT * param_1, char * param_2, J2DTextBoxHBinding param_3, J2DTextBoxVBinding param_4);
    //void J2DTextBox__J2DTextBox(J2DTextBox * this, ulong param_1, TBox2__float__ * param_2, ResFONT * param_3, char * param_4, J2DTextBoxHBinding param_5, J2DTextBoxVBinding param_6);
    //undefined J2DTextBox__draw(J2DTextBox * this, float param_1, float param_2, float param_3, J2DTextBoxHBinding param_4);
    

    //hBinding 2 = LEFT
    for(int i = 0; i < 6; i++){
        GzTextBox__draw(&this->mainTextBoxes[i]);
    }
    

}

static void* dlst_vtbl[] = {
    NULL, NULL, // rtti placeholder
    dDlst_base_c__dDlst_base_c_destructor, // parent destructor
    dDlst_gzMenu__draw,
};




PhaseState gzMenu_load(GzMenu* this){
    if (mDoExt_font0 == (JUTFont *)0x0) {
        OSReport("gzMenu: Font not loaded");
        return 0;
    }
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

    return cPhs_COMPLEATE_e;
}
//based on void __thiscall dMenu_Item_c::screenSet(dMenu_Item_c *this)

void gzMenu_create(GzMenu* this){
    this->screen = (J2DScreen*)JKernel__operator_new(sizeof(J2DScreen));
    if (this->screen != 0) {
        TBox2__float__ rect = {
            .mTL.x = 0.0f,
            .mTL.y = 0.0f,
            .mBR.x = 640.0f,
            .mBR.y = 480.0f
        };


        //override virtual draw function from ddst_base_c
        this->base.vtbl = dlst_vtbl;
        this->capture.base.vtbl = dlst_gz_capture_vtbl;
        // Create the parent J2DPane object for our UI elements.
        _GXColor color = {
            .r = 0x00,
            .g = 0x00,
            .b = 0x00,
            .a = 0x00
        };
        J2DPane__J2DPane(&this->screen->parent);
        this->screen->parent.mName = 0x726f6f74;//0x726f6f74 = root
        this->screen->parent.mPosTL = rect.mTL;
        this->screen->parent.mPosBR = rect.mBR;
        this->screen->field_0xcf = 0;
        this->screen->field_0xd0 = color;
        this->screen->mbClipToParent = 0;
        //    this_00->field_0xd0 = (_GXColor)0xffffffff;
        //this_00->mbClipToParent = 0;
        
        // This is sort of a hack because this is a C toolkit. We need to manually set what vtable our
        // UI element uses. Even though mMenuUI is a J2DScreen object, and its parent is a J2DPane,
        // we set the parent to use J2DScreen's vtable since J2DScreen is a child class of J2DPane.
        this->screen->parent.vtbl = &J2DScreen____vt;

        J2DScreen__set(this->screen, GZ_MENU_BLO, this->mMenuResArc);   /*undefined J2DScreen__set(J2DScreen * this, char * param_1, JKRArchive * param_2);*/

        //this->font = mDoExt_getMesgFont();
    }
}

void gzMenu_create2(GzMenu* this){
    gzMenu_create(this);
    TBox2__float__ warpRect = {
        .mTL.x = 0.0f,
        .mTL.y = 0.0f,
        .mBR.x = 0.0f,
        .mBR.y = 0.0f
    };
    //override virtual draw function from ddst_base_c
    this->base.vtbl = dlst_vtbl;

    this->font = mDoExt_getMesgFont();
    /*
    this->warpTextBox = (J2DTextBox*)JKernel__operator_new(sizeof(J2DTextBox));
    JUTResFont* resFont = mDoExt_resfont0;
    J2DTextBox__J2DTextBox(this->warpTextBox,(char*)0,(char*)0);
    J2DTextBox__initiate(this->warpTextBox, resFont, text, 0,0);
    J2DTextBox__setFont(this->warpTextBox,(JUTFont*)this->font);
    */

   //void GzTextBox__create(GzTextBox* this, float xAxisOffset, float yAxisOffset, float width, char* text)
    float startyOffset = 80.0f;
    float yPadding = 40.0f;
    GzTextBox__create(&this->mainTextBoxes[0],62.0f,startyOffset,100.0f,"Warp", true);
    GzTextBox__create(&this->mainTextBoxes[1],62.0f,startyOffset + (1 * yPadding),100.0f,"Cheats", false);
    GzTextBox__create(&this->mainTextBoxes[2],62.0f,startyOffset + (2 * yPadding),100.0f,"Flags", false);
    GzTextBox__create(&this->mainTextBoxes[3],62.0f,startyOffset + (3 * yPadding),100.0f,"Watches", false);
    GzTextBox__create(&this->mainTextBoxes[4],62.0f,startyOffset + (4 * yPadding),100.0f,"Debug", false);
    GzTextBox__create(&this->mainTextBoxes[5],62.0f,startyOffset + (5 * yPadding),100.0f,"Settings", false);


    //this->screen_capture = (dDlst_MENU_CAPTURE_c*)JKernel__operator_new(sizeof(dDlst_MENU_CAPTURE_c));
    //this->screen_capture->vtbl = &dDlst_base_c____vt;
    //dDlst_MENU_CAPTURE_c__draw(&this->screen_capture);
}

bool gzMenu_draw(GzMenu* this){
    /*
    d_meter__dMenu_flagSet(1);
    d_meter__dMenu_setMenuStatus(2);
    d_meter__dMenu_setMenuStatusOld();
    */
    //dDlst_MENU_CAPTURE_c* screen_capture = (dDlst_MENU_CAPTURE_c*)JKernel__operator_new(sizeof(dDlst_MENU_CAPTURE_c));
    //dDlst_MENU_CAPTURE_c__draw(screen_capture);
/*
    dDlst_list_c__set(&g_dComIfG_gameInfo.mDlstList,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpa,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpaEnd,
                    &this->capture);
*/
    d_meter__dMenu_flagSet(1);
    if(d_menu_window__dMs_capture_c == 0){
        //this is a pointer to a screen capture object.
        //set this value to our screen capture
        d_menu_window__dMs_capture_c = &this->capture;          
    }   

    dDlst_list_c__set(&g_dComIfG_gameInfo.mDlstList,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpa,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpaEnd,
                    &gzMenu);

    d_meter__dMenu_flagSet(1);
    d_meter__dMenu_setMenuStatus(2);
    d_meter__dMenu_setMenuStatusOld();
    //dDlst_MENU_CAPTURE_c__dDlst_MENU_CAPTURE_c_destructor(screen_capture);
    return true;
}

//TODO: Finish destroying menu after render. Not bothering right now since rendering still isn't working...
//Reopening menu after closing once will crash
void gzMenu_destroy(GzMenu* this){


    //dDlst_MENU_CAPTURE_c__dDlst_MENU_CAPTURE_c_destructor(this->menu_dDlst.screen_capture);
    J2DScreen__J2DScreen_destructor(this->screen);
}

void _menu_exec(Settings* settings){
    if(gzMenu.mMenuResArc == 0){
        gzMenu.phase = gzMenu_load(&gzMenu);
    }
    else if(gzMenu.phase == cPhs_ERROR_e){
        OSReport("gzMenu: Error loading gzMenu arc!");
    }
    else{
        //if(gzMenu.screen == 0){
        if(gzMenu.screen == 0){
            gzMenu_create2(&gzMenu);
        }
        short currentInput = _input_current_digital();
        short activate_menu_combo = settings->toggle_menu_combo[0] + settings->toggle_menu_combo[1];
        short destroy_menu_combo = B;

        int currentFrame = *FRAME_COUNT_PTR;
        if(gzMenu.toggle_menu + 30 <= currentFrame){ /*Check if enough time has passed since last menu press*/
            if(currentInput == activate_menu_combo && gzMenu.enabled == false){
                gzMenu.enabled = true;
                gzMenu.toggle_menu = currentFrame;    /*button combo will need to wait 30 frames until checked again*/
            }
            else if(currentInput == destroy_menu_combo && gzMenu.enabled == true){
                //gzMenu_destroy(&gzMenu);
                    //Settings these flags will 'unpause' gameplay
                dDlst_MENU_CAPTURE_c__dDlst_MENU_CAPTURE_c_destructor(&gzMenu.capture.screen_capture);
                d_menu_window__dMs_capture_c = 0;
                d_meter__dMenu_flagSet(0);
                d_meter__dMenu_setMenuStatus(1);
                d_meter__dMenu_setMenuStatusOld();
                
                gzMenu.toggle_menu = currentFrame;
                gzMenu.enabled = false;
            }
        }
        if(gzMenu.enabled == true){
            gzMenu_draw(&gzMenu);
        } 
    }
}