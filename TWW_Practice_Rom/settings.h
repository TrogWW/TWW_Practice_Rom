#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include "input.h"

typedef struct Settings {
    bool frame_advance_enabled;
    short toggle_frame_advance[2];
    short toggle_menu_combo[2];
} Settings;

Settings settings = {
  .frame_advance_enabled = true,
  .toggle_frame_advance = {Z_PRESSED, D_PAD_LEFT_PRESSED},
  .toggle_menu_combo = {X_PRESSED, D_PAD_LEFT_PRESSED}
};
#endif