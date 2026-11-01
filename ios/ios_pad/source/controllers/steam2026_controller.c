/*
 *   Copyright (C) 2026 GaryOderNichts
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "steam2026_controller.h"
#include <bloopair/controllers/steam2026_controller.h>

static const MappingConfiguration default_steam2026_mapping = {
    .num = 26,
    .mappings = {
        { BLOOPAIR_PRO_STICK_L_UP,      BLOOPAIR_PRO_STICK_L_UP, },
        { BLOOPAIR_PRO_STICK_L_DOWN,    BLOOPAIR_PRO_STICK_L_DOWN, },
        { BLOOPAIR_PRO_STICK_L_LEFT,    BLOOPAIR_PRO_STICK_L_LEFT, },
        { BLOOPAIR_PRO_STICK_L_RIGHT,   BLOOPAIR_PRO_STICK_L_RIGHT, },

        { BLOOPAIR_PRO_STICK_R_UP,      BLOOPAIR_PRO_STICK_R_UP, },
        { BLOOPAIR_PRO_STICK_R_DOWN,    BLOOPAIR_PRO_STICK_R_DOWN, },
        { BLOOPAIR_PRO_STICK_R_LEFT,    BLOOPAIR_PRO_STICK_R_LEFT, },
        { BLOOPAIR_PRO_STICK_R_RIGHT,   BLOOPAIR_PRO_STICK_R_RIGHT, },

        { STEAM_2026_TRIGGER_R1,        BLOOPAIR_PRO_TRIGGER_R, },
        { STEAM_2026_TRIGGER_L1,        BLOOPAIR_PRO_TRIGGER_L, },

        { STEAM_BUTTON_Y,               BLOOPAIR_PRO_BUTTON_X, },
        { STEAM_BUTTON_X,               BLOOPAIR_PRO_BUTTON_Y, },
        { STEAM_BUTTON_B,               BLOOPAIR_PRO_BUTTON_A, },
        { STEAM_BUTTON_A,               BLOOPAIR_PRO_BUTTON_B, },

        { STEAM_BUTTON_RSTICK,          BLOOPAIR_PRO_BUTTON_STICK_R, },
        { STEAM_BUTTON_LSTICK,          BLOOPAIR_PRO_BUTTON_STICK_L, },

        { STEAM_BUTTON_DOWN,            BLOOPAIR_PRO_BUTTON_DOWN, },
        { STEAM_BUTTON_UP,              BLOOPAIR_PRO_BUTTON_UP },
        { STEAM_BUTTON_RIGHT,           BLOOPAIR_PRO_BUTTON_RIGHT, },
        { STEAM_BUTTON_LEFT,            BLOOPAIR_PRO_BUTTON_LEFT, },

        { STEAM_2026_TRIGGER_L2,        BLOOPAIR_PRO_TRIGGER_ZL, },
        { STEAM_2026_TRIGGER_R2,        BLOOPAIR_PRO_TRIGGER_ZR, },

        { STEAM_BUTTON_STEAM,           BLOOPAIR_PRO_BUTTON_HOME, },
        { STEAM_2026_BUTTON_MENU,       BLOOPAIR_PRO_BUTTON_PLUS, },
        { STEAM_2026_BUTTON_VIEW,       BLOOPAIR_PRO_BUTTON_MINUS, },

        // map unused buttons to the reserved button bit
        { STEAM_2026_BUTTON_QUICK_ACCESS, BLOOPAIR_PRO_RESERVED, },
        { STEAM_2026_GRIP_L4,             BLOOPAIR_PRO_RESERVED, },
        { STEAM_2026_GRIP_L5,             BLOOPAIR_PRO_RESERVED, },
        { STEAM_2026_GRIP_R4,             BLOOPAIR_PRO_RESERVED, },
        { STEAM_2026_GRIP_R5,             BLOOPAIR_PRO_RESERVED, },
    },
};

static const uint32_t dpad_map[9] = {
    BTN(STEAM_BUTTON_UP),
    BTN(STEAM_BUTTON_UP) | BTN(STEAM_BUTTON_RIGHT),
    BTN(STEAM_BUTTON_RIGHT),
    BTN(STEAM_BUTTON_RIGHT) | BTN(STEAM_BUTTON_DOWN),
    BTN(STEAM_BUTTON_DOWN),
    BTN(STEAM_BUTTON_DOWN) | BTN(STEAM_BUTTON_LEFT),
    BTN(STEAM_BUTTON_LEFT),
    BTN(STEAM_BUTTON_LEFT) | BTN(STEAM_BUTTON_UP),
    0,
};

void controllerData_steam2026(Controller* controller, uint8_t* buf, uint16_t len)
{
    BloopairReportBuffer* rep = &controller->reportBuffer;

    if ((buf[0] == REPORT_INPUT || buf[0] == REPORT_INPUT_BLE) && len >= sizeof(Steam2026InputReport)) {
        Steam2026InputReport* inRep = (Steam2026InputReport*) buf;

        // Since the joystick is already signed, this might be correct? Can't test until connection is fixed
        rep->left_stick_x = inRep->left_stick_x / 32767 * WPAD_PRO_AXIS_NORMALIZE_VALUE;
        rep->left_stick_y = inRep->left_stick_y / 32767 * WPAD_PRO_AXIS_NORMALIZE_VALUE;
        rep->right_stick_x = inRep->right_stick_x / 32767 * WPAD_PRO_AXIS_NORMALIZE_VALUE;
        rep->right_stick_y = inRep->right_stick_y / 32767 * WPAD_PRO_AXIS_NORMALIZE_VALUE;

        rep->buttons = 0;

        if (inRep->buttons.dpad_up)
            rep->buttons |= BTN(STEAM_BUTTON_UP);
        if (inRep->buttons.dpad_left)
            rep->buttons |= BTN(STEAM_BUTTON_LEFT);
        if (inRep->buttons.dpad_down)
            rep->buttons |= BTN(STEAM_BUTTON_DOWN);
        if (inRep->buttons.dpad_right)
            rep->buttons |= BTN(STEAM_BUTTON_RIGHT);

        if (inRep->buttons.a)
            rep->buttons |= BTN(STEAM_BUTTON_A);
        if (inRep->buttons.b)
            rep->buttons |= BTN(STEAM_BUTTON_B);
        if (inRep->buttons.x)
            rep->buttons |= BTN(STEAM_BUTTON_X);
        if (inRep->buttons.y)
            rep->buttons |= BTN(STEAM_BUTTON_Y);
        if (inRep->buttons.l1)
            rep->buttons |= BTN(STEAM_2026_TRIGGER_L1);
        if (inRep->buttons.r1)
            rep->buttons |= BTN(STEAM_2026_TRIGGER_R1);
        if (inRep->buttons.menu)
            rep->buttons |= BTN(STEAM_2026_BUTTON_MENU);
        if (inRep->buttons.view)
            rep->buttons |= BTN(STEAM_2026_BUTTON_MENU);
        if (inRep->buttons.steam)
            rep->buttons |= BTN(STEAM_BUTTON_STEAM);

        if (inRep->buttons.lstick)
            rep->buttons |= BTN(STEAM_BUTTON_LSTICK);
        if (inRep->buttons.rstick)
            rep->buttons |= BTN(STEAM_BUTTON_RSTICK);

        if (inRep->buttons.quickaccess)
            rep->buttons |= BTN(STEAM_2026_BUTTON_QUICK_ACCESS);
        if (inRep->buttons.l4)
            rep->buttons |= BTN(STEAM_2026_GRIP_L4);
        if (inRep->buttons.l5)
            rep->buttons |= BTN(STEAM_2026_GRIP_L5);
        if (inRep->buttons.r4)
            rep->buttons |= BTN(STEAM_2026_GRIP_R4);
        if (inRep->buttons.r5)
            rep->buttons |= BTN(STEAM_2026_GRIP_R5);

        if (!controller->isReady) {
            controller->isReady = 1;
        }
    }
}

void controllerRumble_steam2026(Controller* controller, uint8_t rumble)
{
    // TODO: Implement rumble
}

void controllerDeinit_steam2026(Controller* controller)
{
}

void controllerInit_steam2026(Controller* controller)
{
    controller->setPlayerLed = NULL;
    controller->rumble = controllerRumble_steam2026;
    controller->data = controllerData_steam2026;
    controller->deinit = controllerDeinit_steam2026;
    controller->update = NULL;

    controller->battery = 4;
    controller->isCharging = 0;

    controller->type = BLOOPAIR_CONTROLLER_STEAM2026;
    Configuration_GetAll(controller->type, controller->bda, &controller->commonConfig, &controller->mapping,
                         &controller->customConfig, &controller->customConfigSize);
}

void controllerModuleInit_steam2026(void)
{
    Configuration_SetFallback(BLOOPAIR_CONTROLLER_STEAM2026, NULL, &default_steam2026_mapping, NULL, 0);
}
