#ifndef WARPPANE_C_INCLUDED
#define WARPPANE_C_INCLUDED

#define MAP_FIELD_IDX 0
#define ROOM_FIELD_IDX 1
#define SPAWNID_FIELD_IDX 2
#define LAYER_FIELD_IDX 3
#define HOUR_FIELD_IDX 4
#define WEEK_FIELD_IDX 5

#define SPAWNID_MAX 255
#define LAYER_MAX 8
#define HOUR_MAX 25
#define WEEK_MAX 7

#include "warp_pane.h"
#include "base_pane.c"
#include "textbox/textbox.c"
#include "textbox/text_color_pallete.h"
#include "stage/stage_list.c"
#include "stage/stage.c"
#include "../helpers/JSUPtr_helpers.c" //for JSUPtrList__get_index

static warp_pane_vtbl warp_pane____vt = {
    warp_pane__draw,
    warp_pane__hide,
    warp_pane__update_cursor,
    warp_pane__open,
    warp_pane__close
};

warp_pane* warp_pane__new(warp_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY){
    if(this == 0){
        this = (warp_pane*)JKernel__operator_new(sizeof(warp_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&warp_pane____vt;

    this->parent = parent;
    this->base.pane = pane;
    //base_pane *this, base_pane *relative_pane, float relativeX, float relativeY, char *titleText, text_color_pallete *pallete, JUTResFont *font
    base_pane_set_title(&this->base, this->parent, relativeX, relativeY, "Warp", &TEXT_PALLETE_WHITE, 0);
    
    stage_list__new(&this->warp_list);
    stage_list__loadFromDVD(&this->warp_list);

    byte stage_index;
    byte room_index;
    byte spawn_id;
    byte layer_id;
    byte hour;
    this->stage_index = 0;
    this->room_index = 0;
    this->spawn_id = 0;
    this->layer_id = 0;
    this->hour = (int)MSL_C_PPCEABI_bare_H__floor(g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mCurTime / 15.0);
    this->dayOfWeek = g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mDayOfWeek;
/*    
    GzTextBox stage_label;
    GzTextBox stage_text;
    GzTextBox room_label;
    GzTextBox room_text;
    GzTextBox entrance_label;
    GzTextBox entrance_text;
    */
    float xPadding = 0.0f;
    float yPadding = 30.0f;
    float height = base_pane_height(&this->base);
    float yOffset = height / (WARP_LABEL_COUNT + WARP_FIELD_COUNT);

    float label_font_scale = 1.0;
    float field_font_scale = 0.8;
    
    GzTextBox__new(&this->labels[0], &this->base, xPadding, yPadding + (yOffset * 0), "Map", &TEXT_PALLETE_WHITE, 0, label_font_scale);
    GzTextBox__new(&this->fields[0], &this->base, xPadding, yPadding + (yOffset * 0.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[1], &this->base, xPadding, yPadding + (yOffset * 2), "Room", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[1], &this->base, xPadding, yPadding + (yOffset * 2.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[2], &this->base, xPadding, yPadding + (yOffset * 4), "Entrance", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[2], &this->base, xPadding, yPadding + (yOffset * 4.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[3], &this->base, xPadding, yPadding + (yOffset * 6), "Layer", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[3], &this->base, xPadding, yPadding + (yOffset * 6.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[4], &this->base, xPadding, yPadding + (yOffset * 8), "Hour", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[4], &this->base, xPadding, yPadding + (yOffset * 8.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[5], &this->base, xPadding, yPadding + (yOffset * 10), "Day of Week", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[5], &this->base, xPadding, yPadding + (yOffset * 10.75), "", &TEXT_PALLETE_WHITE_70, 0,field_font_scale);
    return this;
}
void warp_pane__draw(warp_pane *this){
    stage *current_stage = (stage *)JSUPtrList__get_index(&this->warp_list.stages, this->stage_index);
    char *current_room = (char *)JSUPtrList__get_index(&current_stage->rooms, this->room_index);
    //int MSL_C_PPCEABI_bare_H__sprintf(char * __s, char * __format, ...);
    
    char spawn_id_text[3];
    char layer_id_text[2];
    char hour_text[3];
    char dayOfWeek_text[2];
    MSL_C_PPCEABI_bare_H__sprintf(spawn_id_text, "%d",this->spawn_id);
    MSL_C_PPCEABI_bare_H__sprintf(layer_id_text, "%d",this->layer_id);  
    MSL_C_PPCEABI_bare_H__sprintf(hour_text, "%d",this->hour); 
    MSL_C_PPCEABI_bare_H__sprintf(dayOfWeek_text, "%d",this->dayOfWeek); 

    this->fields[MAP_FIELD_IDX].text = current_stage->stage_name;
    this->fields[ROOM_FIELD_IDX].text = current_room;
    this->fields[SPAWNID_FIELD_IDX].text = spawn_id_text;
    this->fields[LAYER_FIELD_IDX].text = layer_id_text;
    this->fields[HOUR_FIELD_IDX].text = hour_text;
    this->fields[WEEK_FIELD_IDX].text = dayOfWeek_text;

    for(int i = 0; i < WARP_LABEL_COUNT; i++){
        if(this->base.cursor_active){
            this->labels[i].pallete = &TEXT_PALLETE_WHITE;
        }
        else{
            this->labels[i].pallete = &TEXT_PALLETE_WHITE_70;
        }
        GzTextBox__draw(&this->labels[i],0);
    }
    for(int i = 0; i < WARP_FIELD_COUNT; i++){
        if(this->base.cursor == i){
            if(this->base.cursor_active){
                this->fields[i].pallete = &TEXT_PALLETE_WHITE;
            }
            else{
                this->fields[i].pallete = &TEXT_PALLETE_WHITE_70;
            }
        }
        else{
            this->fields[i].pallete = &TEXT_PALLETE_WHITE_70;
        }

        GzTextBox__draw(&this->fields[i],0);
    }
    this->base.pane->parent.mbDraw = true;
}
void warp_pane__hide(warp_pane *this){
    this->base.pane->parent.mbDraw = false;
}

void warp_pane__update_cursor(warp_pane *this){
    if(DIGITAL_INPUTS[D_PAD_UP].pressed){
        this->base.cursor = this->base.cursor - 1;
        if(this->base.cursor < 0){
            this->base.cursor = WARP_FIELD_COUNT - 1; //screen wrap cursor
        }
    }
    else if(DIGITAL_INPUTS[D_PAD_DOWN].pressed){
        this->base.cursor = this->base.cursor + 1;
        if(this->base.cursor >= WARP_FIELD_COUNT){
            this->base.cursor = 0;
        }
    }
    else if(DIGITAL_INPUTS[D_PAD_LEFT].pressed){
        this->parent->cursor_active = true;
        this->base.cursor_active = false;
    }
    warp_pane__update_fields(this);
}

void warp_pane__open(warp_pane *this){}
void warp_pane__close(warp_pane *this){}

void warp_pane__warp(warp_pane *this){
    char *pStageName = this->fields[MAP_FIELD_IDX].text;

    
    byte roomIdx = (byte)atoi(this->fields[ROOM_FIELD_IDX].text);
    
    byte layerNo = (byte)this->layer_id;//atoi(this->fields[LAYER_FIELD_IDX].text);
    byte spawnId = (short)this->spawn_id;

    g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mDayOfWeek = (short)this->dayOfWeek;
    g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mCurTime = this->hour * 15.0f;
    //float mCurrTime = this->hour * 15.0f;
    OSReport(MSL_C_PPCEABI_bare_H__printf("warp_pane__warp: pStageName = %s | roomIdx = %d | layerNo = %d | spawnId = %d\n",pStageName, roomIdx, layerNo, spawnId));

    //void dComIfGp_setNextStage(char * pStageName, short startCode, byte roomIdx, byte layerNo, float param_5, uint mode, int param_7, byte wipeType);
    dComIfGp_setNextStage(pStageName, spawnId, roomIdx, layerNo, 0.0,0,1,0);
}
void warp_pane__update_fields(warp_pane *this){
    if(DIGITAL_INPUTS[START].pressed){
        warp_pane__warp(this);
        this->parent->vptr->hide(this->parent);
        return;
    }
    bool xPressed = DIGITAL_INPUTS[X].pressed || DIGITAL_INPUTS[X].long_held;
    bool yPressed = DIGITAL_INPUTS[Y].pressed || DIGITAL_INPUTS[Y].long_held;
    bool zPressed = DIGITAL_INPUTS[Z].pressed;
    if(this->base.cursor == MAP_FIELD_IDX){
        if(xPressed){
            this->stage_index = this->stage_index + 1;
        }
        else if(yPressed){
            this->stage_index = this->stage_index - 1;
        }
        else if(zPressed){
            this->stage_index = 0;
        }

    }
    else if(this->base.cursor == ROOM_FIELD_IDX){
        if(xPressed){
            this->room_index = this->room_index + 1;
        }
        else if(yPressed){
            this->room_index = this->room_index - 1;
        }
        else if(zPressed){
            this->room_index = 0;
        }
    }
    else if(this->base.cursor == SPAWNID_FIELD_IDX){
        if(xPressed){
            this->spawn_id = this->spawn_id + 1;
        }
        else if(yPressed){
            this->spawn_id = this->spawn_id - 1;
        }
        else if(zPressed){
            this->spawn_id = 0;
        }
    }
    else if(this->base.cursor == LAYER_FIELD_IDX){
        if(xPressed){
            this->layer_id = this->layer_id + 1;
        }
        else if(yPressed){
            this->layer_id = this->layer_id - 1;
        }
        else if(zPressed){
            this->layer_id = 0;
        }
    }
    else if(this->base.cursor == HOUR_FIELD_IDX){
        if(xPressed){
            this->hour = this->hour + 1;
        }
        else if(yPressed){
            this->hour = this->hour - 1;
        }
        else if(zPressed){
            this->hour = 0;
        }
    }
    else if(this->base.cursor == WEEK_FIELD_IDX){
        if(xPressed){
            this->dayOfWeek = this->dayOfWeek + 1;
        }
        else if(yPressed){
            this->dayOfWeek = this->dayOfWeek - 1;
        }
        else if(zPressed){
            this->dayOfWeek = 0;
        }
    }

    if(this->stage_index < 0){
        this->stage_index = this->warp_list.stages.mCount - 2;
    }
    else if(this->stage_index >= this->warp_list.stages.mCount - 1){
        this->stage_index = 0;
    }
    stage *current_stage = (stage *)JSUPtrList__get_index(&this->warp_list.stages, this->stage_index);
    if(this->room_index < 0){
        this->room_index = current_stage->rooms.mCount - 1;
    }
    else if(this->room_index >= current_stage->rooms.mCount){
        this->room_index = 0;
    }

    if(this->spawn_id < 0){
        this->spawn_id = SPAWNID_MAX - 1;
    }
    else if(this->spawn_id >= SPAWNID_MAX){
        this->spawn_id = 0;
    }

    if(this->layer_id < 0){
        this->layer_id = LAYER_MAX - 1;
    }
    else if(this->layer_id >= LAYER_MAX){
        this->layer_id = 0;
    }

    if(this->hour < 0){
        this->hour = HOUR_MAX - 1;
    }
    else if(this->hour >= HOUR_MAX){
        this->hour = 0;
    }

    if(this->dayOfWeek < 0){
        this->dayOfWeek = WEEK_MAX - 1;
    }
    else if(this->dayOfWeek >= WEEK_MAX){
        this->dayOfWeek = 0;
    }

}
#endif