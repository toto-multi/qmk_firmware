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
#include "lib/keyball.h"

enum keymap_layers {
  _ENG_,
  _JPN_,
  _SYM_,
  _NUM_,
  _CMD_,
};

// Special key codes for shorthand
#define   ___ENG_   TO(_ENG_)
#define   ___JPN_   TO(_JPN_)
#define   ___SYM_   TO(_SYM_)
#define   ___CMD_   TO(_CMD_)
#define   ___NUM_   TO(_NUM)
#define   ___T_L1   LM(___ENG_, MOD_LGUI)
#define   ___T_L2   LT(_CMD_, KC_TAB)
#define   ___T_L3   LT(_NUM_, KC_SPC)
#define   ___T_R3   LT(_SYM_, KC_BSPC)
#define   ___T_R2   SFT_T(KC_ENT)
#define   ___T_R1   ALT_T(KC_ESC)
#define   ___COMM   CTL_T(KC_COMM)
#define   ___DOT_   CTL_T(KC_DOT)
#define   ___MENU   CTL_T(KC_F11)
#define   ___DEL_   SFT_T(KC_DEL)
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
#define   ___SENT   S(KC_ENT)       // Shift + Enter
#define   ___ADD_   C(KC_A)         // 加算
#define   ___MNS_   C(KC_X)         // 減算
#define   ___CUT_   C(KC_X)         // 切り取り
#define   ___COPY   C(KC_C)         // コピー
#define   ___PSTE   C(KC_V)         // 貼り付け
#define   ___ALL_   C(KC_A)         // 全選択
#define   ___SAVE   C(KC_S)         // 保存
#define   ___ADRS   C(KC_L)         // アドレス欄に移動
#define   ___CLOS   C(KC_W)         // 閉じる
#define   ___COUT   C(KC_SLSH)      // コメントアウト
#define   ___UNDO   C(KC_Z)         // 元に戻す
#define   ___REDO   C(S(KC_Z))      // やり直す
#define   ___CPHS   C(S(KC_V))      // コピー履歴
#define   ___CPCM   C(S(KC_C))      // コピーコマンド

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_ENG_] = LAYOUT(
    XXXXXXX,  KC_U   ,  KC_I   ,  XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_S   ,  KC_R   ,  XXXXXXX,
    KC_Q   ,  KC_A   ,  ___COMM,  KC_F   ,  JP_COLN, XXXXXXX,     XXXXXXX,  JP_SCLN,  KC_V   ,  ___DOT_,  KC_N   ,  KC_Z   ,
    KC_G   ,  KC_L   ,  KC_M   ,  KC_E   ,  KC_O   , XXXXXXX,     XXXXXXX,  KC_C   ,  KC_T   ,  KC_P   ,  KC_Y   ,  KC_J   ,
    KC_B   ,  XXXXXXX,  XXXXXXX,  KC_H   ,  KC_W   , XXXXXXX,     XXXXXXX,  KC_X   ,  KC_D   ,  XXXXXXX,  XXXXXXX,  KC_K   ,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, ___ENG_,     ___JPN_,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  ___T_L2, ___T_L3,     ___T_R3,  ___T_R2,  ___T_R1,  XXXXXXX,  XXXXXXX,  XXXXXXX
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
    _______,  KC_F9   ,  KC_F8 ,  _______,  _______, _______,     _______,  _______,  _______,  JP_HASH,  JP_RCBR,  _______,
    KC_F13 ,  KC_F3   ,  KC_F2 ,  KC_F7  ,  KC_F12 , _______,     _______,  JP_GRV ,  JP_LCBR,  JP_QUES,  JP_RPRN,  JP_SCLN,
    KC_F14 ,  KC_F6   ,  KC_F5 ,  KC_F1  ,  KC_F11 , _______,     _______,  JP_QUOT,  JP_LPRN,  JP_AT  ,  JP_RBRC,  JP_TILD,
    KC_F15 ,  _______,  _______,  KC_F4  ,  KC_F10 , _______,     _______,  JP_DQUO,  JP_LBRC,  _______,  _______,  JP_YEN ,
    _______,  _______,  _______,  _______,  _______, _______,     _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _C_PGUP, _C_PGDN,     _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_NUM_] = LAYOUT(
    _______,  JP_LABK,  JP_RABK,  _______,  _______, _______,     _______,  _______,  _______,  KC_8   ,  KC_9   ,  _______,
    JP_AMPR,  JP_EQL ,  JP_EXLM,  JP_SLSH,  JP_COLN, _______,     _______,  KC_C   ,  KC_7   ,  KC_2   ,  KC_3   ,  KC_D   ,
    JP_ASTR,  JP_CIRC,  JP_DLR ,  JP_PLUS,  JP_PIPE, _______,     _______,  KC_B   ,  KC_1   ,  KC_5   ,  KC_6   ,  KC_E   ,
    JP_PERC,  _______,  _______,  JP_MINS,  JP_UNDS, _______,     _______,  KC_A   ,  KC_4   ,  _______,  _______,  KC_F   ,
    _______,  _______,  _______,  _______,  _______, _______,     KC_RGUI,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______, _______,     ___ADD_,  KC_0   , ___MNS_ ,  _______,  _______,  _______
  ),

  [_CMD_] = LAYOUT(
    _______,  ___UNDO,  KC_BTN2,  _______,  _______, _______,     _______,  _______,  _______,  ___CPCM,  ___MENU,  _______,
    ___REDO,  ___ALL_,  KC_BTN1,  KC_APP ,  ___ADRS, _______,     _______,  _A_F1__,  _A_F3__,  ___CPHS,  _A_F7__,  _A_F8__,
    KC_PSCR,  KC_LEFT,  KC_RGHT,  KC_UP  ,  KC_PGUP, _______,     _______,  _A_F6__,  ___COUT,  ___PSTE,  ___COPY,  _A_F4__,
    CT_PSWD,  _______,  _______,  KC_DOWN,  KC_PGDN, _______,     _______,  _A_F9__,  ___CUT_,  _______,  _______,  _A_F5__,
    _______,  _______,  _______,  _______,  _______, _______,     _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______, _______,     ___DEL_,  ___SENT,  ___CLOS,  _______,  _______,  _______
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
const rgblight_segment_t PROGMEM rgb_layer_num[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 12, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM rgb_layer_cmd[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 12, HSV_YELLOW}
);
const rgblight_segment_t* PROGMEM const rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  rgb_layer_eng,
  rgb_layer_jpn,
  rgb_layer_sym,
  rgb_layer_num,
  rgb_layer_cmd
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
  keyball_set_scroll_mode(get_highest_layer(state) == _SYM_);

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
  rgblight_set_layer_state(_NUM_, layer_state_cmp(state, _NUM_));
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
        SEND_STRING("Woods");
        tap_code16(JP_UNDS);
        SEND_STRING("88");
        tap_code16(JP_UNDS);
        SEND_STRING("Bear");
        tap_code16(JP_UNDS);
        SEND_STRING("fc");
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
