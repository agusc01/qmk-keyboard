/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keycode_aliases.h"
#include "config.h"
#include <stdio.h>      

enum corne_layers { 
    _QWERTY,
    _NAVIGATE,
    _SYMBOLS,
    _NUMPAD_F
};

enum custom_keycodes {
   SW_GUI = SAFE_RANGE
};

bool state_GUI=false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
    //.-----------------------------------------------------.                    .-----------------------------------------------------.
LT_NUMPAD_ESCAPE,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_LBRC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_RSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,KC_COMMA,  KC_DOT,KC_SLASH, KC_LSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI,KC_SPACE,NAVIGATE,    SYMBOLS,KC_ENTER, KC_LCTL
                                        //`--------------------------´  `--------------------------'
  ),

  [_NAVIGATE] = LAYOUT_split_3x6_3(
    //.-----------------------------------------------------.                    .-----------------------------------------------------.
      KC_ESCAPE, XXXXXXX,ICOMILLA,SCOMILLA,DCOMILLA,    REDO,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, XXXXXXX, XXXXXXX, KC_LCTL, KC_LSFT, KC_LGUI,                    KC_PGDOWN, KC_LEFT, KC_DOWN,KC_RIGHT, KC_LALT,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______,    UNDO,     CUT,    COPY,   PASTE, XXXXXXX,                      KC_CAPS, KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, XXXXXXX,    XXXXXXX, _______, _______
                                        //`--------------------------´  `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
    //.-----------------------------------------------------.                    .-----------------------------------------------------.
        KC_GRV ,    KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,   KC_P0, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______,   SLASH,  BSLASH, OCURLYB, CCURLYB,  OEXCLA,                      OINTERR, OROUNDB, CROUNDB, OANGLEB, CANGLEB,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______,CIRCUNFL,VIRGULIL,OSQUAREB,CSQUAREB,  CEXCLA,                      CINTERR,DCOMILLA,SCOMILLA,ICOMILLA, XXXXXXX, KC_LSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, XXXXXXX,    XXXXXXX, _______, _______
                                        //`--------------------------´  `--------------------------'
  ),

  [_NUMPAD_F] = LAYOUT_split_3x6_3(
    //.-----------------------------------------------------.                    .-----------------------------------------------------.
        XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,TERMINAL,                      KC_PPLS,   KC_P7,   KC_P8,   KC_P9, KC_PMNS, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______,   KC_F8,   KC_F7,   KC_F6,   KC_F5,  SW_GUI,                      KC_PAST,   KC_P4,   KC_P5,   KC_P6, KC_PSLS,  EQUALS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_LALT,                      KC_COMM,   KC_P1,   KC_P2,   KC_P3,   KC_P0, KC_PDOT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, XXXXXXX,    XXXXXXX, _______, _______
                                        //`--------------------------´  `--------------------------'
  )

};

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;  
}

void oled_render_master(void) {
    oled_set_cursor(0,0);
    oled_write_P(PSTR("QWERT\n"), layer_state_is(_QWERTY) );
    oled_write_P(PSTR("NAVIG\n"), layer_state_is(_NAVIGATE));
    oled_write_P(PSTR("SYMBO\n"), layer_state_is(_SYMBOLS));
    oled_write_P(PSTR("NUMPA\n"), layer_state_is(_NUMPAD_F));
    oled_write_P(host_keyboard_led_state().caps_lock ? PSTR("CAP  \n") : PSTR("     \n"), false);
    oled_write_P(state_GUI ? PSTR("W>ON ") : PSTR("W>OFF") , false);
}
void oled_render_sclave(void) {
    oled_set_cursor(0,0);
    oled_write_P(PSTR("\nIT'S \nWORK!\n"), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_master();
    }
    else {
        oled_render_sclave();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case SW_GUI:
            if(record->event.pressed) {
                if(state_GUI) {      
                    process_magic(GUI_OFF, record);
                    state_GUI = false;
                }
                else {
                    process_magic(GUI_ON, record);
                    state_GUI = true;
                }
            }
            break;
        default:
            break;
    }
    return true;
}

#endif // #ifdef OLED_DRIVER_ENABLE