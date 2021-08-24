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
#include <stdio.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESCAPE,  KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  LCTL_T(KC_TAB),    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,   KC_S,  KC_MINS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 LSFT_T(KC_BSLS), KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,  RSFT_T(KC_SLSH),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LGUI,LT(1,KC_ENTER),LT(2,KC_SPACE),   KC_SPACE,LT(3,KC_ENTER), KC_LALT
                                    //`--------------------------'  `--------------------------'
                                        //L_NAVIGATE   // L_NUMPAD_F                //L_SYMBOLS               
  ),

  //L_NAVIGATE
  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_ESCAPE, XXXXXXX, XXXXXXX, XXXXXXX,KC_F4, LCA(KC_DEL),                     KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,LCTL(KC_Y), KC_LCTL, KC_LSFT, KC_LGUI, XXXXXXX,                   KC_PGDOWN, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______,LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),XXXXXXX,                 KC_CAPS, KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_ENTER,KC_SPACE,   KC_SPACE, KC_ENTER, KC_LALT
                                      //`--------------------------'  `--------------------------'
// MY_UNDO  "LCTL(KC_Z)"
// MY_REDO  "LCTL(KC_Y)"
// MY_CUT   "LCTL(KC_X)"
// MY_COPY  "LCTL(KC_C)"
// MY_PASTE "LCTL(KC_V)"
  ),

  //L_NUMPAD_F
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_ESCAPE,   KC_F1,   KC_F2,   KC_F3,   KC_F4, GUI_OFF,                      KC_PPLS,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  GUI_ON,                      KC_PAST,    KC_4,    KC_5,    KC_6, KC_SLSH,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,                      KC_COMM,    KC_1,    KC_2,    KC_3,    KC_0, KC_PDOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_ENTER,KC_SPACE,   KC_SPACE, KC_ENTER, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

  //L_SYMBOLS
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_PIPE, KC_EXLM,   KC_AT, KC_LPRN, KC_RPRN, KC_HASH,                      KC_PERC, KC_SLSH, KC_BSLS, KC_EQL, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,KC_MINUS, KC_UNDS, KC_LCBR, KC_RCBR, KC_TILD,                      KC_AMPR,   KC_LT,   KC_GT, XXXXXXX, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC,  KC_DLR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RSFT_T(KC_SLSH),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_ENTER,KC_SPACE,   KC_SPACE, KC_ENTER, KC_LALT
                                      //`--------------------------'  `--------------------------'
  )


};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_DVORAK   0
#define L_NAVIGATE 2
#define L_NUMPAD_F 4
#define L_SYMBOLS  8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_DVORAK:
            oled_write_ln_P(PSTR("DVORAK"), false);
            break;
        case L_NAVIGATE:
            oled_write_ln_P(PSTR("NAVIGATE 111"), false);
            break;
        case L_NUMPAD_F:
            oled_write_ln_P(PSTR("NUMPAD_F 222"), false);
            break;
        case L_SYMBOLS:
        case L_SYMBOLS|L_NAVIGATE:
        case L_SYMBOLS|L_NUMPAD_F:
        case L_SYMBOLS|L_NAVIGATE|L_NUMPAD_F:
            oled_write_ln_P(PSTR("SYMBOLS 333"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
