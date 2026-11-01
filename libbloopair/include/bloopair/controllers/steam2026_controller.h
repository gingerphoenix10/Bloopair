#pragma once

#include "common.h"

enum {
    // Buttons with 2026 in the name are either specific to the 2026 model, or
    // have different / ambiguous names for the 2015 version. E.g. L1 = LB
    STEAM_BUTTON_UP,
    STEAM_BUTTON_DOWN,
    STEAM_BUTTON_LEFT,
    STEAM_BUTTON_RIGHT,
    STEAM_2026_TRIGGER_R1,
    STEAM_2026_TRIGGER_L1,
    STEAM_BUTTON_A,
    STEAM_BUTTON_B,
    STEAM_BUTTON_X,
    STEAM_BUTTON_Y,
    STEAM_BUTTON_LSTICK,
    STEAM_BUTTON_RSTICK,
    STEAM_BUTTON_STEAM,
    STEAM_2026_BUTTON_MENU,
    STEAM_2026_BUTTON_VIEW,
    STEAM_2026_TRIGGER_R2,
    STEAM_2026_TRIGGER_L2,
    STEAM_2026_BUTTON_QUICK_ACCESS,
    STEAM_2026_GRIP_L4,
    STEAM_2026_GRIP_L5,
    STEAM_2026_GRIP_R4,
    STEAM_2026_GRIP_R5,
};

typedef struct {

} Steam2026Configuration;