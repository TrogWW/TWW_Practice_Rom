#ifndef STRINGHELPERS_C_INCLUDED
#define STRINGHELPERS_C_INCLUDED

#include "stringhelpers.h"

bool str_starts_with(const char *pre, const char *str){
    size_t lenpre = MSL_C_PPCEABI_bare_H__strlen(pre);
    size_t lenstr = MSL_C_PPCEABI_bare_H__strlen(str);
    if(lenstr < lenpre){
        return false;
    }
    else{
        int memcmp = MSL_C_PPCEABI_bare_H__memcmp(pre, str, lenpre);
        if(memcmp == 0){
            return true;
        }
        else{
            return false;
        }
    }
}
int atoi(const char *s){
    int sign = 1;
    if(*s == '-'){
        sign = -1;
        s++;
    }
    int num = 0;
    while(*s){
        num = ((*s)-'0') + num * 10;
        s++;
    }
    return num * sign;
}
bool char_is_digit(const char c){
    if(c >= '0' && c <= '9'){
        return true;
    }
    else{
        return false;
    }
}

char* str_extract_int(const char *str){
    size_t len = MSL_C_PPCEABI_bare_H__strlen(str);
    int new_str_len = 0;
    int digit_start = -1;
    char* extracted_int = NULL;
    for(int i = 0; i < len; i++){
        bool is_digit = char_is_digit(str[i]);
        if(is_digit){
            digit_start = i;
            break;
        }
    }
    if(digit_start != -1){
        new_str_len = 1;
        for(int i = digit_start + 1; i < len; i++){
            bool is_digit = char_is_digit(str[i]);
            if(is_digit){
                new_str_len = new_str_len + 1;
            }
            else{
                break;
            }
        }
    }
    if(new_str_len > 0){
        extracted_int = (char*)JKernel__operator_new(sizeof(char) * (new_str_len + 1));
        cLib_memCpy(extracted_int, &str[digit_start],new_str_len);
        extracted_int[new_str_len] = '\0';
        //OSReport(MSL_C_PPCEABI_bare_H__printf("str_extract_int: digit_start = %d | new_str_len = %d | extracted_int = %s\n", digit_start,new_str_len, extracted_int));
    }
    return extracted_int;
}
#endif