
#pragma once
#include <controllers.h>

// Info about the reports can be found here:
// - <https://github.com/atar-axis/xpadneo/blob/master/hid-xpadneo/src/hid-xpadneo.c>
// - <https://github.com/atar-axis/xpadneo/blob/master/hid-xpadneo/src/xpadneo.h>
// - <https://github.com/libsdl-org/SDL/blob/d8c0bd465ec20b93130de42a031013668d37fa79/src/joystick/hidapi/SDL_hidapi_steam_triton.c>
// - <https://github.com/torvalds/linux/blob/8a36f53fd5ec3eff01f1b637d42cbdc3821d0493/drivers/hid/hid-steam.c>/*

#define REPORT_INPUT                  0x42
#define REPORT_INPUT_BLE              0x45
#define REPORT_WIRELESS_STATUS_X      0x46
#define REPORT_WIRELESS_STATUS        0x79
#define HID_FEATURE_REPORT_BYTES      64
#define ID_SET_SETTINGS_VALUES        0x87
#define SETTING_LIZARD_MODE           0x09
#define LIZARD_MODE_OFF               0x00
#define SETTING_STEAM_WATCHDOG_ENABLE 0x47
#define WATCHDOG_DISABLE              0x00
#define ID_OUT_REPORT_HAPTIC_RUMBLE   0x80
#define HID_RUMBLE_OUTPUT_REPORT_BYTES 10

typedef struct PACKED {
    uint8_t report_id;
    uint8_t seq_num;

    struct PACKED {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t x : 1;
        uint8_t y : 1;
        uint8_t quickaccess : 1;
        uint8_t rstick : 1;
        uint8_t menu : 1;
        uint8_t r4 : 1;

        uint8_t r5 : 1;
        uint8_t r1 : 1;
        uint8_t dpad_down : 1;
        uint8_t dpad_right : 1;
        uint8_t dpad_left : 1;
        uint8_t dpad_up : 1;
        uint8_t view : 1;
        uint8_t lstick : 1;

        uint8_t steam : 1;
        uint8_t l4 : 1;
        uint8_t l5 : 1;
        uint8_t l1 : 1;
        uint8_t rstick_touch : 1;
        uint8_t rpad_touch : 1;
        uint8_t rpad : 1;
        uint8_t r2 : 1;

        uint8_t lstick_touch : 1;
        uint8_t lpad_touch : 1;
        uint8_t lpad : 1;
        uint8_t l2 : 1;
        uint8_t rgrip : 1;
        uint8_t lgrip : 1;
        uint8_t       : 2;
    } buttons;

    short left_trigger;
    short right_trigger;

    short left_stick_x;
    short left_stick_y;
    short right_stick_x;
    short right_stick_y;

    short left_pad_x;
    short left_pad_y;
    unsigned short left_pad_pressure;
    short right_pad_x;
    short right_pad_y;
    unsigned short right_pad_pressure;

    struct PACKED {
        uint32_t timestamp;
        short sAccelX;
        short sAccelY;
        short sAccelZ;

        short sGyroX;
        short sGyroY;
        short sGyroZ;
    } imu;
} Steam2026InputReport;
CHECK_SIZE(Steam2026InputReport, 46);

// TODO: Rumble report info