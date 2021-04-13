
#ifndef _SETTINGS_H
    #define _SETTINGS_H "settings.h"
    #include _SETTINGS_H
#endif
#ifndef _INPUT_H
    #define _INPUT_H "input.h"
    #include _INPUT_H
#endif

typedef struct Menu {
    Settings* menu_settings;  
} Menu;

Menu menu = {
    .menu_settings = &settings
};

void _menu_render(){
    /*TODO*/
}