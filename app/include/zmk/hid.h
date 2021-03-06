#pragma once

#include <usb/usb_device.h>
#include <usb/class/usb_hid.h>

#include <dt-bindings/zmk/keys.h>

#include <zmk/keys.h>

#define COLLECTION_REPORT 0x03

#define ZMK_HID_MAX_KEYCODE KC_APP

static const u8_t zmk_hid_report_desc[] = {
    /* USAGE_PAGE (Generic Desktop) */
    HID_GI_USAGE_PAGE,
    USAGE_GEN_DESKTOP,
    /* USAGE (Keyboard) */
    HID_LI_USAGE,
    USAGE_GEN_DESKTOP_KEYBOARD,
    /* COLLECTION (Application) */
    HID_MI_COLLECTION,
    COLLECTION_APPLICATION,
    /* REPORT ID (1) */
    HID_GI_REPORT_ID,
    0x01,
    /* USAGE_PAGE (Keypad) */
    HID_GI_USAGE_PAGE,
    USAGE_GEN_DESKTOP_KEYPAD,
    /* USAGE_MINIMUM (Keyboard LeftControl) */
    HID_LI_USAGE_MIN(1),
    0xE0,
    /* USAGE_MAXIMUM (Keyboard Right GUI) */
    HID_LI_USAGE_MAX(1),
    0xE7,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1),
    0x00,
    /* LOGICAL_MAXIMUM (1) */
    HID_GI_LOGICAL_MAX(1),
    0x01,

    /* REPORT_SIZE (1) */
    HID_GI_REPORT_SIZE,
    0x01,
    /* REPORT_COUNT (8) */
    HID_GI_REPORT_COUNT,
    0x08,
    /* INPUT (Data,Var,Abs) */
    HID_MI_INPUT,
    0x02,

    /* USAGE_PAGE (Keypad) */
    HID_GI_USAGE_PAGE,
    USAGE_GEN_DESKTOP_KEYPAD,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1),
    0x00,
    /* LOGICAL_MAXIMUM (1) */
    HID_GI_LOGICAL_MAX(1),
    0x01,
    /* USAGE_MINIMUM (Reserved) */
    HID_LI_USAGE_MIN(1),
    0x00,
    /* USAGE_MAXIMUM (Keyboard Application) */
    HID_LI_USAGE_MAX(1),
    ZMK_HID_MAX_KEYCODE,
    /* REPORT_SIZE (8) */
    HID_GI_REPORT_SIZE,
    0x01,
    /* REPORT_COUNT (6) */
    HID_GI_REPORT_COUNT,
    ZMK_HID_MAX_KEYCODE + 1,
    /* INPUT (Data,Ary,Abs) */
    HID_MI_INPUT,
    0x02,
    /* USAGE_PAGE (Keypad) */
    HID_GI_USAGE_PAGE,
    USAGE_GEN_DESKTOP_KEYPAD,
    /* REPORT_SIZE (8) */
    HID_GI_REPORT_SIZE,
    0x02,
    /* REPORT_COUNT (6) */
    HID_GI_REPORT_COUNT,
    0x01,
    /* INPUT (Cnst,Var,Abs) */
    HID_MI_INPUT,
    0x03,
    /* END_COLLECTION */
    HID_MI_COLLECTION_END,
    /* USAGE_PAGE (Consumer) */
    HID_GI_USAGE_PAGE,
    0x0C,
    /* USAGE (Consumer Control) */
    HID_LI_USAGE,
    0x01,
    /* Consumer Page */
    HID_MI_COLLECTION,
    COLLECTION_APPLICATION,
    /* REPORT ID (1) */
    HID_GI_REPORT_ID,
    0x02,
    /* USAGE_PAGE (Consumer) */
    HID_GI_USAGE_PAGE,
    0x0C,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1),
    0x00,
    /* LOGICAL_MAXIMUM (1) */
    HID_GI_LOGICAL_MAX(1),
    0x01,
    /* USAGE (Scan Next Track) */
    HID_LI_USAGE,
    0xB5,
    /* USAGE (Scan Previous Track) */
    HID_LI_USAGE,
    0xB6,
    /* USAGE (Stop) */
    HID_LI_USAGE,
    0xB7,
    /* USAGE (Eject) */
    HID_LI_USAGE,
    0xB8,
    /* USAGE (Media Play/Pause) */
    HID_LI_USAGE,
    0xCD,
    /* USAGE (Mute) */
    HID_LI_USAGE,
    0xE2,
    /* USAGE (Volume Increment) */
    HID_LI_USAGE,
    0xE9,
    /* USAGE (Volume Decrement) */
    HID_LI_USAGE,
    0xEA,
    /* INPUT (Data,Ary,Abs) */
    /* REPORT_SIZE (1) */
    HID_GI_REPORT_SIZE,
    0x01,
    /* REPORT_COUNT (8) */
    HID_GI_REPORT_COUNT,
    0x08,
    HID_MI_INPUT,
    0x02,
    /* END COLLECTION */
    HID_MI_COLLECTION_END,
};

// struct zmk_hid_boot_report
// {
//     u8_t modifiers;
//     u8_t _unused;
//     u8_t keys[6];
// } __packed;

struct zmk_hid_keypad_report_body
{
    zmk_mod_flags modifiers;
    u8_t keys[13];
} __packed;

struct zmk_hid_keypad_report
{
    u8_t report_id;
    struct zmk_hid_keypad_report_body body;
} __packed;

struct zmk_hid_consumer_report_body
{
    u8_t keys;
} __packed;

struct zmk_hid_consumer_report
{
    u8_t report_id;
    struct zmk_hid_consumer_report_body body;
} __packed;

enum zmk_hid_report_changes
{
    None = 0x00,
    Keypad = (0x01 << 0x00),
    Consumer = (0x01 << 0x01)
};

int zmk_hid_register_mod(zmk_mod modifier);
int zmk_hid_unregister_mod(zmk_mod modifier);
int zmk_hid_register_mods(zmk_mod_flags modifiers);
int zmk_hid_unregister_mods(zmk_mod_flags modifiers);
enum zmk_hid_report_changes zmk_hid_press_key(zmk_key key);
enum zmk_hid_report_changes zmk_hid_release_key(zmk_key key);

struct zmk_hid_keypad_report *zmk_hid_get_keypad_report();
struct zmk_hid_consumer_report *zmk_hid_get_consumer_report();
