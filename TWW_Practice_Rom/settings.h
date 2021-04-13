#ifndef _INPUT_H
    #define _INPUT_H "input.h"
    #include _INPUT_H
#endif

typedef struct Settings {
    bool frame_advance_enabled;
    short toggle_frame_advance[2];
    bool menu_enabled;
    short toggle_menu[2];
} Settings;

Settings settings = {
  .frame_advance_enabled = true,
  .toggle_frame_advance = {Z, D_PAD_LEFT},
  .menu_enabled = false,
  .toggle_menu = {X,D_PAD_LEFT}
};