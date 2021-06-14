#ifndef WATCHITEM_C_INCLUDED
#define WATCHITEM_C_INCLUDED

#include "watch_item.h"

/*
typedef struct watch_item {
    char *display_name;
    int is_active;
    char *flag;
    int address_offset_count;
    int *address_offsets;
} watch_item;
*/
void watch_item__new(watch_item *this, int offset){
    if(this->display_name != 0){
        this->display_name = ((int)this->display_name) + offset;
    }
    if(this->flag != 0){
        this->flag = ((int)this->flag) + offset;
    }
    if(this->address_offset_count > 0){
        this->address_offsets = ((int)this->address_offsets) + offset;
    }
    //OSReport(MSL_C_PPCEABI_bare_H__printf("watch_item__new: this->display_name = %s, this->flag = %s\n", this->display_name, this->flag));
}
int watch_item__get_address(watch_item *this){
    int curr_address = this->address_offsets[0];
    for(int i = 1; i < this->address_offset_count; i++){
        if((int)curr_address < 0x80000000 || (int)curr_address > 0x9000000){
            return NULL;
        }
        else{
            int curr_offset = (int)this->address_offsets[i];
            int curr_address_value = (int)(*(int *)curr_address);
            curr_address = (void *)(curr_address_value + curr_offset);
            //OSReport(MSL_C_PPCEABI_bare_H__printf("watch_item__get_address: this->display_name = %s, curr_offset = %X, curr_address_value = %X, curr_address = %X\n", this->display_name, curr_offset, curr_address_value, curr_address));
        }
    }
    if((int)curr_address < 0x80000000 || (int)curr_address > 0x9000000){
        return NULL;
    }
    else{
        return curr_address;
    }
}

void watch_item__get_display_value(watch_item *this, char* display_value){

    int address = watch_item__get_address(this);
    
    if(address != NULL){
        size_t flag_len = MSL_C_PPCEABI_bare_H__strlen(this->flag);
        int is_type = MSL_C_PPCEABI_bare_H__memcmp(this->flag, "%f", flag_len);
        
        if(is_type == 0){           //if float
            float *float_val = (float *)address;
            MSL_C_PPCEABI_bare_H__sprintf(display_value, "%f", *float_val);
            return;
        }
        is_type = MSL_C_PPCEABI_bare_H__memcmp(this->flag, "%s", flag_len);
        if(is_type == 0){           //if string
            char *str = (char *)address;
            MSL_C_PPCEABI_bare_H__sprintf(display_value, "%s", str);
            return;
        }
        is_type = MSL_C_PPCEABI_bare_H__memcmp(this->flag, "%d", flag_len);
        if(is_type == 0){           //if int
            int *i = (int *)address;
            MSL_C_PPCEABI_bare_H__sprintf(display_value, "%d", *i);
            return;
        }
        is_type = MSL_C_PPCEABI_bare_H__memcmp(this->flag, "%hi", flag_len);
        if(is_type == 0){           //if short
            short *s = (short *)address;
            MSL_C_PPCEABI_bare_H__sprintf(display_value, "%hi", *s);
            return;
        }
        is_type = MSL_C_PPCEABI_bare_H__memcmp(this->flag, "%hhx", flag_len);
        if(is_type == 0){           //if byte
            byte b = (byte)((char *)address)[0];
            MSL_C_PPCEABI_bare_H__sprintf(display_value, "%hhx", b);
            return;
        }
        //unspecified type, use flag defined in config
        int *val = (int *)address;
        MSL_C_PPCEABI_bare_H__sprintf(display_value, this->flag, *val);
        
    }
    else{
        MSL_C_PPCEABI_bare_H__sprintf(display_value, "%s", "???");
    }
}
#endif