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
         KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,        KC_T,   KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_LBRC,
         KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,        KC_G,   KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
         KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,        KC_B,   KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
         MO(_FN),   KC_LCTL, KC_LGUI, KC_LALT, MO(_SYMB),   KC_SPC,          MO(_NAV),   KC_BSPC, KC_ENT,  KC_RCTL, MO(_FN)
     ),
 
     /* Symbols */
     [_SYMB] = LAYOUT_planck_1x2uC(
         KC_ESC,            KC_EXLM, KC_P7,   KC_P8,   KC_P9,   KC_NO,          LSFT(KC_EQL),  KC_AMPR,        KC_EQL,        KC_NUBS,         KC_RPRN,       LSFT(KC_MINS),
         KC_TAB,            KC_HASH, KC_P4,   KC_P5,   KC_P6,   LSFT(KC_RBRC),  RALT(KC_2),    KC_ASTR,        RALT(KC_8),    RALT(KC_7),      KC_AT,         KC_NUHS,
         MO(_SYMB_SHIFT),   KC_P0,   KC_P1,   KC_P2,   KC_P3,   RALT(KC_4),     KC_NO,         KC_PERC,        RALT(KC_RBRC), LSFT(KC_NUHS),   KC_MINS,       MO(_SYMB_SHIFT),
         KC_NO,             KC_LCTL, KC_LGUI, KC_LALT, KC_TRNS, KC_SPC,                        KC_NO,          KC_DEL,        KC_NO,           KC_NO,         KC_NO
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
         KC_ESC,  KC_BTN5, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,   KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PAUS,
         KC_TAB,  KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO,
         KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_WH_L, KC_WH_R,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT,
         KC_NO,   KC_LCTL, KC_LGUI, KC_LALT, KC_NO,   KC_SPC,             KC_TRNS, KC_BSPC, KC_ENT,  KC_RCTL, KC_NO
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
         KC_ESC,               KC_EXLM, KC_P7,   KC_P8,   KC_P9,   KC_NO,          LSFT(KC_EQL),  KC_AMPR, LSFT(RALT(KC_7)), KC_NUBS,           KC_RPRN, LSFT(KC_MINS),
         KC_TAB,               KC_HASH, KC_P4,   KC_P5,   KC_P6,   LSFT(KC_RBRC),  KC_NUHS,       KC_ASTR, RALT(KC_8),       LSFT(RALT(KC_8)),  KC_AT,   KC_GRV,
         MO(_MAC_SYMB_SHIFT),  KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_NO,          KC_NO,         KC_PERC, RALT(KC_RBRC),    LSFT(KC_NUHS),     KC_MINS, MO(_MAC_SYMB_SHIFT),
         KC_NO,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,                        KC_NO,   KC_DEL,           KC_NO,             KC_NO,   KC_NO
     ),
 
     /* MAC Symbols SHIFTED */
     [_MAC_SYMB_SHIFT] = LAYOUT_planck_1x2uC(
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   RALT(KC_EQL), KC_TRNS, RALT(KC_7), LSFT(KC_NUBS),    KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,      KC_LPRN, RALT(KC_9), LSFT(RALT(KC_9)), KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,      KC_TRNS, KC_TRNS,    KC_TRNS,          KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS,    LSFT(KC_DEL),     KC_TRNS, KC_TRNS
     ),
 
     /* MAC Mouse and arrow keys */
     [_MAC_NAV] = LAYOUT_planck_1x2uC(
         KC_ESC,  KC_BTN5, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_D,   KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_NO,
         KC_TAB,  KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO,
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
 
//  #ifdef ENCODER_MAP_ENABLE
//  /* Rotary Encoders
//   */
//  const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//      /* Qwerty
//       *    v- (index) Clockwise / Counter Clockwise                        v- (index) Clockwise / Counter Clockwise
//       * ,---------------------------------------------------------------------------------------.
//       * | (0) Vol-    / Vol+    |   |   |   |   |   |   |   |   |   |   | (4) Vol-    / Vol+    |
//       * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
//       * | (1) KC_MNXT / KC_MPRV |   |   |   |   |   |   |   |   |   |   | (5) KC_MNXT / KC_MPRV |
//       * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
//       * | (2) KC_WBAK / KC_WFWD |   |   |   |   |   |   |   |   |   |   | (6) KC_SPC  / KC_ENT  |
//       * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
//       * | (3) KC_LEFT / KC_RGHT |   |   |   |   |       |   |   |   |   | (7) KC_DOWN / KC_UP   |
//       * `---------------------------------------------------------------------------------------'
//       */
//      [_QWERTY] = {
//          // LEFT SIDE (index 0 to 3)
//          ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
//          ENCODER_CCW_CW(KC_MNXT, KC_MPRV),
//          ENCODER_CCW_CW(KC_WBAK, KC_WFWD),
//          ENCODER_CCW_CW(KC_LEFT, KC_RGHT),
//          // RIGHT SIDE (index 4 to 7)
//          ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
//          ENCODER_CCW_CW(KC_MNXT, KC_MPRV),
//          ENCODER_CCW_CW(KC_SPC,  KC_ENT),
//          ENCODER_CCW_CW(KC_DOWN, KC_UP)
//      },
 
//      /* Adjust (Lower + Raise)
//       *    v- (index) Clockwise / Counter Clockwise                        v- (index) Clockwise / Counter Clockwise
//       * ,---------------------------------------------------------------------------------------.
//       * | (0) _______ / _______ |   |   |   |   |   |   |   |   |   |   | (4) _______ / _______ |
//       * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
//       * | (1) _______ / _______ |   |   |   |   |   |   |   |   |   |   | (5) _______ / _______ |
//       * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
//       * | (2) UG_NEXT / UG_PREV |   |   |   |   |   |   |   |   |   |   | (6) SAT- / SAT+       |
//       * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
//       * | (3) UG_VALD / UG_VALU |   |   |   |   |       |   |   |   |   | (7) HUE- / HUE+       |
//       * `---------------------------------------------------------------------------------------'
//       */
//      [_ADJUST] = {
//          // LEFT SIDE (index 0 to 3)
//          ENCODER_CCW_CW(_______, _______),
//          ENCODER_CCW_CW(_______, _______),
//          ENCODER_CCW_CW(UG_NEXT, UG_PREV),
//          ENCODER_CCW_CW(UG_VALD, UG_VALU),
//          // RIGHT SIDE (index 4 to 7)
//          ENCODER_CCW_CW(_______, _______),
//          ENCODER_CCW_CW(_______, _______),
//          ENCODER_CCW_CW(UG_SATD,  UG_SATU),
//          ENCODER_CCW_CW(UG_HUEU,  UG_HUED)
//      }
//  };
//  #endif
 /* clang-format on */
 
//  #ifdef AUDIO_ENABLE
//  float plover_song[][2]    = SONG(PLOVER_SOUND);
//  float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
//  #endif
 
//  bool play_encoder_melody(uint8_t index, bool clockwise);
 
//  layer_state_t layer_state_set_user(layer_state_t state) {
//      return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
//  }
 
//  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//  #ifdef ENCODER_MAP_ENABLE
//      if (IS_ENCODEREVENT(record->event) && record->event.pressed) {
//          play_encoder_melody(record->event.key.col, record->event.type == ENCODER_CCW_EVENT);
//      }
//  #endif
//      switch (keycode) {
//          case BACKLIT:
//              if (record->event.pressed) {
//                  register_code(KC_RSFT);
//              } else {
//                  unregister_code(KC_RSFT);
//              }
//              return false;
//              break;
//          case PLOVER:
//              if (record->event.pressed) {
//  #ifdef AUDIO_ENABLE
//                  stop_all_notes();
//                  PLAY_SONG(plover_song);
//  #endif
//                  layer_off(_RAISE);
//                  layer_off(_LOWER);
//                  layer_off(_ADJUST);
//                  layer_on(_PLOVER);
//                  if (!eeconfig_is_enabled()) {
//                      eeconfig_init();
//                  }
//                  keymap_config.raw  = eeconfig_read_keymap();
//                  keymap_config.nkro = 1;
//                  eeconfig_update_keymap(keymap_config.raw);
//              }
//              return false;
//              break;
//          case EXT_PLV:
//              if (record->event.pressed) {
//  #ifdef AUDIO_ENABLE
//                  PLAY_SONG(plover_gb_song);
//  #endif
//                  layer_off(_PLOVER);
//              }
//              return false;
//              break;
//      }
//      return true;
//  }
 
//  /* clang-format off */
//  float melody[8][2][2] = {
//      {{440.0f, 8}, {440.0f, 24}},
//      {{440.0f, 8}, {440.0f, 24}},
//      {{440.0f, 8}, {440.0f, 24}},
//      {{440.0f, 8}, {440.0f, 24}},
//      {{440.0f, 8}, {440.0f, 24}},
//      {{440.0f, 8}, {440.0f, 24}},
//      {{440.0f, 8}, {440.0f, 24}},
//      {{440.0f, 8}, {440.0f, 24}},
//  };
//  /* clang-format on */
 
//  #define JUST_MINOR_THIRD 1.2
//  #define JUST_MAJOR_THIRD 1.25
//  #define JUST_PERFECT_FOURTH 1.33333333
//  #define JUST_TRITONE 1.42222222
//  #define JUST_PERFECT_FIFTH 1.33333333
 
//  #define ET12_MINOR_SECOND 1.059463
//  #define ET12_MAJOR_SECOND 1.122462
//  #define ET12_MINOR_THIRD 1.189207
//  #define ET12_MAJOR_THIRD 1.259921
//  #define ET12_PERFECT_FOURTH 1.33484
//  #define ET12_TRITONE 1.414214
//  #define ET12_PERFECT_FIFTH 1.498307
 
//  deferred_token tokens[8];
 
//  uint32_t reset_note(uint32_t trigger_time, void *note) {
//      *(float*)note = 440.0f;
//      return 0;
//  }
 
//  bool play_encoder_melody(uint8_t index, bool clockwise) {
//      cancel_deferred_exec(tokens[index]);
//      if (clockwise) {
//          melody[index][1][0] = melody[index][1][0] * ET12_MINOR_SECOND;
//          melody[index][0][0] = melody[index][1][0] / ET12_PERFECT_FIFTH;
//          audio_play_melody(&melody[index], 2, false);
//      } else {
//          melody[index][1][0] = melody[index][1][0] / ET12_MINOR_SECOND;
//          melody[index][0][0] = melody[index][1][0] * ET12_TRITONE;
//          audio_play_melody(&melody[index], 2, false);
//      }
//      tokens[index] = defer_exec(1000, reset_note, &melody[index][1][0]);
//      return false;
//  }
 
//  bool encoder_update_user(uint8_t index, bool clockwise) {
//      return play_encoder_melody(index, clockwise);
//  }
 
//  bool dip_switch_update_user(uint8_t index, bool active) {
//      switch (index) {
//          case 0: {
//  #ifdef AUDIO_ENABLE
//              static bool play_sound = false;
//  #endif
//              if (active) {
//  #ifdef AUDIO_ENABLE
//                  if (play_sound) {
//                      PLAY_SONG(plover_song);
//                  }
//  #endif
//                  layer_on(_ADJUST);
//              } else {
//  #ifdef AUDIO_ENABLE
//                  if (play_sound) {
//                      PLAY_SONG(plover_gb_song);
//                  }
//  #endif
//                  layer_off(_ADJUST);
//              }
//  #ifdef AUDIO_ENABLE
//              play_sound = true;
//  #endif
//              break;
//          }
//      }
//      return true;
//  }