#ifndef INVENTORY_SLOT_C_INCLUDED
#define INVENTORY_SLOT_C_INCLUDED

#define IMAGE_WIDTH 40.0f
#define IMAGE_HEIGHT 40.0f
#define INV_XPADDING 20.0f
#define INV_YPADDING 100.0f

#include "inventory_slot.h"
#include "inventory_base.c"
#include "../base_pane.c"
#include "../textbox/text_color_pallete.h"
#include "../inventory_pane.h"

static inventory_slot_vtbl inventory_slot____vt = {
    inventory_slot__init,
    inventory_slot__update_data,
    inventory_slot__update_inventory,
    inventory_base__draw,   //do not override base execute
    inventory_base__execute //do not override base execute
};
#pragma region inventory_defines
int inventory_slot0[2] = { 0, dItem_data__ItemNo__Telescope };
int inventory_slot1[2] = { 0, dItem_data__ItemNo__normal_sail };
int inventory_slot2[2] = { 0, dItem_data__ItemNo__WindWaker };
int inventory_slot3[2] = { 0, dItem_data__ItemNo__GrapplingHook };
int inventory_slot4[2] = { 0, dItem_data__ItemNo__SpoilsBag };
int inventory_slot5[2] = { 0, dItem_data__ItemNo__Boomerang };
int inventory_slot6[2] = { 0, dItem_data__ItemNo__DekuLeaf };
int inventory_slot7[2] = { 0, dItem_data__ItemNo__TingleTuner };
int inventory_slot8[3] = { 0, dItem_data__ItemNo__PictoBox, dItem_data__ItemNo__DeluxePictoBox};
int inventory_slot9[2] = { 0, dItem_data__ItemNo__IronBoots };
int inventory_slot10[2] = { 0, dItem_data__ItemNo__MagicArmor };
int inventory_slot11[2] = { 0, dItem_data__ItemNo__BaitBag };
int inventory_slot12[4] = { 0, dItem_data__ItemNo__HerosBow, dItem_data__ItemNo__FireAndIceArrows, dItem_data__ItemNo__LightArrow};
int inventory_slot13[2] = { 0, dItem_data__ItemNo__Bombs };
int inventory_slot14[11] = { 0, dItem_data__ItemNo__EmptyBottle, dItem_data__ItemNo__RedPotion, dItem_data__ItemNo__GreenPotion, dItem_data__ItemNo__BluePotion, dItem_data__ItemNo__HalfSoup, dItem_data__ItemNo__Soup,dItem_data__ItemNo__BottledWater, dItem_data__ItemNo__BottledFairy,dItem_data__ItemNo__BottledFirefly,dItem_data__ItemNo__ForestWater};
int inventory_slot15[11] = { 0, dItem_data__ItemNo__EmptyBottle, dItem_data__ItemNo__RedPotion, dItem_data__ItemNo__GreenPotion, dItem_data__ItemNo__BluePotion, dItem_data__ItemNo__HalfSoup, dItem_data__ItemNo__Soup,dItem_data__ItemNo__BottledWater, dItem_data__ItemNo__BottledFairy,dItem_data__ItemNo__BottledFirefly,dItem_data__ItemNo__ForestWater};
int inventory_slot16[11] = { 0, dItem_data__ItemNo__EmptyBottle, dItem_data__ItemNo__RedPotion, dItem_data__ItemNo__GreenPotion, dItem_data__ItemNo__BluePotion, dItem_data__ItemNo__HalfSoup, dItem_data__ItemNo__Soup,dItem_data__ItemNo__BottledWater, dItem_data__ItemNo__BottledFairy,dItem_data__ItemNo__BottledFirefly,dItem_data__ItemNo__ForestWater};
int inventory_slot17[11] = { 0, dItem_data__ItemNo__EmptyBottle, dItem_data__ItemNo__RedPotion, dItem_data__ItemNo__GreenPotion, dItem_data__ItemNo__BluePotion, dItem_data__ItemNo__HalfSoup, dItem_data__ItemNo__Soup,dItem_data__ItemNo__BottledWater, dItem_data__ItemNo__BottledFairy,dItem_data__ItemNo__BottledFirefly,dItem_data__ItemNo__ForestWater};
int inventory_slot18[2] = { 0, dItem_data__ItemNo__DeliveryBag };
int inventory_slot19[2] = { 0, dItem_data__ItemNo__Hookshot };
int inventory_slot20[2] = { 0, dItem_data__ItemNo__SkullHammer };

inventory_slot slot0 = { .base.vptr = &inventory_slot____vt, .slot_index = 0, .base.item_count = sizeof(inventory_slot0) / 4, .base.items = &inventory_slot0 };
inventory_slot slot1 = { .base.vptr = &inventory_slot____vt, .slot_index = 1, .base.item_count = sizeof(inventory_slot1) / 4, .base.items = &inventory_slot1 };
inventory_slot slot2 = { .base.vptr = &inventory_slot____vt, .slot_index = 2, .base.item_count = sizeof(inventory_slot2) / 4, .base.items = &inventory_slot2 };
inventory_slot slot3 = { .base.vptr = &inventory_slot____vt, .slot_index = 3, .base.item_count = sizeof(inventory_slot3) / 4, .base.items = &inventory_slot3 };
inventory_slot slot4 = { .base.vptr = &inventory_slot____vt, .slot_index = 4, .base.item_count = sizeof(inventory_slot4) / 4, .base.items = &inventory_slot4 };
inventory_slot slot5 = { .base.vptr = &inventory_slot____vt, .slot_index = 5, .base.item_count = sizeof(inventory_slot5) / 4, .base.items = &inventory_slot5 };
inventory_slot slot6 = { .base.vptr = &inventory_slot____vt, .slot_index = 6, .base.item_count = sizeof(inventory_slot6) / 4, .base.items = &inventory_slot6 };
inventory_slot slot7 = { .base.vptr = &inventory_slot____vt, .slot_index = 7, .base.item_count = sizeof(inventory_slot7) / 4, .base.items = &inventory_slot7 };
inventory_slot slot8 = { .base.vptr = &inventory_slot____vt, .slot_index = 8, .base.item_count = sizeof(inventory_slot8) / 4, .base.items = &inventory_slot8 };
inventory_slot slot9 = { .base.vptr = &inventory_slot____vt, .slot_index = 9, .base.item_count = sizeof(inventory_slot9) / 4, .base.items = &inventory_slot9 };
inventory_slot slot10 = { .base.vptr = &inventory_slot____vt, .slot_index = 10, .base.item_count = sizeof(inventory_slot10) / 4, .base.items = &inventory_slot10 };
inventory_slot slot11 = { .base.vptr = &inventory_slot____vt, .slot_index = 11, .base.item_count = sizeof(inventory_slot11) / 4, .base.items = &inventory_slot11 };
inventory_slot slot12 = { .base.vptr = &inventory_slot____vt, .slot_index = 12, .base.item_count = sizeof(inventory_slot12) / 4, .base.items = &inventory_slot12 };
inventory_slot slot13 = { .base.vptr = &inventory_slot____vt, .slot_index = 13, .base.item_count = sizeof(inventory_slot13) / 4, .base.items = &inventory_slot13 };
inventory_slot slot14 = { .base.vptr = &inventory_slot____vt, .slot_index = 14, .base.item_count = sizeof(inventory_slot14) / 4, .base.items = &inventory_slot14 };
inventory_slot slot15 = { .base.vptr = &inventory_slot____vt, .slot_index = 15, .base.item_count = sizeof(inventory_slot15) / 4, .base.items = &inventory_slot15 };
inventory_slot slot16 = { .base.vptr = &inventory_slot____vt, .slot_index = 16, .base.item_count = sizeof(inventory_slot16) / 4, .base.items = &inventory_slot16 };
inventory_slot slot17 = { .base.vptr = &inventory_slot____vt, .slot_index = 17, .base.item_count = sizeof(inventory_slot17) / 4, .base.items = &inventory_slot17 };
inventory_slot slot18 = { .base.vptr = &inventory_slot____vt, .slot_index = 18, .base.item_count = sizeof(inventory_slot18) / 4, .base.items = &inventory_slot18 };
inventory_slot slot19 = { .base.vptr = &inventory_slot____vt, .slot_index = 19, .base.item_count = sizeof(inventory_slot19) / 4, .base.items = &inventory_slot19 };
inventory_slot slot20 = { .base.vptr = &inventory_slot____vt, .slot_index = 20, .base.item_count = sizeof(inventory_slot20) / 4, .base.items = &inventory_slot20 };


#pragma endregion inventory_defines

void inventory_slot__init(inventory_slot *this, base_pane *pane){
    inventory_base__init(&this->base, pane);
    this->base.vptr = (inventory_base_vtbl *)&inventory_slot____vt;

    float totalWidth = base_pane_width(this->base.parent) - INV_XPADDING;
    float totalHeight = base_pane_height(this->base.parent) - INV_YPADDING;

    float xSpacing = totalWidth / INVENTORY_COLS;
    float ySpacing = totalHeight / INVENTORY_ROWS;

    int curr_column = (int)this->slot_index % INVENTORY_COLS;
    int curr_row = (int)this->slot_index / INVENTORY_COLS;

    this->base.x_offset = INV_XPADDING + (xSpacing * curr_column);
    this->base.y_offset = INV_YPADDING + (ySpacing * curr_row);

    this->base.x_offset = base_pane_xOffset(this->base.parent, this->base.x_offset);
    this->base.y_offset = base_pane_yOffset(this->base.parent, this->base.y_offset);
}

void inventory_slot__update_data(inventory_slot *this){
    char *slot_value_ptr = (char*)((int)&g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mItem + this->slot_index);
    char slot_value = *slot_value_ptr;
    if(slot_value == 0xff){
        slot_value = 0;
    }
    for (int i = 0; i <  this->base.item_count; i++)
    {
        
        // if(hasItem){
        //     OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_slot__update_data: hasItem = %d\n",hasItem));
        //     this->base.item_index = i;
        //     return;
        // }

        if((char)this->base.items[i] == slot_value){
            this->base.item_index = i;
            return;
        }
    }
    OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_slot__setIndex: couldn't set index... slot_value = %d | slot_index = %d\n",(int)slot_value, (int)this->slot_index));
    this->base.item_index = 0;
}
/*
set magic - 
    g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusA.mMaxMagic
    g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusA.mCurrMagic
*/
void inventory_slot__update_inventory(inventory_slot *this){
    int current_item = this->base.items[this->base.item_index];
    char *item_slot = (char*)((int)&g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mItem + this->slot_index);
    if(current_item > 0){
        if(current_item >= dItem_data__ItemNo__EmptyBottle && current_item <= dItem_data__ItemNo__ForestWater){     
            //dSv_player_get_item_c__onItem(dSv_player_get_item_c * this, int param_1, uchar param_2); 
            //dSv_player_get_item_c__onItem(&g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mGetItem,this->slot_index,0);      

            *item_slot = (char)current_item;
        }
        else{
            d_item__execItemGet((char)this->base.items[this->base.item_index]);
        } 
    }
    else{
        g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mGetItem.mBits[this->slot_index] = (uint)0;
        *item_slot = 0xff;
    }
}

#endif
