/* Copyright 2017 Wunder
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
#include "xd75.h"
#include "rgblight.h"
#include <util/delay.h>

// Layer shorthand
#define _QW 0
#define _FN1 1
#define _FN2 2
#define _SCROLL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QW] = { /* QWERTY */
  { KC_GRV,        KC_1,        KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC, KC_DEL },
  { KC_TAB,        KC_Q,        KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS, KC_INS },
  { CTL_T(KC_ESC), KC_A,        KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,  KC_ENT,  KC_HOME },
  { KC_LSFT,       KC_Z,        KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_RSFT, KC_UP,   KC_END },
  { TG(_FN1),      TT(_SCROLL), KC_LALT, KC_LGUI, KC_SPC, KC_SPC, KC_ENT, KC_SPC, KC_SPC,  KC_RGUI, KC_RALT, TG(_FN2), KC_LEFT, KC_DOWN, KC_RGHT },
 },

 [_FN1] = { /* FUNCTION */
  { _______,  KC_F1,       KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  _______, _______ },
  { _______,  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ },
  { _______,  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ },
  { _______,  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ },
  { TG(_FN1), TG(_SCROLL), _______, _______, _______, _______, _______, _______, _______, _______, _______, TG(_FN2), _______, _______, _______ },
 },

 [_FN2] = { /* FUNCTION */
  { _______,  KC_F14,      KC_F15,  _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU, _______, KC_POWER },
  { _______,  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ },
  { _______,  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ },
  { _______,  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ },
  { TG(_FN1), TG(_SCROLL), _______, _______, _______, _______, _______, _______, _______, _______, _______, TG(_FN2), _______, _______, _______ },
 },

 [_SCROLL] = { /* FUNCTION */
  { _______,  _______,     _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ },
  { _______,  _______,     _______, _______,   RESET,   _______, _______, _______, KC_PGUP, _______, _______, _______,  _______, _______, _______ },
  { _______,  _______,     _______, KC_PGDOWN, _______, _______, _______, KC_DOWN, KC_UP,   _______, _______, _______,  _______, _______, _______ },
  { _______,  _______,     _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______ },
  { TG(_FN1), TG(_SCROLL), _______, _______,   _______, _______, _______, _______, _______, _______, _______, TG(_FN2), _______, _______, _______ },
 }
};

const uint16_t PROGMEM fn_actions[] = {

};

void matrix_init_user(void) {
    rgblight_mode(1);
    rgblight_enable();
    rgblight_setrgb(0xFF, 0, 0);
}

void matrix_scan_user(void) {
  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
      case _QW:
        rgblight_setrgb(0, 0, 0);
        break;

      case _FN1:
        rgblight_setrgb(0, 0xFF, 0);
        break;

      case _FN2:
        rgblight_setrgb(0, 0, 0xFF);
        break;

      case _SCROLL:
        rgblight_setrgb(0xFF, 0xFF, 0);
        break;
    }

    old_layer = new_layer;
  }
}
