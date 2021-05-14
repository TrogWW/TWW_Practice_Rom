#ifndef SWORDSHIELD_SLOT_C_INCLUDED
#define SWORDSHIELD_SLOT_C_INCLUDED

#define SS_XPADDING 20.0f
#define SS_YPADDING 300.0f
#define SS_TOTAL_WIDTH 150.0f
#define SS_TOTAL_HEIGHT 80.0f

#define SWORDSHIELD_SIZE 2

#include "sword_shield_slot.h"
#include "inventory_base.c"
#include "../base_pane.c"
#include "../../helpers/hexhelpers.c"

typedef enum dItem_data__ItemCategory {
    dItem_data__ItemCategory__sword = 0,
    dItem_data__ItemCategory__shield = 1
} dItem_data__ItemCategory;
static sword_shield_slot_vtbl sword_shield_slot____vt = {
    sword_shield_slot__init,
    sword_shield_slot__update_data,
    sword_shield_slot__update_inventory,
    inventory_base__draw,   //do not override base execute
    inventory_base__execute //do not override base execute
};

#pragma region sword_shield_defines

int ss_items0[5] = { 0, dItem_data__ItemNo__HerosSword, dItem_data__ItemNo__MasterSwordPowerless, dItem_data__ItemNo__MasterSwordHalfPower, dItem_data__ItemNo__MasterSwordFullPower};
int ss_items1[3] = { 0, dItem_data__ItemNo__HerosShield, dItem_data__ItemNo__MirrorShield };                //, dItem_data__ItemNo__HerosShield, dItem_data__ItemNo__MirrorShield };
int ss_items2[2] = { 0 , dItem_data__ItemNo__HerosShield };

sword_shield_slot ss_slot0 = { .base.vptr = &sword_shield_slot____vt, .base.item_count = sizeof(ss_items0) / 4, .base.items = &ss_items0, .category = dItem_data__ItemCategory__sword };
sword_shield_slot ss_slot1 = { .base.vptr = &sword_shield_slot____vt, .base.item_count = sizeof(ss_items1) / 4, .base.items = &ss_items1, .category = dItem_data__ItemCategory__shield };
sword_shield_slot ss_slot2 = { .base.vptr = &sword_shield_slot____vt, .base.item_count = sizeof(ss_items2) / 4, .base.items = &ss_items2, .category = 2 };

#pragma endregion sword_shield_defines

void sword_shield_slot__init(sword_shield_slot *this, base_pane *pane){
    inventory_base__init(&this->base, pane);
    this->base.vptr = (sword_shield_slot_vtbl *)&sword_shield_slot____vt;

    float totalWidth = SS_TOTAL_WIDTH;
    float totalHeight = SS_TOTAL_HEIGHT;

    float xSpacing = totalWidth / SWORDSHIELD_SIZE;

    this->base.x_offset = SS_XPADDING + (xSpacing * this->category);
    this->base.y_offset = SS_YPADDING;

    this->base.x_offset = base_pane_xOffset(this->base.parent, this->base.x_offset);
    this->base.y_offset = base_pane_yOffset(this->base.parent, this->base.y_offset);
}
void sword_shield_slot__update_data(sword_shield_slot *this){
    byte current_val = g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mCollect.mData[this->category];
    //OSReport(MSL_C_PPCEABI_bare_H__printf("sword_shield_slot__update_data: this->category = %d | mData = %X\n",this->category,current_val));
    if(current_val == 0){
        this->base.item_index = 0;
        return;
    }
    for (int i = 0; i < this->base.item_count; i++)
    {
        if(isNthBitSet(current_val,i)){
            //OSReport(MSL_C_PPCEABI_bare_H__printf("sword_shield_slot__update_data: bit set: = %d\n",i));
            this->base.item_index = i;
            return;
        }
        /* code */
    }
    OSReport(MSL_C_PPCEABI_bare_H__printf("sword_shield_slot__update_data: unable to find item index for value: = %d\n",current_val));
    // byte data = g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mCollect.mData[this->category];
    // if(data == 0){
    //     this->base.item_index = 0;
    //     return;
    // }
    // for (int i = 1; i < this->base.item_count; i++)
    // {
    //     if(data == i - 1){
    //         this->base.item_index = i;
    //         return;
    //     }
    // }
    // //unable to find matching item
    // this->base.item_index = 0;
}
void sword_shield_slot__update_inventory(sword_shield_slot *this){
    int current_item = this->base.items[this->base.item_index];

    g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mCollect.mData[this->category] = 0; //reset data for this category. d_item__execItemGet applies binary 'or' on this field which leaves lingering data.
    if(current_item > 0){       
        d_item__execItemGet((char)this->base.items[this->base.item_index]);
    }
    else{
        g_dComIfG_gameInfo.mSvInfo.mSave.mPlayer.mStatusA.mInventorySlotIndexOnButton[this->category + 5] = 0xff;   //remove item from link's hand
    }
}
void inventory_slot__draw(inventory_slot *this){}
void inventory_slot__execute(inventory_slot *this){}
#endif