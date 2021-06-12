#ifndef WATCHES_PANE_C_INCLUDED
#define WATCHES_PANE_C_INCLUDED

#include "watches_pane.h"
#include "watch/watch_category_list.c"
#include "textbox/textbox.c"
#include "textbox/text_color_pallete.h"
#include "../tools/wiird_loader_context.c"
#include "display/watches_display.c" //for WATCHES_DISPLAY_UI

static watches_pane_vtbl watches_pane____vt = {
    watches_pane__draw,
    watches_pane__hide,
    watches_pane__update_cursor,
    watches_pane__open,
    watches_pane__close
};


watches_pane__set_data(watches_pane *this, void *data){
    this->category_list = (watch_category_list *)data;
    watch_category_list__new(this->category_list, (int)data);
}
watches_pane* watches_pane__new(watches_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY){
    if(this == 0){
        this = (watches_pane*)JKernel__operator_new(sizeof(watches_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&watches_pane____vt;  //inherit base_pane class

    this->parent = parent;
    this->base.pane = pane;

    base_pane_set_title(&this->base, this->parent, relativeX, relativeY, "Watches", &TEXT_PALLETE_WHITE, 0);

    float xPadding = 10.0f;
    float yPadding = 30.0f;
    float height = base_pane_height(&this->base);
    float yOffset = height / WATCHES_LIMIT;
    float field_font_scale = 0.6;
    float category_font_scale = 0.8;

    for(int i = 0; i < WATCHES_LIMIT; i++){
        GzTextBox__new(&this->watches[i], &this->base, xPadding, yPadding + (yOffset * i), "", &TEXT_PALLETE_WHITE, 0, field_font_scale);
    }
    //float categories_font_scale = 0.6;
    yPadding = 60.0f;
    yOffset = 20.0f;
    for(int i = 0; i < WATCH_CATEGORIES_LIMIT; i++){
        GzTextBox__new(&this->categories[i], &this->base, 210.0f, yPadding + (yOffset * i), "", &TEXT_PALLETE_WHITE, 0, category_font_scale);
    }
    return this;
}
void watches_pane__draw(watches_pane *this){
    watch_category *active_category = &this->category_list->watch_categories[this->curr_category_index];
    for (int i = 0; i < active_category->watch_count; i++)
    {
        watch_item *curr_watch = &active_category->watches[i];
        //OSReport(MSL_C_PPCEABI_bare_H__printf("cheat_pane__draw: curr_code->code_name = %s | hex = %X\n",active_category->code_name, active_category->code_name));
        if(this->base.cursor == i){
            if(this->category_window_enabled){
                if(curr_watch->is_active == 1){
                    this->watches[i].pallete = &TEXT_PALLETE_CODE_ACTIVE_WHITE_90;
                }
                else{
                    this->watches[i].pallete = &TEXT_PALLETE_WHITE_90;
                }
            }
            else{
                if(curr_watch->is_active == 1){
                    this->watches[i].pallete = &TEXT_PALLETE_CODE_ACTIVE_WHITE;
                }
                else{
                    this->watches[i].pallete = &TEXT_PALLETE_WHITE;
                }
            }            
        }
        else{
            if(curr_watch->is_active == 1){
                this->watches[i].pallete = &TEXT_PALLETE_CODE_ACTIVE_WHITE_70;
            }
            else{
                this->watches[i].pallete = &TEXT_PALLETE_WHITE_70;
            }
        }
        char display_value[40];
        char watch_display[80];
        watch_item__get_display_value(curr_watch, display_value);
        //OSReport(MSL_C_PPCEABI_bare_H__printf("watches_pane__draw: curr_watch->display_name = %s | display_value = %s\n", curr_watch->display_name, display_value));
        MSL_C_PPCEABI_bare_H__sprintf(watch_display,"%s: %s", curr_watch->display_name, display_value);
        this->watches[i].text = watch_display;
        GzTextBox__draw(&this->watches[i], 2);
    }
    for(int i = 0; i < this->category_list->watch_category_count; i++){
        watch_category *curr_category = &this->category_list->watch_categories[i];
        if(this->curr_category_index == i){
            if(this->category_window_enabled){
                this->categories[i].pallete = &TEXT_PALLETE_WHITE;
            }
            else{
                this->categories[i].pallete = &TEXT_PALLETE_WHITE_90;
            }
        }
        else{
            this->categories[i].pallete = &TEXT_PALLETE_WHITE_70;
        }
        this->categories[i].text = curr_category->category;

        //OSReport(MSL_C_PPCEABI_bare_H__printf("cheat_pane__draw: i = %d | curr_category = %X | curr_category->category_name = %s\n", i, curr_category, curr_category->category_name));

        GzTextBox__draw(&this->categories[i], 0);
    }
    this->base.pane->parent.mbDraw = true;
}
void watches_pane__hide(watches_pane *this){
    this->base.pane->parent.mbDraw = false;
}
void watches_pane__update_cursor(watches_pane *this){
    watch_category *active_category = &this->category_list->watch_categories[this->curr_category_index];
    if(this->category_window_enabled == false){
        if(DIGITAL_INPUTS[D_PAD_RIGHT].pressed){
            this->category_window_enabled = true;
            return;
        }
        else if(DIGITAL_INPUTS[D_PAD_LEFT].pressed){
            this->parent->cursor_active = true;
            this->base.cursor_active = false;
            return;
        }
        else{
            if(DIGITAL_INPUTS[D_PAD_UP].pressed){
                this->base.cursor = this->base.cursor - 1;
            }
            else if(DIGITAL_INPUTS[D_PAD_DOWN].pressed){
                this->base.cursor = this->base.cursor + 1;
            }
            if(DIGITAL_INPUTS[A].pressed){
                watch_item *curr_watch = &active_category->watches[this->base.cursor];
                if(curr_watch->is_active == 1){
                    curr_watch->is_active = 0;
                }
                else{
                    curr_watch->is_active = 1;
                }
            }
            //check for cursor wrap
            if(this->base.cursor < 0){
                this->base.cursor = active_category->watch_count - 1;
            }
            else if(this->base.cursor >= active_category->watch_count){
                this->base.cursor = 0;
            }
        }
    }
    else{
        if(DIGITAL_INPUTS[D_PAD_LEFT].pressed){
            this->category_window_enabled = false;
            return;
        }
        else{
             if(DIGITAL_INPUTS[D_PAD_UP].pressed){
                this->curr_category_index = this->curr_category_index - 1;
            }
            else if(DIGITAL_INPUTS[D_PAD_DOWN].pressed){
                this->curr_category_index = this->curr_category_index + 1;
            }
            //check for cursor wrap
            if(this->curr_category_index < 0){
                this->curr_category_index = this->category_list->watch_category_count - 1;
            }
            else if(this->curr_category_index >= this->category_list->watch_category_count){
                this->base.cursor = 0;
            }
        }
    }

}
void watches_pane__open(watches_pane *this){}
void watches_pane__close(watches_pane *this){
    watches_display_pane__create_list(&WATCHES_DISPLAY_UI, this->category_list);
    this->base.pane->parent.mbDraw = false;
}


#endif