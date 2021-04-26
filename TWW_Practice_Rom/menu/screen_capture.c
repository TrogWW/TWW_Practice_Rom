#include "screen_capture.h"
//vtbl implementation of dDlst_base_c
static void* dlst_gz_capture_vtbl[] = {
    NULL, NULL, // rtti placeholder
    dDlst_base_c__dDlst_base_c_destructor, // parent destructor
    screen_capture___draw
};

void screen_capture___new(screen_capture *this) {
    if(this == 0){
        this = (screen_capture*)JKernel__operator_new(sizeof(screen_capture));
    }
    if(this == 0){
        OSReport("screen_capture___new: Not enough memory to create screen_capture");
        return;
    }
    //implement virtual function 'draw' for dDlst_base_c class
    this->base.vtbl = dlst_gz_capture_vtbl;
}
void screen_capture___destroy(screen_captue *this){
    dDlst_MENU_CAPTURE_c__dDlst_MENU_CAPTURE_c_destructor(&this->dDlst_screen_capture);
}
//implementation of virtual function 'draw'
void screen_capture___draw(screen_capture *this) {
    dDlst_MENU_CAPTURE_c__draw(&this->dDlst_screen_capture); 
}