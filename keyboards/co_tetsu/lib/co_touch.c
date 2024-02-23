/* Copyright 2022 toto toto-03
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

#define CT_LSF  CT_12           // かな左シフトキー
#define CT_RSF  CT_17           // かな右シフトキー
#define B_LSF   1U <<  0        // 左シフト状態
#define B_RSF   1U <<  1        // 左シフト状態
#define B_DAK   1U <<  2        // 濁音シフト状態
#define B_HAN   1U <<  3        // 半濁音シフト状態

// キーコード変換テーブル
#define KANA_MAX 3
const PROGMEM uint16_t KANA_TABLE[][2][KANA_MAX] = {
  // 左手 上段
  {        { JP_LABK ,JP_MINS ,KC_SPC  }, { XXXXXXX ,XXXXXXX ,XXXXXXX } },
  {        { KC_K    ,KC_O    ,XXXXXXX }, { KC_R    ,KC_I    ,XXXXXXX } },
  {        { KC_K    ,KC_I    ,XXXXXXX }, { _______ ,KC_E    ,XXXXXXX } },
  {        { KC_W    ,KC_O    ,XXXXXXX }, { KC_T    ,KC_I    ,XXXXXXX } },
  {        { JP_SLSH ,XXXXXXX ,XXXXXXX }, { XXXXXXX ,XXXXXXX ,XXXXXXX } },
  // 右手 上段
  {        { JP_ASTR ,XXXXXXX ,XXXXXXX }, { XXXXXXX ,XXXXXXX ,XXXXXXX } },
  {        { KC_M    ,KC_A    ,XXXXXXX }, { KC_H    ,KC_E    ,XXXXXXX } },
  {        { KC_N    ,KC_A    ,XXXXXXX }, { _______ ,KC_Y    ,KC_A    } },
  {        { KC_R    ,KC_U    ,XXXXXXX }, { KC_S    ,KC_A    ,XXXXXXX } },
  {        { JP_MINS ,JP_RABK ,KC_SPC  }, { XXXXXXX ,XXXXXXX ,XXXXXXX } },
  // 左手 中段
  {        { KC_T    ,KC_O    ,XXXXXXX }, { KC_M    ,KC_I    ,XXXXXXX } },
  {        { KC_S    ,KC_I    ,XXXXXXX }, { KC_R    ,KC_A    ,XXXXXXX } },
  {        { KC_COMM ,XXXXXXX ,XXXXXXX }, { KC_R    ,KC_E    ,XXXXXXX } },
  {        { KC_K    ,KC_A    ,XXXXXXX }, { _______ ,KC_A    ,XXXXXXX } },
  {        { KC_N    ,KC_I    ,XXXXXXX }, { KC_K    ,KC_E    ,XXXXXXX } },
  // 右手 中段
  {        { KC_K    ,KC_U    ,XXXXXXX }, { KC_R    ,KC_O    ,XXXXXXX } },
  {        { _______ ,KC_I    ,XXXXXXX }, { KC_S    ,KC_U    ,XXXXXXX } },
  {        { KC_DOT  ,XXXXXXX ,XXXXXXX }, { KC_R    ,KC_E    ,XXXXXXX } },
  {        { KC_N    ,KC_N    ,XXXXXXX }, { _______ ,KC_Y    ,KC_O    } },
  {        { KC_MINS ,XXXXXXX ,XXXXXXX }, { JP_TILD ,XXXXXXX ,XXXXXXX } },
  // 左手 下段
  { { _______ ,KC_O    ,XXXXXXX }, { KC_S    ,KC_E    ,XXXXXXX } },
  {        { KC_M    ,KC_O    ,XXXXXXX }, { KC_H    ,KC_U    ,XXXXXXX } },
  {        { KC_X    ,KC_T    ,KC_U    }, { KC_H    ,KC_I    ,XXXXXXX } },
  {        { KC_T    ,KC_E    ,XXXXXXX }, { _______ ,KC_W    ,KC_A    } },
  {        { KC_H    ,KC_A    ,XXXXXXX }, { KC_M    ,KC_E    ,XXXXXXX } },
  // 右手 下段
  {        { KC_T    ,KC_U    ,XXXXXXX }, { KC_M    ,KC_U    ,XXXXXXX } },
  {        { KC_N    ,KC_O    ,XXXXXXX }, { KC_H    ,KC_O    ,XXXXXXX } },
  {        { _______ ,KC_U    ,XXXXXXX }, { KC_N    ,KC_E    ,XXXXXXX } },
  {        { KC_T    ,KC_A    ,XXXXXXX }, { _______ ,KC_Y    ,KC_U    } },
  {        { KC_S    ,KC_O    ,XXXXXXX }, { KC_N    ,KC_U    ,XXXXXXX } },
};

// 濁音・半濁音テーブル
typedef struct {
  uint16_t  mode;
  uint16_t  seion[KANA_MAX];
  uint16_t  dakuon[KANA_MAX];
} SEIDAKU;

const PROGMEM SEIDAKU SEIDAKU_TABLE[] = {
  { B_DAK ,{  KC_K    ,XXXXXXX ,XXXXXXX }, {  KC_G    ,XXXXXXX ,XXXXXXX } },
  { B_DAK ,{  KC_S    ,XXXXXXX ,XXXXXXX }, {  KC_Z    ,XXXXXXX ,XXXXXXX } },
  { B_DAK ,{  KC_T    ,XXXXXXX ,XXXXXXX }, {  KC_D    ,XXXXXXX ,XXXXXXX } },
  { B_DAK ,{  KC_H    ,XXXXXXX ,XXXXXXX }, {  KC_B    ,XXXXXXX ,XXXXXXX } },
  { B_DAK ,{  _______ ,KC_U    ,XXXXXXX }, {  KC_V    ,KC_U    ,XXXXXXX } },
  { B_DAK ,{  KC_W    ,KC_A    ,XXXXXXX }, {  KC_D    ,KC_H    ,KC_I    } },
  { B_HAN ,{  KC_H    ,XXXXXXX ,XXXXXXX }, {  KC_P    ,XXXXXXX ,XXXXXXX } },
  { B_HAN ,{  _______ ,XXXXXXX ,XXXXXXX }, {  KC_X    ,XXXXXXX ,XXXXXXX } },
  { B_HAN ,{  KC_W    ,KC_A    ,XXXXXXX }, {  KC_T    ,KC_H    ,KC_I    } },
};

// 拗音・外来音テーブル
const PROGMEM uint16_t COMB_TABLE[][2][KANA_MAX] = {
  {        {   XXXXXXX ,KC_I   ,XXXXXXX }, {  _______ ,KC_Y    ,XXXXXXX } },
  {        {   _______ ,KC_I   ,XXXXXXX }, {  _______ ,KC_E    ,XXXXXXX } },
  {        {   _______ ,KC_U   ,XXXXXXX }, {  _______ ,KC_A    ,XXXXXXX } },
  {        {   _______ ,KC_U   ,XXXXXXX }, {  _______ ,KC_I    ,XXXXXXX } },
  {        {   _______ ,KC_U   ,XXXXXXX }, {  _______ ,KC_E    ,XXXXXXX } },
  {        {   _______ ,KC_U   ,XXXXXXX }, {  _______ ,KC_O    ,XXXXXXX } },
  {        {   _______ ,KC_U   ,XXXXXXX }, {  _______ ,KC_Y    ,KC_U    } },
  {        {   KC_K    ,KC_U   ,XXXXXXX }, {  _______ ,KC_A    ,XXXXXXX } },
  {        {   KC_K    ,KC_U   ,XXXXXXX }, {  _______ ,KC_I    ,XXXXXXX } },
  {        {   KC_K    ,KC_U   ,XXXXXXX }, {  _______ ,KC_E    ,XXXXXXX } },
  {        {   KC_K    ,KC_U   ,XXXXXXX }, {  _______ ,KC_O    ,XXXXXXX } },
  {        {   KC_K    ,KC_U   ,XXXXXXX }, {  _______ ,KC_W    ,KC_A    } },
  {        {   KC_S    ,KC_I   ,XXXXXXX }, {  _______ ,KC_E    ,XXXXXXX } },
  {        {   KC_T    ,KC_I   ,XXXXXXX }, {  _______ ,KC_E    ,XXXXXXX } },
  {        {   KC_T    ,KC_U   ,XXXXXXX }, {  _______ ,KC_A    ,XXXXXXX } },
  {        {   KC_T    ,KC_U   ,XXXXXXX }, {  _______ ,KC_I    ,XXXXXXX } },
  {        {   KC_T    ,KC_U   ,XXXXXXX }, {  _______ ,KC_E    ,XXXXXXX } },
  {        {   KC_T    ,KC_U   ,XXXXXXX }, {  _______ ,KC_O    ,XXXXXXX } },
  {        {   KC_T    ,KC_E   ,XXXXXXX }, {  _______ ,KC_I    ,XXXXXXX } },
  {        {   KC_T    ,KC_E   ,XXXXXXX }, {  _______ ,KC_Y    ,KC_U    } },
  {        {   KC_T    ,KC_O   ,XXXXXXX }, {  _______ ,KC_U    ,XXXXXXX } },
  {        {   KC_H    ,KC_U   ,XXXXXXX }, {  _______ ,KC_A    ,XXXXXXX } },
  {        {   KC_H    ,KC_U   ,XXXXXXX }, {  _______ ,KC_I    ,XXXXXXX } },
  {        {   KC_H    ,KC_U   ,XXXXXXX }, {  _______ ,KC_E    ,XXXXXXX } },
  {        {   KC_H    ,KC_U   ,XXXXXXX }, {  _______ ,KC_O    ,XXXXXXX } },
  {        {   KC_H    ,KC_U   ,XXXXXXX }, {  _______ ,KC_Y    ,KC_U    } },
};

// 固定文テーブル
typedef struct {
  uint16_t status;
  uint16_t keycode;
  char*  string;
} TEXT;
const PROGMEM TEXT TEXT_TABLE[] = {
  // 半濁音前置
  { B_DAK, CT_07, "masu"},                  // ます
  { B_DAK, CT_12, "onegai"},                // おねがい
  { B_DAK, CT_17, "masita."},               // ました。
  { B_DAK, CT_18, "masenn"},                // ません
  { B_DAK, CT_19, "masyou"},                // ましょう
   // 半濁音前置
  { B_HAN, CT_01, "wakari"},                // わかり
  { B_HAN, CT_03, "tyotto"},                // ちょっと
  { B_HAN, CT_08, "desu"},                  // です
  { B_HAN, CT_10, "nihadousurebaii?"},      // にはどうすればいい？
  { B_HAN, CT_11, "itasimasu."},            // いたします。
  { B_HAN, CT_12, "arigatougozaimasu"},     // ありがとうございます
  { B_HAN, CT_14, "nituite"},               // について
  { B_HAN, CT_15, "kudasai"},               // ください
  { B_HAN, CT_17, "desita."},               // でした。
  { B_HAN, CT_19, "desyouka?"},             // でしょうか？
  { B_HAN, CT_25, "muzukasii"},             // むずかしい
  { B_HAN, CT_29, "sumimasenn"},            // すみません
};

#define BUFFER_SIZE 4
static uint16_t buffer[BUFFER_SIZE];
static uint8_t  buffer_cnt = 0;
static uint8_t  shift_count = 0;

static uint16_t status = 0;
void set_status( const uint16_t bitcode, const bool onoff ) {
  if ( onoff ) {
    status |= bitcode;
  } else {
    status &= ~bitcode;
  }
}

bool get_status( const uint16_t bitcode ) {
  return ( ( status & bitcode ) == bitcode );
}

// 状態を表示する
void print_status( void ) {
  dprintf( "========\n" );
  for ( int i = 0; i < buffer_cnt; i++ ) {
    dprintf( "buffer[%d]   = %2d\n", i, buffer[i] );
  }
  uint16_t mask = 1U;
  dprintf( "LS RS DK HN -- -- -- -- \n" );
  for ( int i = 0; i < 8; i++ ) {
    dprintf( "%2d ", ( ( status & mask ) != 0 ) );
    mask <<= 1;
  }
  dprintf( "\n" );
  dprintf( "shift_count = %d\n", shift_count );
  dprintf( "========\n" );
}

bool is_left_key( uint16_t keycode ) {
  switch ( keycode ) {
    case CT_00 ... CT_04:
    case CT_10 ... CT_14:
    case CT_20 ... CT_24:
      return true;
    default:
      break;
  }
  return false;
}

// バッファから先頭文字を削除する
void compress_buffer( void ) {
  if ( buffer_cnt == 0 ) return;
  for ( int j = 0; j < BUFFER_SIZE; j++ ) {
    if ( j + 1 < BUFFER_SIZE ) {
      buffer[j] = buffer[j + 1];
    } else {
      buffer[j] = XXXXXXX;
    }
  }
  buffer_cnt--;
}

void tap_keycodes( const uint16_t kana[KANA_MAX] ) {
  dprintf( "tap_keycodes() called.\n" );
  for ( int j = 0; j < KANA_MAX; j++ ) {
    if ( kana[j] == XXXXXXX ) continue;
    dprintf( "kana[%d] = %d\n", j, kana[j] );
    tap_code16( kana[j] );
    // 濁音・半濁音ON/OFF
    set_status( B_DAK, ( kana[j] == KC_COMM && !get_status( B_DAK ) ) );
    set_status( B_HAN, ( kana[j] == KC_DOT  && !get_status( B_HAN ) ) );
  }
  compress_buffer();
  dprintf( "tap_keycodes() finished.\n" );
}

bool is_match( const uint16_t kana_0[KANA_MAX],
               const uint16_t kana_1[KANA_MAX] ) {
  dprintf( "is_match() called.\n" );
  for ( int i = 0; i < KANA_MAX; i++ ) {
    if ( kana_1[i] == XXXXXXX ) continue;
    if ( kana_0[i] != kana_1[i] ) {
      return false;
    }
  }
  dprintf( "is_match() finished.\n" );
  return true;
}

bool dakuon( uint16_t kana[KANA_MAX] ) {
  dprintf( "dakuon() called.\n" );
  SEIDAKU seidaku;
  for ( int i = 0; i < ( sizeof( SEIDAKU_TABLE ) / sizeof( seidaku ) ); i++ ) {
    memcpy_P( &seidaku, &SEIDAKU_TABLE[i], sizeof( seidaku ) );
    if ( ( status & seidaku.mode ) != seidaku.mode ) continue;
    if ( is_match( kana, seidaku.seion ) ) {
      for ( int j = 0; j < KANA_MAX; j++ ) {
        if ( seidaku.dakuon[j] == XXXXXXX ) continue;
        kana[j] = seidaku.dakuon[j];
      }
      tap_code16( KC_BSPC );
      return true;
    }
  }
  dprintf( "dakuon() finished.\n" );
  return false;
}

void combine_kana( uint16_t kana_0[2][KANA_MAX], uint16_t kana_1[2][KANA_MAX] ) {
  dprintf( "combine_kana() called.\n" );
  uint16_t comb[2][KANA_MAX];
  for ( int i = 0; i < 2; i++ ) {
    for ( int j = 0; j < 2; j++ ) {
      for ( int k = 0; k < ( sizeof( COMB_TABLE ) / sizeof( comb ) ); k++ ) {
        memcpy_P(&comb, &COMB_TABLE[k], sizeof( comb ) );
        if ( is_match( kana_0[i], comb[0] ) && is_match( kana_1[j], comb[1] ) ) {
          dakuon( kana_0[i] );
          tap_keycodes( kana_0[i] );
          tap_code16( KC_X );
          tap_keycodes( kana_1[j] );
          return;
        } else if ( is_match( kana_0[i], comb[1] ) && is_match( kana_1[j], comb[0] ) ) {
          dakuon( kana_1[j] );
          tap_keycodes( kana_1[j] );
          tap_code16( KC_X );
          tap_keycodes( kana_0[i] );
          return;
        }
      }
    }
  }
  // コンボできなかったらバッファの先頭文字のみ出力する
  tap_keycodes( kana_0[0] );
  dprintf( "combine_kana() finished.\n" );
}

// 固定文を送信する
bool send_text( int keycode ) {
  int status = 0;
  if ( get_status( B_DAK ) ) status = B_DAK;
  if ( get_status( B_HAN ) ) status = B_HAN;
  TEXT text;
  for ( int i = 0; i < ( sizeof( TEXT_TABLE ) / sizeof( TEXT ) ); i++ ) {
    memcpy_P( &text, &TEXT_TABLE[i], sizeof( TEXT ) );
    if ( status == text.status && keycode == text.keycode ) {
      tap_code16( KC_BSPC );
      send_string(text.string);
      compress_buffer();
      set_status( B_DAK, false );
      set_status( B_HAN, false );
      return true;
    }
  }
  return false;
}

// キーコードを送信する
void send_kana( void ) {
  dprintf( "send_kana() called.\n" );
  print_status();
  uint16_t kana_0[2][KANA_MAX];
  memcpy_P( &kana_0, &KANA_TABLE[buffer[0] - CT_00], sizeof( kana_0 ) );
  if ( buffer_cnt  > 1 ) {
    // 同時打鍵
    uint16_t kana_1[2][KANA_MAX];
    memcpy_P( &kana_1, &KANA_TABLE[buffer[1] - CT_00], sizeof( kana_1) );
    combine_kana( kana_0, kana_1 );
  } else {
    if ( ( get_status( B_LSF ) && !is_left_key( buffer[0] ) ) ||
         ( get_status( B_RSF ) &&  is_left_key( buffer[0] ) ) ) {
      // シフト
      tap_keycodes( kana_0[1] );
      shift_count++;
    } else {
      // 固定文
      if ( send_text( buffer[0] ) ) {
        return;
      }
      if ( dakuon( kana_0[0] ) ) {
        // 濁音
        tap_keycodes( kana_0[0] );
      } else if ( dakuon( kana_0[1] ) ) {
        // 半濁音
        tap_keycodes( kana_0[1] );
      } else {
        // 単打
        tap_keycodes( kana_0[0] );
      }
    }
  }
  print_status();
  dprintf( "send_kana() finished.\n" );
}

bool process_cotouch( uint16_t keycode, keyrecord_t *record ) {
  dprintf( "process_cotouch() called.\n" );
  dprintf( "keycode = %d\n", keycode);

  // キーコード範囲チェック
  switch ( keycode ) {
    case CT_00 ... CT_29:
      break;
    case KC_RGHT ... KC_UP:
    case KC_SPC:
    case KC_TAB:
      shift_count++;
      return true;
    default:
      status = 0;
      shift_count = 0;
      return true;
  }

  if ( record->event.pressed ) {
    dprintf( "record->event.pressed !\n" );
    // シフト設定
    if ( keycode == CT_LSF && !get_status( B_RSF ) ) {
      set_status( B_LSF, true );
    } else if ( keycode == CT_RSF && !get_status( B_LSF ) ) {
      set_status( B_RSF, true );
    } else {
      // バッファに追加
      buffer[buffer_cnt] = keycode;
      buffer_cnt++;
    }
    print_status();
  } else {
    dprintf( "record->event.released !\n" );
    // かな送信
    while ( buffer_cnt > 0 ) {
      print_status();
      send_kana();
    }
    // シフト解除
    if ( keycode == CT_LSF ) {
      set_status( B_LSF, false );
      if ( ( shift_count == 0 ) && !get_status( B_RSF ) ) {
        buffer[buffer_cnt] = keycode;
        buffer_cnt++;
        send_kana();
      }
    }
    if ( keycode == CT_RSF ) {
      set_status( B_RSF, false );
      if ( ( shift_count == 0 ) && !get_status( B_LSF ) ) {
        buffer[buffer_cnt] = keycode;
        buffer_cnt++;
        send_kana();
      }
    }
    if ( !get_status( B_LSF ) && !get_status( B_RSF ) ) shift_count = 0;
  }
  dprintf( "process_cotouch() finished.\n" );
  return false;
}
