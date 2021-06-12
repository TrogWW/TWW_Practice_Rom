#ifndef WATCHES_DISPLAY_C_INCLUDED
#define WATCHES_DISPLAY_C_INCLUDED

#define INFO_TEXT 0x494e464f
#define RMID_TEXT 0x524d4944

#include "watches_display.h"

watches_display_pane WATCHES_DISPLAY_UI;
static watches_display_pane_vtbl watches_display_pane____vt = {
    watches_display_pane__draw,
    watches_display_pane__hide,
    watches_display_pane__update_cursor,
    watches_display_pane__open,
    watches_display_pane__close
};
/*
struct watches_display_pane {
    base_pane base;
    JSUPtrList watches_list;    //linked list of J2DTextboxes displaying watches
};
*/
watches_display_pane *watches_display_pane___new(watches_display_pane *this, J2DScreen *screen){ 
    if(this == 0){
        this = (watches_display_pane*)JKernel__operator_new(sizeof(watches_display_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&watches_display_pane____vt;  //inherit base_pane class

    this->screen = screen;
    this->info_window = (J2DWindow*)J2DScreen__search(screen, INFO_TEXT);

    J2DWindow* watches_window = (J2DWindow*)J2DScreen__search(screen, RMID_TEXT);
    this->base.pane = watches_window;
    //OSReport(MSL_C_PPCEABI_bare_H__printf("watches_display_pane___new: watches_window = %X\n", watches_window));


    menu_ddlst___new(&this->watches_display_ddlst_item, this);
    //OSReport(MSL_C_PPCEABI_bare_H__printf("watches_display_pane___new: FINISHED\n"));
    return this;
}
void watches_display_pane__update_dDlst(watches_display_pane *this){
    dDlst_list_c__set(&g_dComIfG_gameInfo.mDlstList,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpa,
                    &g_dComIfG_gameInfo.mDlstList.mp2DOpaEnd,
                    &this->watches_display_ddlst_item);
}
void watches_display_pane__add_watch(watches_display_pane *this, watch_item *watch){
   // OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_code_list__add: ADDING code->code_name %s | code->code_name %X | code->code_arr_count %d | code_list %X\n", code->code_name, code->code_name, code->code_arr_count, &this->code_list));
    JSUPtrLink *new_link = (JSUPtrLink*)JKernel__operator_new(sizeof(JSUPtrLink));

    watches_display_textbox *newTextBox = (watches_display_textbox*)JKernel__operator_new(sizeof(watches_display_textbox));
    newTextBox->textbox = (GzTextBox *)JKernel__operator_new(sizeof(GzTextBox));
    newTextBox->watch = watch;

    GzTextBox__new(newTextBox->textbox, &this->base, 10.0f, 20.0 + (15.0 * this->watches_list.mCount), "", &TEXT_PALLETE_WHITE, 0, 0.5);
    JSUPtrLink__JSUPtrLink(new_link, newTextBox);
    JSUPtrList__append(&this->watches_list, new_link);
}

void watches_display_pane__create_list(watches_display_pane *this, watch_category_list *watches_list){
    if(this->watches_list.mCount > 0){
        JSUPtrList__JSUPtrList_destructor(&this->watches_list);    //reset watch list (probably need to deconstruct gztextbox)
    }
    JSUPtrList__JSUPtrList(&this->watches_list, true);
    
    for(int i = 0; i < watches_list->watch_category_count; i++){
        watch_category *curr_category = &watches_list->watch_categories[i];
       // OSReport(MSL_C_PPCEABI_bare_H__printf("wiird_code_list__create_category_list: curr_category->category_name = %s | curr_category = %X\n", curr_category->category, curr_category));
        for(int j = 0; j < curr_category->watch_count; j++){
            watch_item *curr_watch = &curr_category->watches[j];
            if(curr_watch->is_active == 1){
                watches_display_pane__add_watch(this, curr_watch);
            }
        }
    }
   // OSReport(MSL_C_PPCEABI_bare_H__printf("watches_display_pane__create_list: AFTER this->watches_list.mCount = %d\n", this->watches_list.mCount));
}
void watches_display_pane__draw(watches_display_pane *this){   
    if(this->watches_list.mCount == 0){
        this->base.pane->parent.mbDraw = false;
        return;
    }


    J2DGrafContext* pCtx = (J2DGrafContext*)g_dComIfG_gameInfo.mp2DOrthoGraph;
    J2DGrafContext__setPort((J2DGrafContext*)g_dComIfG_gameInfo.mp2DOrthoGraph);


   //J2DScreen__draw(J2DScreen * this, float x, float y, J2DGrafContext * pCtx);
    J2DScreen__draw(this->screen,0.0,0.0,pCtx);

    this->base.pane->parent.mbDraw = true;
    this->info_window->parent.mbDraw = true;

    JSUPtrLink *current_link = this->watches_list.mpHead;
    while(current_link != 0 && current_link->mpData != 0){
        watches_display_textbox *curr_textbox = (watches_display_textbox *)current_link->mpData;
        char display_value[40];
        char watch_display[80];
        watch_item__get_display_value(curr_textbox->watch, display_value);
        
        MSL_C_PPCEABI_bare_H__sprintf(watch_display,"%s: %s", curr_textbox->watch->display_name, display_value);
        curr_textbox->textbox->pallete = &TEXT_PALLETE_WHITE;
        curr_textbox->textbox->text = watch_display;
        //OSReport(MSL_C_PPCEABI_bare_H__printf("watches_display_pane__draw: curr_textbox->watch->display_name = %s | display_value = %s\n", curr_textbox->watch->display_name, display_value));

        GzTextBox__draw(curr_textbox->textbox, 2);
        current_link = current_link->mpNext;
    }
}
void watches_display_pane__hide(watches_display_pane *this){ }
void watches_display_pane__update_cursor(watches_display_pane *this){ }
void watches_display_pane__open(watches_display_pane *this){ }
void watches_display_pane__close(watches_display_pane *this){
    this->base.pane->parent.mbDraw = false;
    this->info_window->parent.mbDraw = false;
}
#endif