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
#include "co_touch.h"

enum keymap_layers {
  _ENG_,
  _JPN_,
  _SYM_,
  _NUM_,
};

// Special key codes for shorthand
#define   ___JPN_   TO(_JPN_)
#define   ___ENG_   TO(_ENG_)
#define   ___S_CM   SFT_T(KC_COMM)  // Shift , COMM
#define   ___S_DT   SFT_T(KC_DOT)   // Shift , DOT
#define   ___T_L1   CTL_T(KC_BSPC)
#define   ___T_L2   LT(_SYM_, KC_TAB)
#define   ___T_L3   GUI_T(KC_SPC)
#define   ___T_R3   LM(___ENG_, MOD_LALT)
#define   ___T_R2   LT(_NUM_, KC_ENT)
#define   ___T_R1   CTL_T(KC_ESC)
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
// VSCode
#define   ___CMDP   A(KC_F1)        // コマンドパレット
#define   ___VIEX   A(KC_F2)        // エクスプローラー
#define   ___AFND   A(KC_F3)        // 全検索
#define   ___VGIT   A(KC_F4)        // Git
#define   ___VPR_   A(KC_F5)        // PullRequest
#define   ___VGH_   A(KC_F6)        // GitHub
#define   ___RECT   A(KC_F7)        // 矩形選択モード
#define   ___TERM   A(KC_F8)        // ターミナル
#define   ___LEDT   A(KC_F9)        // 左エディタ
#define   ___REDT   A(KC_F10)       // 右エディタ
#define   ___FILE   C(KC_P)         // ファイル検索

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_ENG_] = LAYOUT(
    KC_B   ,  KC_H   ,  KC_K   ,  KC_J   ,  KC_Z   , XXXXXXX,     XXXXXXX,  KC_Q   ,  KC_V   ,  KC_S   ,  KC_R   ,  KC_M   ,
    KC_U   ,  KC_A   ,  ___S_CM,  KC_L   ,  KC_W   , XXXXXXX,     XXXXXXX,  KC_C   ,  KC_T   ,  ___S_DT,  KC_N   ,  KC_G   ,
    JP_COLN,  KC_F   ,  KC_I   ,  KC_E   ,  KC_O   , XXXXXXX,     XXXXXXX,  KC_X   ,  KC_D   ,  KC_P   ,  KC_Y   ,  JP_SCLN,
    KC_7   ,  KC_3   ,  KC_1   ,  KC_5   ,  KC_9   , XXXXXXX,     XXXXXXX,  KC_8   ,  KC_2   ,  KC_0   ,  KC_4   ,  KC_6   ,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  ___T_L1,  ___T_L2, XXXXXXX,     XXXXXXX,  ___T_R2,  ___T_R1,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  ___ENG_,  XXXXXXX,  ___T_L3, XXXXXXX,     XXXXXXX,  ___T_R3,  XXXXXXX,  ___JPN_,  XXXXXXX,  XXXXXXX
  ),

  [_JPN_] = LAYOUT(
    CT_00  ,  CT_01  ,  CT_02  ,  CT_03  ,  CT_04  , XXXXXXX,     XXXXXXX,  CT_05  ,  CT_06  ,  CT_07  ,  CT_08  ,  CT_09  ,
    CT_10  ,  CT_11  ,  CT_12  ,  CT_13  ,  CT_14  , XXXXXXX,     XXXXXXX,  CT_15  ,  CT_16  ,  CT_17  ,  CT_18  ,  CT_19  ,
    CT_20  ,  CT_21  ,  CT_22  ,  CT_23  ,  CT_24  , XXXXXXX,     XXXXXXX,  CT_25  ,  CT_26  ,  CT_27  ,  CT_28  ,  CT_29  ,
    _______,  _______,  _______,  _______,  _______, XXXXXXX,     XXXXXXX,  _______,  _______,  _______,  _______,  _______,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______, XXXXXXX,     XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______, XXXXXXX,     XXXXXXX,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX
  ),

  [_SYM_] = LAYOUT(
    JP_CIRC,  JP_DQUO,  JP_HASH,  JP_LCBR,  JP_RCBR, XXXXXXX,     XXXXXXX,  JP_PIPE,  JP_UNDS,  JP_MINS,  JP_ASTR,  JP_BSLS,
    JP_GRV ,  JP_QUOT,  JP_QUES,  JP_LPRN,  JP_RPRN, XXXXXXX,     XXXXXXX,  JP_AMPR,  JP_PLUS,  JP_EXLM,  JP_EQL,   JP_DLR ,
    JP_COLN,  JP_LABK,  JP_RABK,  JP_LBRC,  JP_RBRC, XXXXXXX,     XXXXXXX,  JP_PERC,  JP_SLSH,  JP_TILD,  JP_AT  ,  JP_SCLN,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______, XXXXXXX,     XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______, XXXXXXX,     XXXXXXX,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX
  ), 

  [_NUM_] = LAYOUT(
    RGB_TOG,  KC_LEFT,  KC_UP  ,  KC_DOWN,  KC_PGUP, XXXXXXX,     XXXXXXX,  CT_PSWD,  ___LEDT,  ___TERM,  ___REDT,  ___AFND,
    ___UNDO,  ___ALL_,  KC_F2  ,  KC_RGHT,  KC_PGDN, XXXXXXX,     XXXXXXX,  KC_F5  ,  ___CMDP,  ___CPHS,  ___CPCM,  ___CLSE,
    ___REDO,  KC_PSCR,  ___ADRS,  ___SAVE,  KC_APP , XXXXXXX,     XXXXXXX,  ___COUT,  ___CUT_,  ___PSTE,  ___COPY,  ___QUIT,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DEL ,  KC_BTN1, XXXXXXX,     XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  KC_BTN2, XXXXXXX,     XXXXXXX,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX
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
  rgblight_set_layer_state(_NUM_, layer_state_cmp(state, _NUM_));
  #endif
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 日本語
  if (get_highest_layer(layer_state) == _JPN_) {
    switch (keycode) {
      case CT_12:
        if (record->event.pressed) {
          register_code(KC_LSFT);
        } else {
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
        }
        break;
      case CT_17:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
        }
        break;
      case CT_00 ... CT_11:
      case CT_13 ... CT_16:
      case CT_18 ... CT_29:
        unregister_code(KC_LSFT);
        unregister_code(KC_RSFT);
        break;
      case ___T_R1:
        layer_off(_JPN_);
        layer_on(_ENG_);
      default:
        break;
    }
    return process_cotouch(keycode, record);
  }
  if (get_highest_layer(layer_state) == _NUM_) {
    switch (keycode) {
      case CT_PSWD:
        tap_code16(KC_LANG2);
        SEND_STRING("Woods");
        tap_code16(JP_UNDS);
        SEND_STRING("88");
        tap_code16(JP_UNDS);
        SEND_STRING("Bear");
        tap_code16(JP_UNDS);
        SEND_STRING("fc");
        break;
    }
  }
  return true;
}
