#ifndef INVENTORYPANE_C_INCLUDED
#define INVENTORYPANE_C_INCLUDED

#include "inventory_pane.h"
#include "base_pane.c"
#define TIMG_TEXT 0x54494d47

#define it13_TEXT 0x69743133
#define ITEMICON_RES_NAME "itemicon"

enum ITEMICON_RES_FILE_IDS {
  /* TIMG */
  ITEMICON_BTI_AMULET_00=0x3,
  ITEMICON_BTI_AMULET_01=0x4,
  ITEMICON_BTI_ARROWCASE_1=0x5,
  ITEMICON_BTI_ARROWCASE_2=0x6,
  ITEMICON_BTI_ARROW_00=0x7,
  ITEMICON_BTI_ARROW_01=0x8,
  ITEMICON_BTI_ARROW_02=0x9,
  ITEMICON_BTI_ARROW_03=0xA,
  ITEMICON_BTI_ARROW_POWER_01=0xB,
  ITEMICON_BTI_ARROW_POWER_02=0xC,
  ITEMICON_BTI_BAIT_01=0xD,
  ITEMICON_BTI_BAIT_02=0xE,
  ITEMICON_BTI_BATON=0xF,
  ITEMICON_BTI_BATON_STONE=0x10,
  ITEMICON_BTI_BEAST_01=0x11,
  ITEMICON_BTI_BEAST_02=0x12,
  ITEMICON_BTI_BEAST_03=0x13,
  ITEMICON_BTI_BEAST_04=0x14,
  ITEMICON_BTI_BEAST_05=0x15,
  ITEMICON_BTI_BEAST_06=0x16,
  ITEMICON_BTI_BEAST_07=0x17,
  ITEMICON_BTI_BEAST_08=0x18,
  ITEMICON_BTI_BIG_PURSE=0x19,
  ITEMICON_BTI_BOKO_STICK=0x1A,
  ITEMICON_BTI_BOMBPOUCH_1=0x1B,
  ITEMICON_BTI_BOMBPOUCH_2=0x1C,
  ITEMICON_BTI_BOMB_00=0x1D,
  ITEMICON_BTI_BOOMERANG=0x1E,
  ITEMICON_BTI_BOOTS_00=0x1F,
  ITEMICON_BTI_BOOTS_01=0x20,
  ITEMICON_BTI_BOSS_KEY=0x21,
  ITEMICON_BTI_BOTTLE_00=0x22,
  ITEMICON_BTI_BOTTLE_01=0x23,
  ITEMICON_BTI_BOTTLE_02=0x24,
  ITEMICON_BTI_BOTTLE_03=0x25,
  ITEMICON_BTI_BOTTLE_04=0x26,
  ITEMICON_BTI_BOTTLE_05=0x27,
  ITEMICON_BTI_BOTTLE_06=0x28,
  ITEMICON_BTI_BOTTLE_07=0x29,
  ITEMICON_BTI_BOTTLE_08=0x2A,
  ITEMICON_BTI_BOTTLE_09=0x2B,
  ITEMICON_BTI_BOW_01=0x2C,
  ITEMICON_BTI_CAMERA=0x2D,
  ITEMICON_BTI_CAMERA_2=0x2E,
  ITEMICON_BTI_CLOTHES=0x2F,
  ITEMICON_BTI_CMAP_HINT2=0x30,
  ITEMICON_BTI_CMAP_PHANTOMSHIP2=0x31,
  ITEMICON_BTI_CMAP_TINGLE2=0x32,
  ITEMICON_BTI_CMAP_TREASURE2=0x33,
  ITEMICON_BTI_CMAP_TRI2=0x34,
  ITEMICON_BTI_COMPASS=0x35,
  ITEMICON_BTI_COVEROFBAIT=0x36,
  ITEMICON_BTI_COVEROFBEAST=0x37,
  ITEMICON_BTI_COVER_RETURN=0x38,
  ITEMICON_BTI_DELIVERY=0x39,
  ITEMICON_BTI_DELIVERY_01=0x3A,
  ITEMICON_BTI_DELIVERY_02=0x3B,
  ITEMICON_BTI_DELIVERY_03=0x3C,
  ITEMICON_BTI_DELIVERY_04=0x3D,
  ITEMICON_BTI_DELIVERY_05=0x3E,
  ITEMICON_BTI_DELIVERY_06=0x3F,
  ITEMICON_BTI_DELIVERY_07=0x40,
  ITEMICON_BTI_DELIVERY_08=0x41,
  ITEMICON_BTI_DELIVERY_09=0x42,
  ITEMICON_BTI_DELIVERY_10=0x43,
  ITEMICON_BTI_DELIVERY_11=0x44,
  ITEMICON_BTI_DELIVERY_12=0x45,
  ITEMICON_BTI_DELIVERY_13=0x46,
  ITEMICON_BTI_DELIVERY_14=0x47,
  ITEMICON_BTI_DELIVERY_15=0x48,
  ITEMICON_BTI_DELIVERY_16=0x49,
  ITEMICON_BTI_DELIVERY_17=0x4A,
  ITEMICON_BTI_DELIVERY_18=0x4B,
  ITEMICON_BTI_DELIVERY_19=0x4C,
  ITEMICON_BTI_DUNGEON_MAP=0x4D,
  ITEMICON_BTI_FAN=0x4E,
  ITEMICON_BTI_GET_KEY=0x4F,
  ITEMICON_BTI_GET_RUPY=0x50,
  ITEMICON_BTI_GLOVES_00=0x51,
  ITEMICON_BTI_GLOVES_01=0x52,
  ITEMICON_BTI_GOD_SYMBOL_00=0x53,
  ITEMICON_BTI_GOD_SYMBOL_01=0x54,
  ITEMICON_BTI_GOD_SYMBOL_02=0x55,
  ITEMICON_BTI_HAMMER_01=0x56,
  ITEMICON_BTI_HATCHET=0x57,
  ITEMICON_BTI_HEART_UP_01=0x58,
  ITEMICON_BTI_HEART_UP_02=0x59,
  ITEMICON_BTI_HOOKSHOT=0x5A,
  ITEMICON_BTI_IRON_CLUB=0x5B,
  ITEMICON_BTI_LONGSWORD=0x5C,
  ITEMICON_BTI_MAX_PURSE=0x5D,
  ITEMICON_BTI_ROPE=0x5E,
  ITEMICON_BTI_SAIL_00=0x5F,
  ITEMICON_BTI_SAIL_01=0x60,
  ITEMICON_BTI_SAIL_02=0x61,
  ITEMICON_BTI_SHIELD_00=0x62,
  ITEMICON_BTI_SHIELD_01=0x63,
  ITEMICON_BTI_SHIELD_02=0x64,
  ITEMICON_BTI_SPEAR=0x65,
  ITEMICON_BTI_SWORD_00=0x66,
  ITEMICON_BTI_SWORD_01=0x67,
  ITEMICON_BTI_SWORD_02=0x68,
  ITEMICON_BTI_SWORD_03=0x69,
  ITEMICON_BTI_TELESCOPE=0x6A,
  ITEMICON_BTI_TINGLE_FIGURE=0x6B,
  ITEMICON_BTI_TRIFORCE_00=0x6C,
  ITEMICON_BTI_TRIFORCE_01=0x6D,
  ITEMICON_BTI_TRIFORCE_02=0x6E,
  ITEMICON_BTI_TRIFORCE_03=0x6F,
  ITEMICON_BTI_TRIFORCE_04=0x70,
  ITEMICON_BTI_TRIFORCE_05=0x71,
  ITEMICON_BTI_TRIFORCE_06=0x72,
  ITEMICON_BTI_TRIFORCE_07=0x73,
  ITEMICON_BTI_WHISTLE=0x74,
};

static inventory_pane_vtbl inventory_pane____vt = {
    inventory_pane__draw,
    inventory_pane__hide,
    inventory_pane__update_cursor,
    inventory_pane__open,
    inventory_pane__close
};

inventory_pane* inventory_pane__new(inventory_pane *this, base_pane *parent, J2DWindow *pane, float relativeX, float relativeY){
    if(this == 0){
        this = (inventory_pane*)JKernel__operator_new(sizeof(inventory_pane));
    }
    base_pane___new(&this->base);
    this->base.vptr = (base_pane_vtbl *)&inventory_pane____vt;

    this->parent = parent;
    this->base.pane = pane;

    base_pane_set_title(&this->base, this->parent, relativeX, relativeY, "Inventory", &TEXT_PALLETE_WHITE_70, 0);


    
    // this->picture = (J2DPicture *)J2DPane__search(pane, it13_TEXT);

//     //OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_pane__new: g_dComIfG_gameInfo.mPlay.mpItemIconArchive = %X\n",g_dComIfG_gameInfo.mPlay.mpItemIconArchive));
// //   int JKRArchive__readTypeResource(void * pDst, ulong size, ulong param_3, char * pFilename, JKRArchive * pArc);

//     JKRArchive__readTypeResource(&this->resImg, 0xC00,TIMG_TEXT,"telescope.bti",g_dComIfG_gameInfo.mPlay.mpItemIconArchive);
//     OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_pane__new:&this->resImg = %X\n",&this->resImg));
//     //os__DCStoreRange(*(ResTIMG *)resTIMG_ptr, 0xC00);
//     //undefined J2DPicture__changeTexture(J2DPicture * this, ResTIMG * param_1, uchar param_2);
//     J2DPicture__changeTexture(this->picture, &this->resImg, 0);
//     //J2DPicture__changeTexture_1(this->picture, "telescope.bti", 0);
//     OSReport(MSL_C_PPCEABI_bare_H__printf("inventory_pane__new: this->picture->mpTexture[0] = %X | this->picture->mpTexture[1] = %X\n",this->picture->mpTexture[0], this->picture->mpTexture[1]));
    return this;
}
void inventory_pane__draw(inventory_pane *this){
    this->base.pane->parent.mbDraw = true;
}
void inventory_pane__hide(inventory_pane *this){
    this->base.pane->parent.mbDraw = false;
}
void inventory_pane__update_cursor(inventory_pane *this){

}
void inventory_pane__open(inventory_pane *this){

}
void inventory_pane__close(inventory_pane *this){

}
void inventory_pane__update_fields(inventory_pane *this){

}

#endif