/**************************************
 * stepper_bump_sensiivity_screen.cpp *
 **************************************/

/****************************************************************************
 *   Written By Mark Pelletier  2017 - Aleph Objects, Inc.                  *
 *   Written By Marcio Teixeira 2018 - Aleph Objects, Inc.                  *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <http://www.gnu.org/licenses/>.                              *
 ****************************************************************************/

#include "../config.h"

#if ENABLED(TOUCH_UI_FTDI_EVE) && HAS_TRINAMIC

#include "screens.h"

using namespace FTDI;
using namespace ExtUI;
using namespace Theme;

void StepperBumpSensitivityScreen::onRedraw(draw_mode_t what) {
  widgets_t w(what);
  w.precision(0, BaseNumericAdjustmentScreen::DEFAULT_LOWEST);
  w.heading(                     GET_TEXT_F(MSG_TMC_HOMING_THRS));
  w.color(x_axis)  .adjuster( 2, GET_TEXT_F(MSG_AXIS_X),  getTMCBumpSensitivity(X),
  #if X_SENSORLESS
    true
  #else
    false
  #endif
  );
  w.color(y_axis)  .adjuster( 4, GET_TEXT_F(MSG_AXIS_Y),  getTMCBumpSensitivity(Y),
   #if Y_SENSORLESS
     true
   #else
     false
   #endif
  );
  w.color(z_axis)  .adjuster( 6, GET_TEXT_F(MSG_AXIS_Z),  getTMCBumpSensitivity(Z),
   #if Z_SENSORLESS
     true
   #else
     false
   #endif
  );
  w.increments();
}

bool StepperBumpSensitivityScreen::onTouchHeld(uint8_t tag) {
  const float increment = getIncrement();
  switch (tag) {
    case  2: UI_DECREMENT(TMCBumpSensitivity, X ); break;
    case  3: UI_INCREMENT(TMCBumpSensitivity, X ); break;
    case  4: UI_DECREMENT(TMCBumpSensitivity, Y ); break;
    case  5: UI_INCREMENT(TMCBumpSensitivity, Y ); break;
    case  6: UI_DECREMENT(TMCBumpSensitivity, Z ); break;
    case  7: UI_INCREMENT(TMCBumpSensitivity, Z ); break;
    default:
      return false;
  }
  SaveSettingsDialogBox::settingsChanged();
  return true;
}

#endif // TOUCH_UI_FTDI_EVE && HAS_TRINAMIC
