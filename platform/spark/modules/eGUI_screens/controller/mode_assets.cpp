/**
 ******************************************************************************
  Copyright (c) 2015 Brewpi/Matthew McGowan/Elco Jacobs.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */


#include "mode_assets.h"
#include "mode_selector.h"
#include "ControllerScreenViews.h"
#include "TempControl.h"
#include "../brewpi_colors.h"


const char mode_ids[CONTROLLER_MODE_COUNT] = {
    MODE_FRIDGE_CONSTANT,
    MODE_BEER_CONSTANT,
    MODE_BEER_PROFILE,
    MODE_OFF,
    MODE_TEST
};

// maximum mode text including 
#define CONTROLLER_MODE_TEXT_LENGTH (8)

const char* mode_names[CONTROLLER_MODE_COUNT] = {
    "FRIDGE",
    "BEER",
    "PROFILE",
    "OFF",
    "TEST"
};

const D4D_COLOR mode_colors[CONTROLLER_MODE_COUNT] = {
    MODE_FRIDGE_COLOR,
    MODE_BEER_COLOR,
    MODE_PROFILE_COLOR,
    MODE_OFF_COLOR,
    MODE_TEST_COLOR
};

void show_mode_selector()
{
    show_mode_selector_(tempControl.getMode());
}


int8_t mode_index(char mode)
{
    for (unsigned i=0; i<CONTROLLER_MODE_COUNT; i++) {
        if (mode_ids[i]==mode)
            return i;
    }
    return -1;
}

uint8_t fetch_mode_style(char mode, mode_style* style)
{
    int8_t index = mode_index(mode);
    bool ok = index>=0;
    if (ok) {
        style->color = mode_colors[index];
        style->name = mode_names[index];
    }
    return ok;
}


static const D4D_OBJECT* buttons[] = { &scrModeSelector_button1, &scrModeSelector_button2, 
    &scrModeSelector_button3, &scrModeSelector_button4, &scrModeSelector_button5 };

D4D_EXTERN_SCREEN(screen_mode_selector);

uint8_t mode_focus_index;

void mode_selection_clicked(D4D_OBJECT* pButton)
{
    int idx = -1;
    for (int i=0; i<CONTROLLER_MODE_COUNT; i++) {
        if (pButton==buttons[i])
            idx = i;
    }
    if (idx>=0) {
        idx += (mode_focus_index+CONTROLLER_MODE_COUNT-3);
        idx %= CONTROLLER_MODE_COUNT;
        tempControl.setMode(mode_ids[idx], false);
        D4D_EscapeScreen();
    }
}

void show_mode_selector_(char mode)
{
    uint8_t index = mode_index(mode);
    mode_focus_index = index;
    index += (CONTROLLER_MODE_COUNT-3);
    index %= CONTROLLER_MODE_COUNT;
    
    // assign each button the visual attributes
    for (uint8_t i=0; i<CONTROLLER_MODE_COUNT; i++) 
    {
        ControllerModeView view(buttons[i]);
        ControllerModePresenter pres(view);
        pres.update(mode_ids[index]);
        index = (index+1) % CONTROLLER_MODE_COUNT;
    }
        
    D4D_ActivateScreen((D4D_SCREEN*)&screen_mode_selector, 0);
}
