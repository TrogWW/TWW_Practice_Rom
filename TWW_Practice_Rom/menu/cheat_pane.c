#ifndef CHEAT_PANE_C_INCLUDED
#define CHEAT_PANE_C_INCLUDED

#include "cheat_pane.h"
#include "cheat/wiird_category_list.c"
#include "textbox/textbox.c"
#include "textbox/text_color_pallete.h"
#include "../tools/wiird_loader_context.c"

static cheat_pane_vtbl cheat_pane____vt = {
    cheat_pane__draw,
    cheat_pane__hide,
    cheat_pane__update_cursor,
    cheat_pane__open,
    cheat_pane__close
};

//initialize data after archive is loaded
cheat_pane__set_cheat_data(cheat_pane *this, void *data){   
    this->category_list = (wiird_category_list*)data;
    wiird_category_list__new(this->category_list, (int)data);
    OSReport(MSL_C_PPCEABI_bare_H__printf("cheat_pane__set_cheat_data: this->wiird_categories = %X\n",&this->category_list));
}

cheat_pane* cheat_pane__new(cheat_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY){
    if(this == 0){
        this = (cheat_pane*)JKernel__operator_new(sizeof(cheat_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&cheat_pane____vt;  //inherit base_pane class

    this->parent = parent;
    this->base.pane = pane;

    base_pane_set_title(&this->base, this->parent, relativeX, relativeY, "Cheats", &TEXT_PALLETE_WHITE, 0);

    float xPadding = 0.0f;
    float yPadding = 30.0f;
    float height = base_pane_height(&this->base);
    float yOffset = height / CODES_LIMIT;
    float field_font_scale = 0.8;

    for(int i = 0; i < CODES_LIMIT; i++){
        GzTextBox__new(&this->cheats[i], &this->base, 0, yPadding + (yOffset * i), "", &TEXT_PALLETE_WHITE, 0, field_font_scale);
    }
    //float categories_font_scale = 0.6;
    yPadding = 60.0f;
    yOffset = 20.0f;
    for(int i = 0; i < CATEGORIES_LIMIT; i++){
        GzTextBox__new(&this->categories[i], &this->base, 210.0f, yPadding + (yOffset * i), "", &TEXT_PALLETE_WHITE, 0, field_font_scale);
    }
    return this;
}
void cheat_pane__draw(cheat_pane *this){
    wiird_category *active_category = &this->category_list->categories[this->curr_category_index];
    

    for (int i = 0; i < active_category->code_count; i++)
    {
        wiird_code *curr_code = &active_category->code_list[i];
        //OSReport(MSL_C_PPCEABI_bare_H__printf("cheat_pane__draw: curr_code->code_name = %s | hex = %X\n",active_category->code_name, active_category->code_name));
        if(this->base.cursor == i){
            if(this->category_window_enabled){
                if(curr_code->is_active == 1){
                    this->cheats[i].pallete = &TEXT_PALLETE_CODE_ACTIVE_WHITE_90;
                }
                else{
                    this->cheats[i].pallete = &TEXT_PALLETE_WHITE_90;
                }
            }
            else{
                if(curr_code->is_active == 1){
                    this->cheats[i].pallete = &TEXT_PALLETE_CODE_ACTIVE_WHITE;
                }
                else{
                    this->cheats[i].pallete = &TEXT_PALLETE_WHITE;
                }
            }            
        }
        else{
            if(curr_code->is_active == 1){
                this->cheats[i].pallete = &TEXT_PALLETE_CODE_ACTIVE_WHITE_70;
            }
            else{
                this->cheats[i].pallete = &TEXT_PALLETE_WHITE_70;
            }
        }
        this->cheats[i].text = curr_code->code_name;
        GzTextBox__draw(&this->cheats[i], 0);
    }
    for(int i = 0; i < this->category_list->category_count; i++){
        wiird_category *curr_category = &this->category_list->categories[i];
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
        this->categories[i].text = curr_category->category_name;

        //OSReport(MSL_C_PPCEABI_bare_H__printf("cheat_pane__draw: i = %d | curr_category = %X | curr_category->category_name = %s\n", i, curr_category, curr_category->category_name));

        GzTextBox__draw(&this->categories[i], 0);
    }
    this->base.pane->parent.mbDraw = true;
}
void cheat_pane__hide(cheat_pane *this){
    this->base.pane->parent.mbDraw = false;
}
void cheat_pane__update_cursor(cheat_pane *this){
    wiird_category *active_category = &this->category_list->categories[this->curr_category_index];
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
                wiird_code *curr_code = &active_category->code_list[this->base.cursor];
                if(curr_code->is_active == 1){
                    curr_code->is_active = 0;
                }
                else{
                    curr_code->is_active = 1;
                }
            }
            //check for cursor wrap
            if(this->base.cursor < 0){
                this->base.cursor = active_category->code_count - 1;
            }
            else if(this->base.cursor >= active_category->code_count){
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
                this->curr_category_index = this->category_list->category_count - 1;
            }
            else if(this->curr_category_index >= this->category_list->category_count){
                this->base.cursor = 0;
            }
        }
    }
}
void cheat_pane__open(cheat_pane *this){}
void cheat_pane__close(cheat_pane *this){
    OSReport(MSL_C_PPCEABI_bare_H__printf("cheat_pane__close: this->category_list->category_count = %d | this->category_list = %X\n", this->category_list->category_count, this->category_list));
    wiird_code_list__create_category_list(&code_list, this->category_list);
    OSReport(MSL_C_PPCEABI_bare_H__printf("cheat_pane__close: CLOSED\n"));
}

#endif