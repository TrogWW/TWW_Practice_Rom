#ifndef WARPPANE_C_INCLUDED
#define WARPPANE_C_INCLUDED

//#define EVNT_TXT 0x45564e54
#define AREA_FIELD_IDX 0
#define MAP_FIELD_IDX 1
#define ROOM_FIELD_IDX 2
#define SPAWNID_FIELD_IDX 3
#define LAYER_FIELD_IDX 4
#define HOUR_FIELD_IDX 5
#define WEEK_FIELD_IDX 6

// #define SPAWNID_MAX 255
#define LAYER_MAX 13
#define HOUR_MAX 25
#define WEEK_MAX 7

#include "warp_pane.h"
#include "base_pane.c"
#include "textbox/textbox.c"
#include "textbox/text_color_pallete.h"
#include "stage/area_list.c"
#include "stage/stage.c"
#include "../helpers/JSUPtr_helpers.c" //for JSUPtrList__get_index

static warp_pane_vtbl warp_pane____vt = {
    warp_pane__draw,
    warp_pane__hide,
    warp_pane__update_cursor,
    warp_pane__open,
    warp_pane__close
};
warp_pane__set_stage_data(warp_pane *this, void *data){ //initialize data after archive is loaded
    this->warp_list = (area_list*)data;
    area_list__new(this->warp_list, (int)data);
}
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
    

    //stage_list__loadFromDVD(&this->warp_list);

    byte stage_index;
    byte room_index;
    byte spawn_id;
    byte layer_id;
    byte hour;
    this->area_index = 0;
    this->stage_index = 0;
    this->room_index = 0;
    this->spawn_id = 0;
    this->layer_id = 0;
    this->hour = (int)MSL_C_PPCEABI_bare_H__floor(g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mCurTime / 15.0);
    this->dayOfWeek = g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mDayOfWeek;
    this->event_window_enabled = false;
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
    
    GzTextBox__new(&this->labels[0], &this->base, xPadding, yPadding + (yOffset * 0), "Area", &TEXT_PALLETE_WHITE, 0, label_font_scale);
    GzTextBox__new(&this->fields[0], &this->base, xPadding, yPadding + (yOffset * 0.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[1], &this->base, xPadding, yPadding + (yOffset * 2), "Map", &TEXT_PALLETE_WHITE, 0, label_font_scale);
    GzTextBox__new(&this->fields[1], &this->base, xPadding, yPadding + (yOffset * 2.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[2], &this->base, xPadding, yPadding + (yOffset * 4), "Room", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[2], &this->base, xPadding, yPadding + (yOffset * 4.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[3], &this->base, xPadding, yPadding + (yOffset * 6), "Entrance", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[3], &this->base, xPadding, yPadding + (yOffset * 6.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[4], &this->base, xPadding, yPadding + (yOffset * 8), "Layer", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[4], &this->base, xPadding, yPadding + (yOffset * 8.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[5], &this->base, xPadding, yPadding + (yOffset * 10), "Hour", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[5], &this->base, xPadding, yPadding + (yOffset * 10.75), "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    GzTextBox__new(&this->labels[6], &this->base, xPadding, yPadding + (yOffset * 12), "Day of Week", &TEXT_PALLETE_WHITE, 0,label_font_scale);
    GzTextBox__new(&this->fields[6], &this->base, xPadding, yPadding + (yOffset * 12.75), "", &TEXT_PALLETE_WHITE_70, 0,field_font_scale);



    GzTextBox__new(&this->event_label, &this->base, 210.0f, 60.0f, "Events", &TEXT_PALLETE_WHITE, 0, label_font_scale);
    GzTextBox__new(&this->event_field, &this->base, 210.0f, 90.0f, "", &TEXT_PALLETE_WHITE_70, 0, field_font_scale);

    return this;
}
event *warp_pane__current_event(warp_pane *this){
    stage *current_stage = warp_pane__current_stage(this);
    if(current_stage != 0 && current_stage->event_count > 0){
        return &current_stage->events[this->event_index];
    }
    else{
        return 0;
    }
}
room *warp_pane__current_room(warp_pane *this){
    stage *current_stage = warp_pane__current_stage(this);
    if(current_stage != 0 && current_stage->room_count > 0){
        return &current_stage->rooms[this->room_index];
    }
    else{
        return 0;
    }
}
stage *warp_pane__current_stage(warp_pane *this){
    area *current_area = warp_pane__current_area(this);
    if(current_area != 0 && current_area->stage_count > 0){
        return &current_area->stages[this->stage_index];
    }
    else{
        return 0;
    }
}
area *warp_pane__current_area(warp_pane *this){
    return &this->warp_list->areas[this->area_index];
}
void warp_pane__draw(warp_pane *this){
    area *current_area = warp_pane__current_area(this);
    stage *current_stage = warp_pane__current_stage(this);
    room *current_room = warp_pane__current_room(this);
    event *current_event = warp_pane__current_event(this);

    char spawn_id_text[3];
    char layer_id_text[2];
    char hour_text[3];
    char dayOfWeek_text[2];
    char room_index_text[3];

    char event_title[20];
    if(this->event_window_enabled == false){
        int room_index = 0;
        int spawn_index = 0;
        if(current_room != 0){
            room_index = current_room->index;
            spawn_index = current_room->spawn_ids[this->spawn_id];
        }

        MSL_C_PPCEABI_bare_H__sprintf(room_index_text, "%d",room_index);
        MSL_C_PPCEABI_bare_H__sprintf(spawn_id_text, "%d",spawn_index);
        MSL_C_PPCEABI_bare_H__sprintf(layer_id_text, "%d",this->layer_id);  

    }
    else{
        MSL_C_PPCEABI_bare_H__sprintf(room_index_text, "%d",current_event->room_index);
        MSL_C_PPCEABI_bare_H__sprintf(spawn_id_text, "%d",current_event->spawn_id);
        MSL_C_PPCEABI_bare_H__sprintf(layer_id_text, "%d",current_event->layer_ids[0]);  //TODO
    }
    MSL_C_PPCEABI_bare_H__sprintf(event_title, "Events (%d)",current_stage->event_count);
    MSL_C_PPCEABI_bare_H__sprintf(hour_text, "%d",this->hour); 
    MSL_C_PPCEABI_bare_H__sprintf(dayOfWeek_text, "%d",this->dayOfWeek); 
    this->fields[AREA_FIELD_IDX].text = current_area->area_name;
    if(current_stage->display_name != 0){
        this->fields[MAP_FIELD_IDX].text = current_stage->display_name;
    }
    else{
        this->fields[MAP_FIELD_IDX].text = current_stage->stage_name;
    }


    if(current_room != 0){
        this->fields[ROOM_FIELD_IDX].text = room_index_text;
        this->fields[SPAWNID_FIELD_IDX].text = spawn_id_text;
        this->fields[LAYER_FIELD_IDX].text = layer_id_text;
    }
    else{
        this->fields[ROOM_FIELD_IDX].text = "";
        this->fields[SPAWNID_FIELD_IDX].text =  "";
        this->fields[LAYER_FIELD_IDX].text =  "";
    }


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
    this->event_label.pallete = &TEXT_PALLETE_WHITE;
    this->event_label.text = event_title;
    if(this->event_window_enabled){
        this->event_field.text = current_event->event_name;
        this->event_field.pallete = &TEXT_PALLETE_WHITE;
    }
    else{
        this->event_field.text = "N/A";
        this->event_field.pallete = &TEXT_PALLETE_WHITE_70;
    }

    GzTextBox__draw(&this->event_label,0);
    GzTextBox__draw(&this->event_field,0);
    this->base.pane->parent.mbDraw = true;
}
void warp_pane__hide(warp_pane *this){
    this->base.pane->parent.mbDraw = false;
}

void warp_pane__update_cursor(warp_pane *this){
    if(this->event_window_enabled){
        warp_pane__update_event_fields(this);
        if(DIGITAL_INPUTS[D_PAD_LEFT].pressed){
            this->event_window_enabled = false;
        }
    }
    else{
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


        stage *current_stage = warp_pane__current_stage(this);
        if(DIGITAL_INPUTS[D_PAD_RIGHT].pressed && current_stage->event_count > 0){
            this->event_window_enabled = true;
        }
        else{
            this->event_window_enabled = false;
            this->event_index = 0;
        }
    }
}

void warp_pane__open(warp_pane *this){}
void warp_pane__close(warp_pane *this){
    this->base.pane->parent.mbDraw = false;
}

void warp_pane__warp(warp_pane *this){
    stage *current_stage = warp_pane__current_stage(this);
    room *current_room = warp_pane__current_room(this);
    event *current_event = warp_pane__current_event(this);
    char *pStageName = current_stage->stage_name;
    byte roomIdx = 0;
    byte spawnId = 0;
    byte layerNo = 0;
    if(this->event_window_enabled == false){
        roomIdx = (byte)current_room->index;
        spawnId= (byte)current_room->spawn_ids[this->spawn_id];
        layerNo = (byte)this->layer_id;
    }
    else{
        roomIdx = (byte)current_event->room_index;
        spawnId = (byte)current_event->spawn_id;
        layerNo = (byte)current_event->layer_ids[0]; //todo
    }


    g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mDayOfWeek = (short)this->dayOfWeek;
    g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mCurTime = this->hour * 15.0f;
    //float mCurrTime = this->hour * 15.0f;
    OSReport(MSL_C_PPCEABI_bare_H__printf("warp_pane__warp: pStageName = %s | roomIdx = %d | layerNo = %d | spawnId = %d\n",pStageName, roomIdx, layerNo, spawnId));

    //void dComIfGp_setNextStage(char * pStageName, short startCode, byte roomIdx, byte layerNo, float param_5, uint mode, int param_7, byte wipeType);
    dComIfGp_setNextStage(pStageName, spawnId, roomIdx, layerNo, g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusB.mCurTime,0,1,0);
}
void warp_pane__update_event_fields(warp_pane *this){
    if(DIGITAL_INPUTS[START].pressed){
        warp_pane__warp(this);
        this->parent->vptr->hide(this->parent);
        return;
    }

    bool xPressed = DIGITAL_INPUTS[X].pressed || DIGITAL_INPUTS[X].long_held;
    bool yPressed = DIGITAL_INPUTS[Y].pressed || DIGITAL_INPUTS[Y].long_held;
    bool zPressed = DIGITAL_INPUTS[Z].pressed;

    stage *current_stage = warp_pane__current_stage(this);

    if(xPressed){
        this->event_index = this->event_index + 1;
    }
    else if(yPressed){
        this->event_index = this->event_index - 1;
    }
    else if(zPressed){
        this->event_index = 0;
    }
    if(this->event_index < 0){
        this->event_index = current_stage->event_count - 1;
    }
    else if(this->event_index >= current_stage->event_count){
        this->event_index = 0;
    }
    //event *current_event = &current_stage->events[this->event_index];
    //OSReport(MSL_C_PPCEABI_bare_H__printf("warp_pane__update_event_fields: this->event_index = %d | current_stage->stage_name = %s | current_stage->event_count = %d | current_event->event_name = %s\n",
    //this->event_index, current_stage->stage_name, current_stage->event_count, current_event->event_name));

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

    
    if(this->base.cursor == AREA_FIELD_IDX){
        if(xPressed){
            this->area_index = this->area_index + 1;
        }
        else if(yPressed){
            this->area_index = this->area_index - 1;
        }
        else if(zPressed){
            this->area_index = 0;
        }

    }
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
    if(this->area_index < 0){
        this->area_index = this->warp_list->area_count - 1;
    }
    else if(this->area_index >= this->warp_list->area_count){
        this->area_index = 0;
    }
    if(this->stage_index < 0){
        this->stage_index = this->warp_list->areas[this->area_index].stage_count - 1;
    }
    else if(this->stage_index >= this->warp_list->areas[this->area_index].stage_count){
        this->stage_index = 0;
    }
    stage *current_stage = warp_pane__current_stage(this);
    if(current_stage != 0){
        if(this->room_index < 0){
            this->room_index = current_stage->room_count - 1;
        }
        else if(this->room_index >= current_stage->room_count){
            this->room_index = 0;
        }
    }
    else{
        this->room_index = 0;
    }

    room *current_room = warp_pane__current_room(this);
    if(current_room != 0){
        if(this->spawn_id < 0){
            this->spawn_id = current_room->spawn_count - 1;
        }
        else if(this->spawn_id >= current_room->spawn_count){
            this->spawn_id = 0;
        }
    }
    else{
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