/**
  Copyright (c) 2015 Brewpi/Matthew McGowan.  All rights reserved.

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

#if 0
#include "d4d.h"

#include "controller_screen_layout.h"
#include "mode_assets.h"
#include "../fonts.h"
#include "../brewpi_colors.h"
#include "../widget_color_scheme.h"



#define DECLARE_MODE_BUTTON(x) \
    char mode_button##x[CONTROLLER_MODE_TEXT_LENGTH] = ""; \
    D4D_DECLARE_COLOR_LABEL(scrModeSelector_button##x, mode_button##x, COL2_X, ROWMODE_Y, COL2_CX, ROWMODE_CY, FONT_REGULAR, D4D_NO_CONST, INITIAL_BLOCK_COLOR, REGULAR_TEXT_COLOR)


DECLARE_MODE_BUTTON(1);
DECLARE_MODE_BUTTON(2);
DECLARE_MODE_BUTTON(3);
DECLARE_MODE_BUTTON(4);
DECLARE_MODE_BUTTON(5);

D4D_DECLARE_SCREEN_BEGIN(screen_mode_selector, ScrModeSelector_, COL2_X, 0, COL2_CX, 240, NULL, FONT_REGULAR, NULL, 0, NULL)    
    D4D_DECLARE_SCREEN_OBJECT(scrModeSelector_button1)
    D4D_DECLARE_SCREEN_OBJECT(scrModeSelector_button2)
    D4D_DECLARE_SCREEN_OBJECT(scrModeSelector_button3)
    D4D_DECLARE_SCREEN_OBJECT(scrModeSelector_button4)
    D4D_DECLARE_SCREEN_OBJECT(scrModeSelector_button5)    
D4D_DECLARE_SCREEN_END()        
    

#endif