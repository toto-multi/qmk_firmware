/* Copyright 2022 toto-03
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
#include "lib/co_touch.h"

enum keymap_layers {
  _ENG_,
  _JPN_,
  _SYM_,
  _CMD_,
};

// Special key codes for shorthand
#define   ___ENG_   TO(_ENG_)
#define   ___JPN_   TO(_JPN_)
#define   ___SYM_   TO(_SYM_)
#define   ___CMD_   TO(_CMD_)
#define   ___T_L1   LM(___ENG_, MOD_LGUI)
#define   ___T_L2   LT(_CMD_, KC_TAB)
#define   ___T_L3   SFT_T(KC_SPC)
#define   ___T_L4   LM(___ENG_, MOD_LCTL)
#define   ___T_R4   LM(___ENG_, MOD_LCTL)
#define   ___T_R3   SFT_T(KC_BSPC)
#define   ___T_R2   LT(_SYM_, KC_ENT)
#define   ___T_R1   LM(___ENG_, MOD_RALT)
#define   ___COMM   CTL_T(KC_COMM)
#define   ___DOT_   CTL_T(KC_DOT)
#define   _C_PGUP   C(KC_PGUP)
#define   _C_PGDN   C(KC_PGDN)
#define   _A_F1__   A(KC_F1)
#define   _A_F2__   A(KC_F2)
#define   _A_F3__   A(KC_F3)
#define   _A_F4__   A(KC_F4)
#define   _A_F5__   A(KC_F5)
#define   _A_F6__   A(KC_F6)
#define   _A_F7__   A(KC_F7)
#define   _A_F8__   A(KC_F8)
#define   _A_F9__   A(KC_F9)
#define   ___CUT_   C(KC_X)         // 切り取り
#define   ___COPY   C(KC_C)         // コピー
#define   ___PSTE   C(KC_V)         // 貼り付け
#define   ___ALL_   C(KC_A)         // 全選択
#define   ___SAVE   C(KC_S)         // 保存
#define   ___CLSE   C(KC_W)         // 閉じる
#define   ___QUIT   C(KC_Q)         // 終了
#define   ___ADRS   C(KC_L)         // アドレス欄に移動
#define   ___COUT   C(KC_SLSH)      // コメントアウト
#define   ___UNDO   C(KC_Z)         // 元に戻す
#define   ___REDO   S(C(KC_Z))      // やり直す
#define   ___CPHS   A(C(KC_V))      // コピー履歴
#define   ___CPCM   A(C(KC_C))      // コピーコマンド

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_ENG_] = LAYOUT(
    XXXXXXX,  KC_U   ,  KC_I   ,  XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_S   ,  KC_R   ,  XXXXXXX,
    KC_Q   ,  KC_A   ,  ___COMM,  KC_F   ,  KC_Z   , XXXXXXX,     XXXXXXX,  JP_COLN,  KC_V   ,  ___DOT_,  KC_N   ,  JP_SCLN,
    KC_G   ,  KC_L   ,  KC_M   ,  KC_E   ,  KC_O   , XXXXXXX,     XXXXXXX,  KC_C   ,  KC_T   ,  KC_P   ,  KC_Y   ,  KC_J   ,
    KC_B   ,  KC_2   ,  KC_1   ,  KC_H   ,  KC_W   , XXXXXXX,     XXXXXXX,  KC_X   ,  KC_D   ,  KC_6   ,  KC_5   ,  KC_K   ,
    KC_3   ,  XXXXXXX,  XXXXXXX,  KC_0   ,  KC_9   , ___ENG_,     ___JPN_,  KC_8   ,  KC_7   ,  XXXXXXX,  XXXXXXX,  KC_4   ,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  ___T_L2, ___T_L3,     ___T_R3,  ___T_R2,  ___T_R1,  XXXXXXX,  ___T_R4,  XXXXXXX
  ),

  [_JPN_] = LAYOUT(
    _______,  CT_01  ,  CT_02  ,  _______,  _______, _______,     _______,  _______,  _______,  CT_07  ,  CT_08  ,  _______,
    CT_00  ,  CT_11  ,  CT_12  ,  CT_03  ,  CT_04  , _______,     _______,  CT_05  ,  CT_06  ,  CT_17  ,  CT_18  ,  CT_09  ,
    CT_10  ,  CT_21  ,  CT_22  ,  CT_13  ,  CT_14  , _______,     _______,  CT_15  ,  CT_16  ,  CT_27  ,  CT_28  ,  CT_19  ,
    CT_20  ,  _______,  _______,  CT_23  ,  CT_24  , _______,     _______,  CT_25  ,  CT_26  ,  _______,  _______,  CT_29  ,
    _______,  _______,  _______,  _______,  _______, _______,     _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______, _______,     _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_SYM_] = LAYOUT(
    _______,  JP_DQUO,  JP_QUOT,  _______,  _______, _______,     _______,  _______,  _______,  JP_MINS,  JP_ASTR,  _______,
    JP_GRV ,  JP_LPRN,  JP_QUES,  JP_AT  ,  JP_CIRC, _______,     _______,  JP_COLN,  JP_UNDS,  JP_EXLM,  JP_EQL ,  JP_SCLN,
    JP_LBRC,  JP_RPRN,  JP_HASH,  JP_LCBR,  JP_LABK, _______,     _______,  JP_AMPR,  JP_SLSH,  JP_PERC,  JP_DLR ,  JP_BSLS,
    JP_RBRC,  _______,  _______,  JP_RCBR,  JP_RABK, _______,     _______,  JP_PIPE,  JP_PLUS,  _______,  _______,  JP_TILD,
    _______,  _______,  _______,  _______,  _______, _______,     _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _C_PGUP, _C_PGDN,     _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_CMD_] = LAYOUT(
    _______,  ___UNDO,  KC_BTN2,  _______,  _______, _______,     _______,  _______,  _______,  ___CPCM,  _A_F7__,  _______,
    CT_PSWD,  ___ALL_,  KC_BTN1,  KC_F2  ,  ___ADRS, _______,     _______,  _A_F1__,  _A_F2__,  ___CPHS,  _A_F3__,  _A_F8__,
    KC_APP ,  KC_LEFT,  KC_RGHT,  KC_UP  ,  KC_PGUP, _______,     _______,  _A_F6__,  ___COUT,  ___PSTE,  ___COPY,  _______,
    KC_PSCR,  KC_F2  ,  KC_F1  ,  KC_DOWN,  KC_PGDN, _______,     _______,  _A_F9__,  ___CUT_,  KC_F6  ,  KC_F5  ,  KC_PSCR,
    KC_F3  ,  _______,  _______,  KC_F10 ,  KC_F9  , _______,     _______,  KC_F8  ,  KC_F7  ,  _______,  _______,  KC_F4  ,
    _______,  _______,  _______,  _______,  _______, _______,     KC_DEL ,  CT_ESC ,  ___SAVE,  _______,  _______,  _______
  ),
};

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM rgb_layer_eng[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 12, HSV_BLUE}
);
const rgblight_segment_t PROGMEM rgb_layer_jpn[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 12, HSV_GREEN}
);
const rgblight_segment_t PROGMEM rgb_layer_sym[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 12, HSV_RED}
);
const rgblight_segment_t PROGMEM rgb_layer_fnc[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 12, HSV_YELLOW}
);
const rgblight_segment_t* PROGMEM const rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  rgb_layer_eng,
  rgb_layer_jpn,
  rgb_layer_sym,
  rgb_layer_fnc
);
#endif

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  rgblight_layers = rgb_layers;
  #endif

  #ifdef CONSOLE_ENABLE
  debug_enable = true;
  debug_matrix = true;
  #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _ENG_:
      tap_code16(KC_LANG2);
      break;
    case _JPN_:
      tap_code16(KC_LANG1);
      break;
    default:
      break;
  }
  #ifdef RGBLIGHT_ENABLE
  rgblight_set_layer_state(_ENG_, layer_state_cmp(state, _ENG_));
  rgblight_set_layer_state(_JPN_, layer_state_cmp(state, _JPN_));
  rgblight_set_layer_state(_SYM_, layer_state_cmp(state, _SYM_));
  rgblight_set_layer_state(_CMD_, layer_state_cmp(state, _CMD_));
  #endif
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if ( record->event.pressed ) {
    // Nothing To Do
  } else {
    switch (keycode) {
      case CT_PSWD:
        layer_off(_JPN_);
        layer_on(_ENG_);
        return false;
      case CT_ESC:
        layer_off(_JPN_);
        layer_on(_ENG_);
        tap_code16(KC_ESC);
        return false;
    }
  }

  // 日本語
  if (get_highest_layer(layer_state) == _JPN_) {
    return process_cotouch(keycode, record);
  }
  return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  dprintf("pointing_device_task_user()¥n");
  return mouse_report;
}
