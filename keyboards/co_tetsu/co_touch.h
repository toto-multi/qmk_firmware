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

#pragma once

#include "keymap_jp.h"

enum custom_keycodes {
  CT_00 = SAFE_RANGE,
  CT_01,
  CT_02,
  CT_03,
  CT_04,
  CT_05,
  CT_06,
  CT_07,
  CT_08,
  CT_09,
  CT_10,
  CT_11,
  CT_12,
  CT_13,
  CT_14,
  CT_15,
  CT_16,
  CT_17,
  CT_18,
  CT_19,
  CT_20,
  CT_21,
  CT_22,
  CT_23,
  CT_24,
  CT_25,
  CT_26,
  CT_27,
  CT_28,
  CT_29,
  CT_PSWD,
  CT_ESC,
};

bool process_cotouch( uint16_t, keyrecord_t * );

