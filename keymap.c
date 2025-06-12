/* Copyright 2015-2023 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 #include QMK_KEYBOARD_H
#include "timer.h"

static bool lshift_tap = false;
static bool rshift_tap = false;
static uint16_t lshift_timer = 0;
static uint16_t rshift_timer = 0;

 enum planck_layers { _QWERTY, _SYMB, _SYMB_SHIFT, _NAV, _FN, _NO, _MAC_QUERTY, _MAC_SYMB, _MAC_SYMB_SHIFT, _MAC_NAV, _MAC_FN, _MAC_NO };

 enum planck_keycodes { PLOVER = SAFE_RANGE, BACKLIT, EXT_PLV };

 #define LOWER MO(_LOWER)
 #define RAISE MO(_RAISE)

 // #define QWERTY PDF(_QWERTY)
 // #define COLEMAK PDF(_COLEMAK)
 // #define DVORAK PDF(_DVORAK)

 /* clang-format off */
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

     /* QUERTY */
     [0] = LAYOUT_planck_1x2uC(
         KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,        KC_T,     KC_Y,    KC_U,       KC_I,     KC_O,    KC_P,     KC_LBRC,
         KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,        KC_G,     KC_H,    KC_J,       KC_K,     KC_L,    KC_SCLN,  KC_QUOT,
         KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,        KC_B,     KC_N,    KC_M,       KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
         MO(_FN),   KC_LCTL, KC_LGUI, KC_LALT, MO(_SYMB),   KC_SPC,            MO(_NAV),   KC_BSPC,  KC_ENT,  KC_RCTL,   MO(_FN)
     ),

     /* Symbols */
     [_SYMB] = LAYOUT_planck_1x2uC(
         KC_ESC,            KC_EXLM, KC_7,    KC_8,    KC_9,    KC_NO,          LSFT(KC_EQL),  KC_AMPR,    KC_EQL,        KC_NUBS,        KC_RPRN,   LSFT(KC_MINS),
         KC_TAB,            KC_HASH, KC_4,    KC_5,    KC_6,    LSFT(KC_RBRC),  RALT(KC_2),    KC_ASTR,    RALT(KC_8),    RALT(KC_7),     KC_AT,     KC_NUHS,
         MO(_SYMB_SHIFT),   KC_0,    KC_1,    KC_2,    KC_3,    RALT(KC_4),     LSFT(KC_6),    KC_PERC,    RALT(KC_RBRC), LSFT(KC_NUHS),  KC_MINS,   MO(_SYMB_SHIFT),
         KC_NO,             KC_LCTL, KC_LGUI, KC_LALT, KC_TRNS, KC_SPC,                        KC_NO,      KC_DEL,        KC_NO,          KC_NO,     KC_NO
     ),

     /* Symbols SHIFTED */
     [_SYMB_SHIFT] = LAYOUT_planck_1x2uC(
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   RALT(KC_EQL), KC_TRNS, KC_GRV,     LSFT(KC_NUBS), KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,      KC_LPRN, RALT(KC_9), RALT(KC_0),    KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,      KC_TRNS, KC_TRNS,    KC_TRNS,       KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS,    LSFT(KC_DEL),  KC_TRNS, KC_TRNS
     ),

     /* Mouse and arrow keys */
     [_NAV] = LAYOUT_planck_1x2uC(
         KC_ESC,    KC_BTN5,   KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_WH_U,   KC_NO,   KC_HOME,   KC_UP,     KC_END,    KC_PGUP,   KC_PAUS,
         KC_TAB,    KC_BTN4,   KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_WH_D,   KC_NO,   KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_PGDN,   KC_NO,
         KC_LSFT,   KC_NO,     KC_NO,     KC_NO,     KC_WH_L,   KC_WH_R,   KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_RSFT,
         KC_NO,     KC_LCTL,   KC_LGUI,   KC_LALT,   KC_NO,     KC_SPC,             KC_TRNS,   KC_BSPC,   KC_ENT,    KC_RCTL,   KC_NO
     ),

     /* Function keys */
     [_FN] = LAYOUT_planck_1x2uC(
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
         KC_NO,   KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,            MI_ON,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_LSFT, KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_TRNS, KC_LCTL, KC_LGUI, KC_LALT, KC_NO,   TG(_MAC_QUERTY),           KC_NO,   KC_BSPC, KC_ENT,  KC_RCTL, KC_TRNS
     ),

     /* Empty */
     [_NO] = LAYOUT_planck_1x2uC(
         KC_ESC,  RGB_TOG, RGB_M_P, KC_NO,    KC_NO,    KC_NO,   KC_NO,   RGB_VAI, RGB_HUI, RGB_SAI,  RGB_SPI,  RGB_MOD,
         KC_TAB,  RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_NO,   KC_NO,   RGB_VAD, RGB_HUD, RGB_SAD,  RGB_SPD,  RGB_RMOD,
         KC_LSFT, RGB_M_K, RGB_M_X, RGB_M_G,  RGB_M_T,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_RSFT,
         KC_TRNS, KC_LCTL, KC_LGUI, KC_LALT,  KC_TRNS,  KC_NO,            KC_NO,   KC_BSPC, KC_ENT,   KC_RCTL,  KC_NO
     ),

     /* MAC QUERTY */
     [_MAC_QUERTY] = LAYOUT_planck_1x2uC(
         KC_ESC,      KC_Q,    KC_W,    KC_E,    KC_R,           KC_T,   KC_Y,    KC_U,          KC_I,    KC_O,    KC_P,    KC_LBRC,
         KC_TAB,      KC_A,    KC_S,    KC_D,    KC_F,           KC_G,   KC_H,    KC_J,          KC_K,    KC_L,    KC_SCLN, KC_QUOT,
         KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,           KC_B,   KC_N,    KC_M,          KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
         MO(_MAC_FN), KC_LCTL, KC_LALT, KC_LGUI, MO(_MAC_SYMB),  KC_SPC,          MO(_MAC_NAV),  KC_BSPC, KC_ENT,  KC_LGUI, MO(_MAC_FN)
     ),

     /* MAC Symbols */
     [_MAC_SYMB] = LAYOUT_planck_1x2uC(
         KC_ESC,               KC_EXLM, KC_7,    KC_8,    KC_9,    KC_NO,          LSFT(KC_EQL),  KC_AMPR, LSFT(RALT(KC_7)), KC_NUBS,           KC_RPRN, LSFT(KC_MINS),
         KC_TAB,               KC_HASH, KC_4,    KC_5,    KC_6,    LSFT(KC_RBRC),  KC_NUHS,       KC_ASTR, RALT(KC_8),       LSFT(RALT(KC_8)),  KC_AT,   KC_GRV,
         MO(_MAC_SYMB_SHIFT),  KC_0,    KC_1,    KC_2,    KC_3,    LSFT(KC_4),     LSFT(KC_6),    KC_PERC, RALT(KC_RBRC),    LSFT(KC_NUHS),     KC_MINS, MO(_MAC_SYMB_SHIFT),
         KC_NO,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,                        KC_NO,   KC_DEL,           KC_NO,             KC_NO,   KC_NO
     ),

     /* MAC Symbols SHIFTED */
     [_MAC_SYMB_SHIFT] = LAYOUT_planck_1x2uC(
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_EQL,    KC_TRNS, RALT(KC_7), LSFT(KC_NUBS),    KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_LPRN, RALT(KC_9), LSFT(RALT(KC_9)), KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS,          KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS,    LSFT(KC_DEL),     KC_TRNS, KC_TRNS
     ),

     /* MAC Mouse and arrow keys */
     [_MAC_NAV] = LAYOUT_planck_1x2uC(
         KC_ESC,  KC_BTN5, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,   KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_NO,
         KC_TAB,  KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO,
         KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_WH_R, KC_WH_L,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT,
         KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_SPC,             KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_NO
     ),

     /* MAC Function keys */
     [_MAC_FN] = LAYOUT_planck_1x2uC(
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
         KC_NO,   KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,         MI_ON,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_LSFT, KC_BRID, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   TG(_QWERTY),            KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),

     /* Empty */
     [_MAC_NO] = LAYOUT_planck_1x2uC(
         KC_ESC,  RGB_TOG, RGB_M_P, KC_NO,    KC_NO,    KC_NO,   KC_NO,   RGB_VAI, RGB_HUI, RGB_SAI,  RGB_SPI,  RGB_MOD,
         KC_TAB,  RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_NO,   KC_NO,   RGB_VAD, RGB_HUD, RGB_SAD,  RGB_SPD,  RGB_RMOD,
         KC_LSFT, RGB_M_K, RGB_M_X, RGB_M_G,  RGB_M_T,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_RSFT,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_NO,            KC_NO,   KC_TRNS, KC_TRNS,  KC_TRNS,  KC_NO
     )
 };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LSFT) {
        if (record->event.pressed) {
            lshift_timer = timer_read();
        } else {
            lshift_tap = timer_elapsed(lshift_timer) < 200;
            if (lshift_tap && rshift_tap && timer_elapsed(rshift_timer) < 200) {
                tap_code(KC_CAPS);
                lshift_tap = false;
                rshift_tap = false;
            }
        }
    }

    if (keycode == KC_RSFT) {
        if (record->event.pressed) {
            rshift_timer = timer_read();
        } else {
            rshift_tap = timer_elapsed(rshift_timer) < 200;
            if (lshift_tap && rshift_tap && timer_elapsed(lshift_timer) < 200) {
                tap_code(KC_CAPS);
                lshift_tap = false;
                rshift_tap = false;
            }
        }
    }

    return true;
}
