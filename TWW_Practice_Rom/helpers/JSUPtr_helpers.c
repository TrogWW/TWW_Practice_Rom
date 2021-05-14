#ifndef JSUPtrList_C_INCLUDED
#define JSUPtrList_C_INCLUDED

#include "JSUPtr_helpers.h"

/*
struct JSUPtrList {
    struct JSUPtrLink * mpHead; // 0x04 bytes
    struct JSUPtrLink * mpTail; // 0x04 bytes
    int mCount; // 0x04 bytes
};
struct JSUPtrLink {
    pointer mpData; // 0x04 bytes
    struct JSUPtrList * mpList; // 0x04 bytes
    struct JSUPtrLink * mpPrev; // 0x04 bytes
    struct JSUPtrLink * mpNext; // 0x04 bytes
};
*/
// void* JSUPtrList__get_index(JSUPtrList *this, int index){
//     if(index < 0 || index >= this->mCount){
//         return NULL;
//     }
//     int curr_index = 0;
//     JSUPtrLink *curr_link = this->mpHead;
//     while(curr_index < this->mCount){
//         if(curr_index == index){
//             return curr_link->mpData;
//         }
//         else{
//             curr_link = curr_link->mpNext;
//             curr_index = curr_index + 1;
//         }
//     }
//     return NULL;
// }
#endif