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

#ifndef MODE_SELECTOR_H
#define	MODE_SELECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "d4d.h"

D4D_EXTERN_OBJECT(scrModeSelector_button1);
D4D_EXTERN_OBJECT(scrModeSelector_button2);
D4D_EXTERN_OBJECT(scrModeSelector_button3);
D4D_EXTERN_OBJECT(scrModeSelector_button4);
D4D_EXTERN_OBJECT(scrModeSelector_button5);


void show_mode_selector();

void show_mode_selector_(char mode);


#ifdef __cplusplus
}
#endif


#endif	/* MODE_SELECTOR_H */

